#pragma once
#include <wrl.h>
#include <d3dcommon.h>
#include "RenderBase.h"

class Dx12Wrapper;
struct ID3D12PipelineState;
struct ID3D12RootSignature;
class MaterialBase;
class CbMatrix;

// í èÌî≈
class BasicRender :
	public RenderBase
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	BasicRender(ComPtr<ID3DBlob>& vs, ComPtr<ID3DBlob>& ps,Dx12Wrapper& dx12);
	~BasicRender();
	/*void Draw(MaterialBase& mate, CbMatrix& cbMat);*/
private:

	bool CreatePipelineState(ComPtr<ID3DBlob>& vs, ComPtr<ID3DBlob>& ps);
	bool CreateRootSignature(void);

};

