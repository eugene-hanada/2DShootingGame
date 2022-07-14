#pragma once
#include <concepts>
#include <d3dx12.h>
#include <d3d12.h>
#include "../../Dx12Wrapper.h"
#include "Dx12Resource.h"

#include "../../../common/Debug.h"

// 定数バッファ用コンセプト
template<class T>
concept CbC = std::integral<T> || std::floating_point<T> || std::is_class_v<T>;

// 定数バッファ用クラス
template<CbC T>
class ConstantResource :
	public Dx12Resource
{
public:
	ConstantResource(Dx12Wrapper& dx12);
	ConstantResource(Dx12Wrapper& dx12, size_t num);
	virtual ~ConstantResource();
	bool CreateView(Dx12Wrapper& dx12) override;
	bool CreateResource(Dx12Wrapper& dx12,D3D12_RESOURCE_DESC& resourceDesc) override;
	virtual void Update(void) = 0;
	
protected:
	T* mapped_;
	std::size_t size_;
};

template<CbC T>
inline ConstantResource<T>::ConstantResource(Dx12Wrapper& dx12) :
	Dx12Resource{ dx12 }, size_{ (sizeof(T) + 0xff) & ~0xff }, mapped_{ nullptr }
{
	if (!CreateDescriptorHeap(dx12))
	{
		assert(false);
		return;
	}

	D3D12_RESOURCE_DESC resDesc{ CD3DX12_RESOURCE_DESC::Buffer(size_) };
	if (!(CreateResource(dx12,resDesc)))
	{
		DebugLog("リソースの生成に失敗しました");
		assert(false);
		return;
	}

	if (!CreateView(dx12))
	{
		DebugLog("バッファービューの生成に失敗しました");
		assert(false);
		return;
	}
}

template<CbC T>
inline ConstantResource<T>::ConstantResource(Dx12Wrapper& dx12, size_t num) :
	Dx12Resource{ dx12 }, size{ ((sizeof(T) * num) + 0xff) & ~0xff }, mapped_{ nullptr }
{
	if (!CreateDescriptorHeap(dx12))
	{
		assert(false);
		return;
	}

	D3D12_RESOURCE_DESC resDesc{ CD3DX12_RESOURCE_DESC::Buffer(size_) };
	if (!(CreateResource(dx12, resDesc)))
	{
		DebugLog("リソースの生成に失敗しました");
		assert(false);
		return;
	}

	if (!CreateView(dx12))
	{
		DebugLog("バッファービューの生成に失敗しました");
		assert(false);
		return;
	}
}

template<CbC T>
inline ConstantResource<T>::~ConstantResource()
{
}

template<CbC T>
inline bool ConstantResource<T>::CreateView(Dx12Wrapper& dx12)
{
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
	cbvDesc.BufferLocation = resource_->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = static_cast<UINT>(size_);
	dx12.Device()->CreateConstantBufferView(&cbvDesc, descriptorHeap_->GetCPUDescriptorHandleForHeapStart());
	return true;
}

template<CbC T>
inline bool ConstantResource<T>::CreateResource(Dx12Wrapper& dx12,D3D12_RESOURCE_DESC& resourceDesc)
{
	
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

	if (FAILED(dx12.Device()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
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
	resource_->SetName(TEXT("Resource"));
	return true;
}

