#pragma once
#include <concepts>
#include <d3dx12.h>
#include <d3d12.h>
#include "../../GameSystem.h"
#include "../../Dx12Wrapper.h"
#include "Dx12Resource.h"

#include "../../../common/Debug.h"

// 定数バッファ用コンセプト
template<class T>
concept CbC = std::integral<T> || std::floating_point<T>;

// 定数バッファ用クラス
template<CbC T>
class ConstantResource :
	public Dx12Resource
{
public:
	ConstantResource();
	~ConstantResource();
	bool CreateView(void) override;
	bool CreateResource(D3D12_RESOURCE_DESC& resourceDesc) override;
protected:
	T* mapped_;
	std::size_t size_;
};

template<CbC T>
inline ConstantResource<T>::ConstantResource()
{
	D3D12_RESOURCE_DESC resDesc{ CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD) };
	if (!(CreateResource(resDesc)))
	{
		DebugLog("リソースの生成に失敗しました");
		return;
	}

}

template<CbC T>
inline ConstantResource<T>::~ConstantResource()
{
}

template<CbC T>
inline bool ConstantResource<T>::CreateView(void)
{
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
	cbvDesc.BufferLocation = worldBuff_->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = static_cast<UINT>(size_);
	GameSys.GetDx12().Device()->CreateConstantBufferView(&cbvDesc, resource_->GetCPUDescriptorHandleForHeapStart());
	return true;
}

template<CbC T>
inline bool ConstantResource<T>::CreateResource(D3D12_RESOURCE_DESC& resourceDesc)
{
	size_ = sizeof(T);
	size_ = (buffSize + 0xff) & ~0xff;
	auto resDesc = CD3DX12_RESOURCE_DESC::Buffer(size_);

	if (FAILED(GameSys.GetDx12().Device()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(resource_.ReleaseAndGetAddressOf())
	)))
	{
		return false;
	}

	if (FAILED(resource_->Map(0, nullptr, (void**)&mapped_)))
	{
		return false;
	}
	return true;
}

