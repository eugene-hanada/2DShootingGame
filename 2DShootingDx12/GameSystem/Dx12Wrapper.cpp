#include <list>
#include <string>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dx12.h>
#include "Window.h"
#include "Dx12/Resource/CbMatrix.h"
#include "Dx12Wrapper.h"

#include "../common/Debug.h"

Dx12Wrapper::Dx12Wrapper(Window& wnd)
{
	SetClearRenderTarget(1.0f, 1.0f, 1.0f, 1.0f);
	
	if (!CreateDXGIDevice())
	{
		DebugLog("デバイスの生成に失敗");
		assert(false);
	}
	DebugLog("デバイスの生成に成功");

	if (FAILED(device_->CreateFence(fenceVal_, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence_.ReleaseAndGetAddressOf()))))
	{
		DebugLog("フェンス生成に失敗");
		assert(false);
	}
	DebugLog("フェンス生成に成功");


	if (!CreateCommand())
	{
		DebugLog("コマンド生成に失敗");
		assert(false);
	}
	DebugLog("コマンド生成に成功");

	if (!CreateSwapChain(wnd))
	{
		DebugLog("スワップチェインの生成に失敗");
		assert(false);
	}
	DebugLog("スワップチェイン生成に成功");

	if (!CreateFinalRenderTarget())
	{
		assert(false);
	}


	cbMat_ = std::make_unique<CbMatrix>(*this);
	cbMat_->mat_.m[0][0] = 2.0f / wnd.GetSize<float>().x;
	cbMat_->mat_.m[1][1] = -2.0f / wnd.GetSize<float>().y;
	cbMat_->mat_.m[3][0] = -1.0f;
	cbMat_->mat_.m[3][1] = 1.0f;
	cbMat_->Update();
}

Dx12Wrapper::~Dx12Wrapper()
{
}

void Dx12Wrapper::BeginFinalRenderTarget(void)
{
	// バックバッファのインデックスを取得
	auto bbIdx = swapChain_->GetCurrentBackBufferIndex();
	// リソースバリアの設定
	auto barrierDesc = CD3DX12_RESOURCE_BARRIER::Transition(backBuffers_[bbIdx].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	cmdList_->ResourceBarrier(1, &barrierDesc);

	// レンダーターゲットを指定する
	// ハンドルを取得
	auto rtvH = rtvHeap_->GetCPUDescriptorHandleForHeapStart();
	// 1のバッファの方に進める
	rtvH.ptr += static_cast<ULONG_PTR>(bbIdx) * static_cast<ULONG_PTR>(device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));


	// 画面をクリアにする
	cmdList_->ClearRenderTargetView(rtvH, clearColor_, 0, nullptr);

	cmdList_->OMSetRenderTargets(1, &rtvH, false, nullptr);

	// ビューポートとシザー矩形をセット
	cmdList_->RSSetViewports(1, viewPort_.get());
	cmdList_->RSSetScissorRects(1, scissorRect_.get());
	
}

