#include <d3dx12.h>
#include <d3dcompiler.h>
#include "../../Dx12Wrapper.h"
#include "../../../common/Debug.h"
#include "TextureSheetRender.h"

TextureSheetRender::TextureSheetRender(Dx12Wrapper& dx12, std::uint32_t maxNum) :
	dx12_{dx12}, maxNum_{maxNum}
{
}

TextureSheetRender::~TextureSheetRender()
{
}

void TextureSheetRender::Draw(const Math::Vector2& lt, const Math::Vector2& rt, const Math::Vector2& lb, const Math::Vector2& rb, std::string_view key)
{
	int nowIdx = nowNum_ * 4;
	int idicIdx = nowNum_ * 6;
	vertices_[nowIdx].no = nowNum_;
	vertices_[nowIdx].pos = lt;
	vertices_[nowIdx].uv;
	idices_[idicIdx] = nowIdx;

	nowIdx++;
	vertices_[nowIdx].no = nowNum_;
	vertices_[nowIdx].pos = rt;
	vertices_[nowIdx].uv;
	idices_[idicIdx + 1] = nowIdx;
	idices_[idicIdx + 3] = nowIdx;

	nowIdx++;
	vertices_[nowIdx].no = nowNum_;
	vertices_[nowIdx].pos = lb;
	vertices_[nowIdx].uv;
	idices_[idicIdx + 2] = nowIdx;
	idices_[idicIdx + 5] = nowIdx;

	nowIdx++;
	vertices_[nowIdx].no = nowNum_;
	vertices_[nowIdx].pos = rb;
	vertices_[nowIdx].uv;
	idices_[idicIdx + 4] = nowIdx;
	
	DirectX::XMStoreFloat4x4(&mat_[nowNum_], DirectX::XMMatrixIdentity());
	nowNum_++;
}

bool TextureSheetRender::CreateRootSignature(void)
{
	return false;
}

bool TextureSheetRender::CreatePipeline(void)
{
	auto flag = D3DCOMPILE_SKIP_OPTIMIZATION;
#ifdef _DEBUG
	flag |= D3DCOMPILE_DEBUG;
#endif
	ComPtr<ID3DBlob> vs{};
	ComPtr<ID3DBlob> errorBlob{ nullptr };
	HRESULT result = D3DCompileFromFile(
		L"",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"vs_5_0",
		flag,
		0,
		&vs,
		&errorBlob);
	if (FAILED(result))
	{
		DebugLog("頂点シェーダのコンパイルに失敗");
		return false;
	}

	ComPtr<ID3DBlob> ps{};
	result = D3DCompileFromFile(
		L"",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"ps_5_0",
		flag,
		0,
		&ps,
		&errorBlob
	);
	if (FAILED(result))
	{
		DebugLog("ピクセルシェーダのコンパイルに失敗");
		return false;
	}

	// シェーダのインプットレイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{	// 座標情報
			"POSITION",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
		{	// uv情報
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
		{	// 行列の番号
			"BONE_NO",
			0,
			DXGI_FORMAT_R32_UINT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
	};

	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	// ルートシグネチャをセット
	gpipeline.pRootSignature = rootSignature_.Get();

	// シェーダをセット
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vs.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(ps.Get());

	// デフォルトのサンプルマスク
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	// ラスタライザ周りの設定
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;

	// 深度ステンシルの設定
	gpipeline.DepthStencilState.DepthEnable = false;
	gpipeline.DepthStencilState.StencilEnable = false;


	// ブレンド設定系
	gpipeline.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	gpipeline.BlendState.RenderTarget[0].BlendEnable = true;
	gpipeline.BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	gpipeline.BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	gpipeline.BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

	// 入力レイアウトを設定
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	// ポリゴンの表示についての設定
	gpipeline.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;		// インデックスバッファを使う
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;		// 三角形を表す
	gpipeline.NumRenderTargets = 1;		// 今は一つなので
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;		// 正規化されたRGBAを渡す

	// アンチエイリアシングに関する設定
	gpipeline.SampleDesc.Count = 1;
	gpipeline.SampleDesc.Quality = 0;

	if (FAILED(dx12_.Device()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(pipeline_.ReleaseAndGetAddressOf()))))
	{
		DebugLog("グラフィックパイプラインの生成に失敗");
		return false;
	}
	return true;
}

bool TextureSheetRender::CreateVertex(void)
{
	vertices_.resize(maxNum_ * 4);
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto vrResDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices_[0]) * vertices_.size());
	// リソース生成
	if (dx12_.Device()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&vrResDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(vb_.ReleaseAndGetAddressOf())) != S_OK)
	{
		return false;
	}

	// 頂点情報のコピー
	if (vb_->Map(0, nullptr, reinterpret_cast<void**>(&vertMap_)) != S_OK)
	{
		return false;
	}
	std::copy(vertices_.begin(), vertices_.end(), vertMap_);
	
	// 頂点バッファービューの作成
	vbView_ = std::make_unique<D3D12_VERTEX_BUFFER_VIEW>();
	vbView_->BufferLocation = vb_->GetGPUVirtualAddress();		// バッファの仮想アドレスを入れる
	vbView_->SizeInBytes = static_cast<UINT>(sizeof(vertices_[0]) * vertices_.size());		// 総バイト数
	vbView_->StrideInBytes = sizeof(Vertex);		// 1t頂点当たりのバイト数

	return true;
}

bool TextureSheetRender::CreateIdx(void)
{
	idices_.resize(maxNum_ * 6);
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto irResDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(idices_[0]) * idices_.size());
	if (dx12_.Device()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&irResDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(ib_.ReleaseAndGetAddressOf())) != S_OK)
	{
		return false;
	}

	// 作ったバッファにインデックスデータをコピー
	if (FAILED(ib_->Map(0, nullptr, (void**)&idMap)))
	{
		return false;
	}
	std::copy(std::begin(idices_), std::end(idices_), idMap);


	// インデックスバッファビューを作成する
	ibView_ = std::make_unique<D3D12_INDEX_BUFFER_VIEW>();
	ibView_->BufferLocation = ib_->GetGPUVirtualAddress();
	ibView_->Format = DXGI_FORMAT_R16_UINT;
	ibView_->SizeInBytes = static_cast<UINT>(sizeof(idices_[0]) * idices_.size());

	return false;
}
