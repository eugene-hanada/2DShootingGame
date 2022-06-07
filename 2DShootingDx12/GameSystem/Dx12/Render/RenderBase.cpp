#include <d3d12.h>
#include "../../Dx12Wrapper.h"
#include "../Resource/MaterialBase.h"
#include "../../../Component/Transform.h"
#include "../Resource/Mesh.h"
#include "RenderBase.h"

RenderBase::RenderBase(Dx12Wrapper& dx12) :
	dx12_{dx12}
{
}

RenderBase::~RenderBase()
{
}

void RenderBase::Draw(MaterialBase& mate, CbMatrix& cbMat)
{
	// �O���t�B�b�N�p�C�v���C�����Z�b�g
	dx12_.CmdLlist()->SetPipelineState(pipeline_.Get());

	// ���[�g�V�O�l�`�����Z�b�g
	dx12_.CmdLlist()->SetGraphicsRootSignature(rootSignature_.Get());

	// �v���~�e�B�u�g�|���W�[���Z�b�g
	dx12_.CmdLlist()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ���_���Z�b�g
	dx12_.CmdLlist()->IASetVertexBuffers(0, 1, &mate.GetMesh()->GetVertexBufferView());

	ID3D12DescriptorHeap* cbmatDh[]{ cbMat.DescriptorHeap().Get() };
	dx12_.CmdLlist()->SetDescriptorHeaps(1, cbmatDh);
	dx12_.CmdLlist()->SetGraphicsRootDescriptorTable(0, cbMat.DescriptorHeap()->GetGPUDescriptorHandleForHeapStart());

	ID3D12DescriptorHeap* transDh[]{ mate.GetTransform()->DescriptorHeap().Get() };
	dx12_.CmdLlist()->SetDescriptorHeaps(1, transDh);
	dx12_.CmdLlist()->SetGraphicsRootDescriptorTable(1, mate.GetTransform()->DescriptorHeap()->GetGPUDescriptorHandleForHeapStart());

	// �V�F�[�_�ɒ萔�o�b�t�@��e�N�X�`�����̃��\�[�X���Z�b�g����
	int  pramIdx{ 2 };
	for (auto& r : mate.GetShaderResource())
	{
		if (r.expired())
		{
			continue;
		}
		ID3D12DescriptorHeap* dh[]{ r.lock()->DescriptorHeap().Get() };
		dx12_.CmdLlist()->SetDescriptorHeaps(1, dh);
		dx12_.CmdLlist()->SetGraphicsRootDescriptorTable(pramIdx , r.lock()->DescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
		pramIdx++;
	}

	// �`�悷��
	dx12_.CmdLlist()->DrawInstanced(static_cast<UINT>(mate.GetMesh()->GetVertexSize()), 1, 0, 0);
}
