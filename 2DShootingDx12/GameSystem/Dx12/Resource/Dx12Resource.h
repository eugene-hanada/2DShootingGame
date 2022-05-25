#pragma once
#include <wrl.h>
struct ID3D12Resource;
struct ID3D12DescriptorHeap;
struct D3D12_RESOURCE_DESC;

class Dx12Resource
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Dx12Resource();
	~Dx12Resource();
	ComPtr<ID3D12DescriptorHeap>& DescriptorHeap(void)
	{
		return descriptorHeap_;
	}
private:
	
	virtual bool CreateView(void) = 0;
	virtual bool CreateResource(D3D12_RESOURCE_DESC&  resourceDesc) = 0;
protected:
	bool CreateDescriptorHeap(void);
	ComPtr<ID3D12Resource> resource_;
	ComPtr<ID3D12DescriptorHeap> descriptorHeap_;
};

