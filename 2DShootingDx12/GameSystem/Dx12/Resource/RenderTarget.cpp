#include "Mesh.h"
#include "CbMatrix.h"
#include "MaterialBase.h"
#include "Texture.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget(Dx12Wrapper& dx12,const Math::Vector2& size) :
	size_{size}, dx12_{dx12}
{
	cbMat_ = std::make_unique<CbMatrix>(dx12);
	cbMat_->mat_.m[0][0] = 2.0f / size.x;
	cbMat_->mat_.m[1][1] = -2.0f / size.y;
	cbMat_->mat_.m[3][0] = -1.0f;
	cbMat_->mat_.m[3][1] = 1.0f;
	cbMat_->Update();
	material_ = std::make_unique<MaterialBase>(dx12_, size_);
	if (!CreateRenderTarget())
	{
		DebugLog("レンダーターゲットの生成に失敗");
		assert(false);
	}
	DebugLog("レンダーターゲットの生成に成功");
}

RenderTarget::~RenderTarget()
{
}


void RenderTarget::DrawBegin(void)
{
	// バリアを作成(シェーダリソースからレンダーターゲットに)
	auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(texure_->GetResource().Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);

	// バリアをセット
	dx12_.CmdLlist()->ResourceBarrier(1, &barrier);

	auto h = rtDescriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// レンダーターゲットをセット
	dx12_.CmdLlist()->OMSetRenderTargets(1, &h, false, nullptr);

	// ビューポートとシザー矩形をセット
	dx12_.CmdLlist()->RSSetViewports(1, viewPort_.get());
	dx12_.CmdLlist()->RSSetScissorRects(1, scissorRect_.get());

}

void RenderTarget::DrawEnd(void)
{
	// バリアを作成(レンダーターゲットからシェーダリソースに)
	auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(texure_->GetResource().Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

	// バリアをセット
	dx12_.CmdLlist()->ResourceBarrier(1, &barrier);
}

void RenderTarget::Clear(void)
{
	// バリアを作成(シェーダリソースからレンダーターゲットに)
	auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(texure_->GetResource().Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);

	// バリアをセット
	dx12_.CmdLlist()->ResourceBarrier(1, &barrier);

	// レンダーターゲットを指定の色にクリア
	dx12_.CmdLlist()->ClearRenderTargetView(rtDescriptorHeap_->GetCPUDescriptorHandleForHeapStart(), color_, 0, nullptr);

	// バリアを作成(レンダーターゲットからシェーダリソースに)
	barrier = CD3DX12_RESOURCE_BARRIER::Transition(texure_->GetResource().Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

	// バリアをセット
	dx12_.CmdLlist()->ResourceBarrier(1, &barrier);
}


bool RenderTarget::CreateRenderTarget(void)
{
	ComPtr<ID3D12Resource> resource{nullptr};
	D3D12_DESCRIPTOR_HEAP_DESC descHDesc{};

	// フラグは特にないのでNONE
	descHDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	descHDesc.NodeMask = 0;
	descHDesc.NumDescriptors = 1;

	// レンダーターゲットに使用する
	descHDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

	if (FAILED(dx12_.Device()->CreateDescriptorHeap(&descHDesc, IID_PPV_ARGS(rtDescriptorHeap_.ReleaseAndGetAddressOf()))))
	{
		return false;
	}

	D3D12_HEAP_PROPERTIES heapProp{ CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT) };
	D3D12_RESOURCE_DESC resDesc{};
	D3D12_CLEAR_VALUE clearVal{ CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM,color_) };
	resDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resDesc.MipLevels = 1;
	resDesc.Width = static_cast<UINT64>(size_.x);
	resDesc.Height = static_cast<UINT64>(size_.y);
	resDesc.DepthOrArraySize = 1;
	resDesc.Alignment = 65536;
	resDesc.SampleDesc.Count = 1;
	resDesc.SampleDesc.Quality = 0;
	resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
	//resDesc.Alignment = 
	if (FAILED(
		dx12_.Device()->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			&clearVal,
			IID_PPV_ARGS(resource.ReleaseAndGetAddressOf())
		)))
	{
		return false;
	}

	// レンダーターゲットビュー設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	// レンダービューターゲットに設定
	dx12_.Device()->CreateRenderTargetView(resource.Get(), &rtvDesc, rtDescriptorHeap_->GetCPUDescriptorHandleForHeapStart());

	viewPort_ = std::make_unique<CD3DX12_VIEWPORT>(resource.Get());
	scissorRect_ = std::make_unique<CD3DX12_RECT>(0, 0, static_cast<long>(resDesc.Width), static_cast<long>(resDesc.Height));

	
	texure_ = std::make_shared<Texture>(dx12_, resource);
	material_->shaderResource_.emplace_back(texure_);

	return true;
}