void Dx12Wrapper::EndFinalRenderTarget(void)
{
	// バリアを解除
	auto bbIdx = swapChain_->GetCurrentBackBufferIndex();
	auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(backBuffers_[bbIdx].Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	cmdList_->ResourceBarrier(1, &barrier);
}

void Dx12Wrapper::DrawFinalRenderTarget(void)
{

	// コマンドリストの命令を実行するためにクローズ
	auto result = cmdList_->Close();

	// コマンドリストの命令を実行
	ID3D12CommandList* cmdLists[]{ cmdList_.Get() };
	cmdQueue_->ExecuteCommandLists(1, cmdLists);

	// 待つ処理
	// フェンス値を取得
	result = cmdQueue_->Signal(fence_.Get(), ++fenceVal_);
	if (fence_->GetCompletedValue() < fenceVal_)
	{
		// イベントを取得
		auto ev = CreateEvent(nullptr, false, false, nullptr);

		// イベントをセット
		fence_->SetEventOnCompletion(fenceVal_, ev);

		// イベントが発生するまで待つ
		WaitForSingleObject(ev, INFINITE);

		// イベントを閉じる
		CloseHandle(ev);
	}

	// コマンドキューとコマンドリストの命令の再受け入れ処理
	cmdAllocator_->Reset();
	cmdList_->Reset(cmdAllocator_.Get(), nullptr);

	swapChain_->Present(1, 0);
}

bool Dx12Wrapper::CreateDXGIDevice(void)
{
	UINT flagsDXGI = 0;

#ifdef _DEBUG
	flagsDXGI |= DXGI_CREATE_FACTORY_DEBUG;
#endif

	if (FAILED(CreateDXGIFactory2(flagsDXGI, IID_PPV_ARGS(dxgiFactory_.ReleaseAndGetAddressOf()))))
	{
		DebugLog("DXGIFactory2の生成に失敗");
		return false;
	}
	DebugLog("DXGIFactory2の生成に成功");

	// アダプターの列挙用
	std::list<IDXGIAdapter*> adapters;

	// 目的の名前のアダプターを入れる
	IDXGIAdapter* tmpAdapter = nullptr;

	// アダプターを格納してく
	for (int i = 0; dxgiFactory_->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; i++)
	{
		adapters.push_back(tmpAdapter);
	}

	// 格納したアダプターの中から目的の名前のアダプターを探す
	std::wstring strDesc;
	tmpAdapter = *adapters.begin();
	for (auto& adpt : adapters)
	{
		DXGI_ADAPTER_DESC adesc{};
		adpt->GetDesc(&adesc);			// アダプターの説明オブジェクトを取得する
		strDesc = adesc.Description;
		if (strDesc.find(L"NVIDIA") != std::string::npos)
		{
			// 一致したら抜ける
			tmpAdapter = adpt;
			break;
		}
	}

	// フューチャーレベルの配列
	D3D_FEATURE_LEVEL levels[]{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};
	D3D_FEATURE_LEVEL fLavel;

	
	
	for (auto& level : levels)
	{
		if (SUCCEEDED(D3D12CreateDevice(tmpAdapter, level, IID_PPV_ARGS(device_.ReleaseAndGetAddressOf()))))
		{
			// 見つかったらやめる
			fLavel = level;
			DebugLog("Deviceの生成に成功");
			device_->SetName(TEXT("Device"));
			return true;
		}
	}
	DebugLog("Deviceの生成に失敗");
	return false;
}

bool Dx12Wrapper::CreateCommand(void)
{
	// コマンドアロケーターを作成
	if (FAILED(device_->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(cmdAllocator_.ReleaseAndGetAddressOf())
	))
		)
	{
		DebugLog("コマンドアロケーターの生成に失敗");
		return false;
	}
	DebugLog("コマンドアロケーターの生成に成功");
	//cmdAllocator_->SetName(TEXT("CommandAllocator"));

	// コマンドリストを作成
	if (FAILED(device_->CreateCommandList(
		0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator_.Get(), nullptr, IID_PPV_ARGS(cmdList_.ReleaseAndGetAddressOf())
	)))
	{
		DebugLog("コマンドリストの生成に失敗");
		return false;
	}
	DebugLog("コマンドリストの生成に成功");

	// cmdAllocator_->SetName(TEXT("CommandList"));

	// 設定をDESC構造体で行う
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc{};

	// タイムアウトの設定(無しにする)
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	// アダプターの設定(一つしか使わないときは0でいい)
	cmdQueueDesc.NodeMask = 0;

	// プライオリティ特に設定なし
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;

	// ここはコマンドリストと合わせる
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	// キューを生成
	if (FAILED(device_->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(cmdQueue_.ReleaseAndGetAddressOf()))))
	{
		DebugLog("コマンドキューの生成に失敗");
		return false;
	}
	DebugLog("コマンドキューの生成に成功");
	return true;
}

