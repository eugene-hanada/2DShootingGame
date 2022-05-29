#include <d3dx12.h>
#include <d3d12.h>
#include "../../Dx12Wrapper.h"
#include "../../../common/Debug.h"
#include "Mesh.h"

Mesh::Mesh(Dx12Wrapper& dx12, const Math::Vector2& size)
{
	vertices_.fill(Vertex{ {0.0f,0.0f}, {0.0f, 0.0f} });
	vertices_[1].pos.x = size.x;
	vertices_[1].uv.x =1.0f;
	vertices_[2].pos.y= size.y;
	vertices_[2].uv.y = 1.0f;
	vertices_[3].pos = { size.x , size.y};
	vertices_[3].uv = { 1.0f, 1.0f };
	
	if (!CreateVertex(dx12))
	{
		DebugLog("頂点情報の生成に失敗");
		assert(false);
	}
}

bool Mesh::SetVertex(const std::array<Vertex, 4>&vertices)
{
	vertices_ = vertices;
	Vertex* vertMap{ nullptr };
	if (vResource_->Map(0, nullptr, (void**)&vertMap) != S_OK)
	{
		return false;
	}
	std::copy(vertices_.begin(), vertices_.end(), vertMap);
	vResource_->Unmap(0, nullptr);
	return true;
}

bool Mesh::CreateVertex(Dx12Wrapper& dx12)
{
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto vrResDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices_[0]) * vertices_.size());

	// リソース生成
	if (dx12.Device()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&vrResDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(vResource_.ReleaseAndGetAddressOf())) != S_OK)
	{
		return false;
	}

	// 頂点情報のコピー
	Vertex* vertMap{ nullptr };
	if (vResource_->Map(0, nullptr, (void**)&vertMap) != S_OK)
	{
		return false;
	}
	std::copy(vertices_.begin(), vertices_.end(), vertMap);
	vResource_->Unmap(0, nullptr);

	// 頂点バッファービューの作成
	vbView_ = std::make_unique<D3D12_VERTEX_BUFFER_VIEW>();
	vbView_->BufferLocation = vResource_->GetGPUVirtualAddress();		// バッファの仮想アドレスを入れる
	vbView_->SizeInBytes = static_cast<UINT>(sizeof(vertices_[0]) * vertices_.size());		// 総バイト数
	vbView_->StrideInBytes = sizeof(Vertex);		// 1t頂点当たりのバイト数
	return true;
}
