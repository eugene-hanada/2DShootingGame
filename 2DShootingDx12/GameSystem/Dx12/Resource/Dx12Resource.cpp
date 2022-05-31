#include <d3d12.h>
#include "../../Dx12Wrapper.h"
#include "Dx12Resource.h"

#include "../../../common/Debug.h"

Dx12Resource::Dx12Resource(Dx12Wrapper& dx12)
{
	if (!CreateDescriptorHeap(dx12))
	{
		DebugLog("デスクリプタヒープの生成に失敗");
		Assert(false, "デスクリプタヒープの生成に失敗");
	}
}

Dx12Resource::~Dx12Resource()
{
}

bool Dx12Resource::CreateDescriptorHeap(Dx12Wrapper& dx12)
{
	D3D12_DESCRIPTOR_HEAP_DESC descHDesc{};
	descHDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	descHDesc.NodeMask = 0;
	descHDesc.NumDescriptors = 1;
	descHDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	if (FAILED(dx12.Device()->CreateDescriptorHeap(&descHDesc, IID_PPV_ARGS(descriptorHeap_.ReleaseAndGetAddressOf()))))
	{
		return false;
	}
	return true;

}