bool Dx12Wrapper::CreateSwapChain(Window& wnd)
{
	// 設定用のDESC
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc{};

	// 幅
	swapchainDesc.Width = wnd.GetSize<UINT>().x;

	// 高さ
	swapchainDesc.Height = wnd.GetSize<UINT>().y;

	// ピクセルフォーマット
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// ステレオ表示フラグ
	swapchainDesc.Stereo = false;

	// マルチサンプルの指定(Countは1, Qualityは0でよい)
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;

	// DXGI_USAGE_BACK_BUFFERこんままでよか
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// バッファーの数ダブルバッファ-なので2
	swapchainDesc.BufferCount = 2;

	// バックバッファ-は伸び縮みできるように設定
	swapchainDesc.Scaling = DXGI_SCALING_STRETCH;

	// フリップ後にすぐに破棄するように設定
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	// 特に指定しないのでDXGI_ALPHA_MODE_UNSPECIFIEDで
	swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

	// フルスクリーン-ウィンドウの切り替え可能に設定
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


	// スワップチェインの生成
	IDXGISwapChain1* swapchain = nullptr;

	if (FAILED(dxgiFactory_->CreateSwapChainForHwnd(cmdQueue_.Get(), wnd.GetWndHandle(), &swapchainDesc, nullptr, nullptr, &swapchain)))
	{
		DebugLog("スワップチェインの生成に失敗");
		return false;
	}
	if (FAILED(swapchain->QueryInterface(IID_PPV_ARGS(swapChain_.ReleaseAndGetAddressOf()))))
	{
		DebugLog("スワップチェインの生成に失敗");
		return false;
	}
	DebugLog("スワップチェインの生成に成功");
	return true;
}

bool Dx12Wrapper::CreateFinalRenderTarget(void)
{
	// 設定用DESC
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};

	// レンダービューターゲットビューなのでRTVを設定
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

	// 複数のGPUを使うとき用なので0で
	heapDesc.NodeMask = 0;

	// ディスクリプタの数を表すのでダブルバッファーにするので2にする
	heapDesc.NumDescriptors = 2;

	// テクスチャバッファーや定数バッファーを使うはないのでNONEで
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	// ディスクリプタヒープを生成
	if (FAILED(device_->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(rtvHeap_.ReleaseAndGetAddressOf()))))
	{
		DebugLog("レンダーターゲット用デスクリプタヒープの生成に失敗");
		return false;
	}
	//rtvHeap_->SetName(TEXT("RenderTargetHeap"));

	// スワップチェインと紐づけする
	DXGI_SWAP_CHAIN_DESC1 swcDesc{};

	if (FAILED(swapChain_->GetDesc1(&swcDesc)))
	{
		DebugLog("スワップチェインの情報取得に失敗");
		return false;
	}

	backBuffers_.resize(swcDesc.BufferCount);

	// 先頭のポインタを取得
	D3D12_CPU_DESCRIPTOR_HANDLE handle = rtvHeap_->GetCPUDescriptorHandleForHeapStart();

	// SRGB用のレンダーターゲットビュー設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	// rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	for (unsigned int i = 0; i < swcDesc.BufferCount; i++)
	{
		if (FAILED(swapChain_->GetBuffer(static_cast<UINT>(i), IID_PPV_ARGS(backBuffers_[i].ReleaseAndGetAddressOf()))))
		{
			DebugLog("スワップチェインのバッファー取得に失敗");
			return false;
		}

		// レンダービューターゲットに設定
		device_->CreateRenderTargetView(backBuffers_[i].Get(), &rtvDesc, handle);

		// ポインタをずらす
		handle.ptr += device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	}

	viewPort_ = std::make_unique<CD3DX12_VIEWPORT>(backBuffers_[0].Get());
	scissorRect_ = std::make_unique<CD3DX12_RECT>(0, 0, swcDesc.Width, swcDesc.Height);
	DebugLog("ファイナルレンダーターゲットの生成に成功");
	return true;
}
