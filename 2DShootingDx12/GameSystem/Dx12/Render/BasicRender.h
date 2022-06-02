#pragma once
#include <wrl.h>
#include "RenderBase.h"

class Dx12Wrapper;
struct ID3D12PipelineState;
struct ID3D12RootSignature;
class MaterialBase;
class CbMatrix;

class BasicRender :
	public RenderBase
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	BasicRender(Dx12Wrapper& dx12);
	~BasicRender();
	/*void Draw(MaterialBase& mate, CbMatrix& cbMat);*/
private:

	bool CreatePipelineState(void);
	bool CreateRootSignature(void);

};

