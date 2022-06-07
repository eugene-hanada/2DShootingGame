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
		DebugLog("�����_�[�^�[�Q�b�g�̐����Ɏ��s");
		assert(false);
	}
	DebugLog("�����_�[�^�[�Q�b�g�̐����ɐ���");
}

RenderTarget::~RenderTarget()
{
}


void RenderTarget::DrawBegin(void)
{
	// �o���A���쐬(�V�F�[�_���\�[�X���烌���_�[�^�[�Q�b�g��)
	auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(texure_->GetResource().Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);

	// �o���A���Z�b�g
	dx12_.CmdLlist()->ResourceBarrier(1, &barrier);

	auto h = rtDescriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// �����_�[�^�[�Q�b�g���Z�b�g
	dx12_.CmdLlist()->OMSetRenderTargets(1, &h, false, nullptr);

	// �r���[�|�[�g�ƃV�U�[��`���Z�b�g
	dx12_.CmdLlist()->RSSetViewports(1, viewPort_.get());
	dx12_.CmdLlist()->RSSetScissorRects(1, scissorRect_.get());

}

void RenderTarget::DrawEnd(void)
{
	// �o���A���쐬(�����_�[�^�[�Q�b�g����V�F�[�_���\�[�X��)
	auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(texure_->GetResource().Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

	// �o���A���Z�b�g
	dx12_.CmdLlist()->ResourceBarrier(1, &barrier);
}

void RenderTarget::Clear(void)
{
	// �o���A���쐬(�V�F�[�_���\�[�X���烌���_�[�^�[�Q�b�g��)
	auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(texure_->GetResource().Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);

	// �o���A���Z�b�g
	dx12_.CmdLlist()->ResourceBarrier(1, &barrier);

	// �����_�[�^�[�Q�b�g���w��̐F�ɃN���A
	dx12_.CmdLlist()->ClearRenderTargetView(rtDescriptorHeap_->GetCPUDescriptorHandleForHeapStart(), color_, 0, nullptr);

	// �o���A���쐬(�����_�[�^�[�Q�b�g����V�F�[�_���\�[�X��)
	barrier = CD3DX12_RESOURCE_BARRIER::Transition(texure_->GetResource().Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

	// �o���A���Z�b�g
	dx12_.CmdLlist()->ResourceBarrier(1, &barrier);
}


bool RenderTarget::CreateRenderTarget(void)
{
	ComPtr<ID3D12Resource> resource{nullptr};
	D3D12_DESCRIPTOR_HEAP_DESC descHDesc{};

	// �t���O�͓��ɂȂ��̂�NONE
	descHDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	descHDesc.NodeMask = 0;
	descHDesc.NumDescriptors = 1;

	// �����_�[�^�[�Q�b�g�Ɏg�p����
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

	// �����_�[�^�[�Q�b�g�r���[�ݒ�
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	// �����_�[�r���[�^�[�Q�b�g�ɐݒ�
	dx12_.Device()->CreateRenderTargetView(resource.Get(), &rtvDesc, rtDescriptorHeap_->GetCPUDescriptorHandleForHeapStart());

	viewPort_ = std::make_unique<CD3DX12_VIEWPORT>(resource.Get());
	scissorRect_ = std::make_unique<CD3DX12_RECT>(0, 0, static_cast<long>(resDesc.Width), static_cast<long>(resDesc.Height));

	
	texure_ = std::make_shared<Texture>(dx12_, resource);
	material_->shaderResource_.emplace_back(texure_);

	return true;
}


