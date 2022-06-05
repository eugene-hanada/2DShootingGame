#pragma once
#include <memory>
#include <wrl.h>
#include "../../../common/Math.h"

class Dx12Wrapper;
class CbMatrix;
class MaterialBase;
class Texture;
struct ID3D12Resource;
struct CD3DX12_RECT;
struct CD3DX12_VIEWPORT;
struct ID3D12DescriptorHeap;

class RenderTarget
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	RenderTarget(Dx12Wrapper& dx12,const Math::Vector2& size);
	~RenderTarget();
	void SetClearColor(float r, float g, float b, float a)
	{
		color_[0] = r;
		color_[1] = g;
		color_[2] = b;
		color_[3] = a;
	}

	void DrawBegin(void);
	void DrawEnd(void);
	void Clear(void);

	MaterialBase& GetMaterial(void) { return *material_; }
	CbMatrix& GetCbMat(void) { return *cbMat_; }
private:
	

	bool CreateRenderTarget(void);


	Dx12Wrapper& dx12_;

	// �����_�[�^�[�Q�b�g�̃T�C�Y(�����ƕ�)
	Math::Vector2 size_;

	//// ���b�V��
	//std::unique_ptr<Mesh> mesh_;

	// �X�N���[����̍��W����V�F�[�_�p�ɕϊ�����s��
	std::unique_ptr<CbMatrix> cbMat_;

	float color_[4];

	//// ���\�[�X
	//ComPtr<ID3D12Resource> resource_;

	// �����_�[�^�[�Q�b�g�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> rtDescriptorHeap_;

	std::unique_ptr<MaterialBase> material_;

	std::shared_ptr<Texture> texure_;

	// �r���[�|�[�g
	std::unique_ptr<CD3DX12_VIEWPORT> viewPort_;

	// �V�U�[��`
	std::unique_ptr<CD3DX12_RECT> scissorRect_;
};

