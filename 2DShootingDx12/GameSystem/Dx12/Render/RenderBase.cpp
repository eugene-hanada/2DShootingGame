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
	// グラフィックパイプラインをセット
	dx12_.CmdLlist()->SetPipelineState(pipeline_.Get());

	// ルートシグネチャをセット
	dx12_.CmdLlist()->SetGraphicsRootSignature(rootSignature_.Get());

	// プリミティブトポロジーをセット
	dx12_.CmdLlist()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// 頂点をセット
	dx12_.CmdLlist()->IASetVertexBuffers(0, 1, &mate.GetMesh()->GetVertexBufferView());

	ID3D12DescriptorHeap* cbmatDh[]{ cbMat.DescriptorHeap().Get() };
	dx12_.CmdLlist()->SetDescriptorHeaps(1, cbmatDh);
	dx12_.CmdLlist()->SetGraphicsRootDescriptorTable(0, cbMat.DescriptorHeap()->GetGPUDescriptorHandleForHeapStart());

	ID3D12DescriptorHeap* transDh[]{ mate.GetTransform()->DescriptorHeap().Get() };
	dx12_.CmdLlist()->SetDescriptorHeaps(1, transDh);
	dx12_.CmdLlist()->SetGraphicsRootDescriptorTable(1, mate.GetTransform()->DescriptorHeap()->GetGPUDescriptorHandleForHeapStart());

	// シェーダに定数バッファやテクスチャ等のリソースをセットする
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

	// 描画する
	dx12_.CmdLlist()->DrawInstanced(static_cast<UINT>(mate.GetMesh()->GetVertexSize()), 1, 0, 0);
}
