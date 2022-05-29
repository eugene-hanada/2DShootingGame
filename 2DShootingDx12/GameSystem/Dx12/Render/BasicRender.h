#pragma once
#include <wrl.h>

class Dx12Wrapper;
struct ID3D12PipelineState;
struct ID3D12RootSignature;
class MaterialBase;
class CbMatrix;

class BasicRender
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	BasicRender(Dx12Wrapper& dx12);
	~BasicRender();
	void Draw(MaterialBase& mate, CbMatrix& cbMat);
private:

	bool CreatePipelineState(void);
	bool CreateRootSignature(void);

	Dx12Wrapper& dx12_;

	// primitive�p�p�C�v���C��
	ComPtr<ID3D12PipelineState> pipeline_{ nullptr };


	// primitive�p���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature_{ nullptr };
};

