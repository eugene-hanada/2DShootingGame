#pragma once
#include "RenderBase.h"

// alphaƒuƒŒƒ“ƒh”Å
class AlphaRender :
	public RenderBase
{
public:
	AlphaRender(ComPtr<ID3DBlob>& vs, ComPtr<ID3DBlob>& ps, Dx12Wrapper& dx12);
	~AlphaRender();
private:
	bool CreatePipelineState(ComPtr<ID3DBlob>& vs, ComPtr<ID3DBlob>& ps);
	bool CreateRootSignature(void);
};

