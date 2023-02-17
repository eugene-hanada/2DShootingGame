#pragma once
#include <wrl.h>
struct ID3D12Resource;
struct ID3D12DescriptorHeap;
struct D3D12_RESOURCE_DESC;

class Dx12Wrapper;

// directX12�n�̃��\�[�X�̊��N���X
class Dx12Resource
{
protected:
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Dx12Resource(Dx12Wrapper& dx12);
	virtual ~Dx12Resource();

	/// <summary>
	/// �f�B�X�N���v�^�q�[�v���擾
	/// </summary>
	/// <param name=""></param>
	/// <returns> �f�B�X�N���v�^�q�[�v���擾 </returns>
	ComPtr<ID3D12DescriptorHeap>& DescriptorHeap(void)
	{
		return descriptorHeap_;
	}

	/// <summary>
	/// ���\�[�X�̎擾
	/// </summary>
	/// <param name=""></param>
	/// <returns> ���\�[�X </returns>
	ComPtr<ID3D12Resource>& GetResource(void) { return resource_; }

private:
	
	/// <summary>
	/// �r���[�̍쐬
	/// </summary>
	/// <param name="dx12"></param>
	/// <returns> ������true�A���s��false </returns>
	virtual bool CreateView(Dx12Wrapper& dx12) = 0;

	/// <summary>
	/// ���\�[�X�̍쐬
	/// </summary>
	/// <param name="dx12"> directX12�̃��b�v�N���X </param>
	/// <param name="resourceDesc"> ���\�[�X�̐ݒ�N���X </param>
	/// <returns></returns>
	virtual bool CreateResource(Dx12Wrapper& dx12,D3D12_RESOURCE_DESC&  resourceDesc) = 0;
protected:
	bool CreateDescriptorHeap(Dx12Wrapper& dx12);

	// ���\�[�X
	ComPtr<ID3D12Resource> resource_;

	// �f�B�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descriptorHeap_;
};

