#pragma once
#include "RenderBase.h"

class AlphaRender :
	public RenderBase
{
public:
	AlphaRender(Dx12Wrapper& dx12);
	~AlphaRender();
private:
	bool CreatePipelineState(void);
	bool CreateRootSignature(void);
};

