#pragma once
#include <wrl.h>
struct ID3D12Resource;
struct ID3D12DescriptorHeap;
struct D3D12_RESOURCE_DESC;

class Dx12Wrapper;

class Dx12Resource
{
protected:
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Dx12Resource(Dx12Wrapper& dx12);
	virtual ~Dx12Resource();
	ComPtr<ID3D12DescriptorHeap>& DescriptorHeap(void)
	{
		return descriptorHeap_;
	}
	ComPtr<ID3D12Resource>& GetResource(void) { return resource_; }
private:
	
	virtual bool CreateView(Dx12Wrapper& dx12) = 0;
	virtual bool CreateResource(Dx12Wrapper& dx12,D3D12_RESOURCE_DESC&  resourceDesc) = 0;
protected:
	bool CreateDescriptorHeap(Dx12Wrapper& dx12);
	ComPtr<ID3D12Resource> resource_;
	ComPtr<ID3D12DescriptorHeap> descriptorHeap_;
};

