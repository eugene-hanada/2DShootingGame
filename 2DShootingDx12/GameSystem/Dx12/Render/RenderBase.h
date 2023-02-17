#pragma once
#include <wrl.h>

class Dx12Wrapper;
struct ID3D12PipelineState;
struct ID3D12RootSignature;
class MaterialBase;
class CbMatrix;

// directX12のパイプラインステートとルードシグネチャをまとめたクラス
class RenderBase
{
public:
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
	RenderBase(Dx12Wrapper& dx12);
	virtual ~RenderBase();
	void Draw(MaterialBase& mate, CbMatrix& cbMat);
	ComPtr<ID3D12PipelineState>& GetPipelineState(void) { return pipeline_; }
	ComPtr<ID3D12RootSignature>& GetRootSignature(void) { return rootSignature_; }
protected:
	virtual bool CreatePipelineState(ComPtr<ID3DBlob>& vs, ComPtr<ID3DBlob>& ps) = 0;
	virtual bool CreateRootSignature(void) = 0;
	
	// DirectX12のラッパークラス
	Dx12Wrapper& dx12_;

	// パイプライン
	ComPtr<ID3D12PipelineState> pipeline_{ nullptr };


	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature_{ nullptr };

};

