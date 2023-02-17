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

// �����_�[�^�[�Q�b�g�̃N���X
class RenderTarget
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	RenderTarget(Dx12Wrapper& dx12,const Math::Vector2& size);
	~RenderTarget();

	// �������p�̃J���[���Z�b�g
	void SetClearColor(float r, float g, float b, float a)
	{
		color_[0] = r;
		color_[1] = g;
		color_[2] = b;
		color_[3] = a;
	}

	/// <summary>
	/// �`��J�n
	/// </summary>
	/// <param name=""></param>
	void DrawBegin(void);

	/// <summary>
	/// �`��I��
	/// </summary>
	/// <param name=""></param>
	void DrawEnd(void);

	/// <summary>
	/// �N���A
	/// </summary>
	/// <param name=""></param>
	void Clear(void);

	/// <summary>
	/// �}�e���A���̎擾
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	MaterialBase& GetMaterial(void) { return *material_; }

	/// <summary>
	/// �ϊ��p�s��̎擾
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	CbMatrix& GetCbMat(void) { return *cbMat_; }
private:
	
	/// <summary>
	/// �����_�[�^�[�Q�b�g�̍쐬
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool CreateRenderTarget(void);


	// directX�̃��b�v�N���X
	Dx12Wrapper& dx12_;

	// �����_�[�^�[�Q�b�g�̃T�C�Y(�����ƕ�)
	Math::Vector2 size_;

	//// ���b�V��
	//std::unique_ptr<Mesh> mesh_;

	// �X�N���[����̍��W����V�F�[�_�p�ɕϊ�����s��
	std::unique_ptr<CbMatrix> cbMat_;

	// �N���A���̃J���[
	float color_[4]{0.0f,0.0f,0.0f,0.0f};

	//// ���\�[�X
	//ComPtr<ID3D12Resource> resource_;

	// �����_�[�^�[�Q�b�g�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> rtDescriptorHeap_;

	// �}�e���A��
	std::unique_ptr<MaterialBase> material_;

	// �e�N�X�`��
	std::shared_ptr<Texture> texure_;

	// �r���[�|�[�g
	std::unique_ptr<CD3DX12_VIEWPORT> viewPort_;

	// �V�U�[��`
	std::unique_ptr<CD3DX12_RECT> scissorRect_;
};

