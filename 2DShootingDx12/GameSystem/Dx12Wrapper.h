#pragma once
#include <vector>
#include <wrl.h>
#include <memory>

struct ID3D12Device;
struct IDXGIFactory6;
struct IDXGISwapChain4;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;
struct ID3D12CommandQueue;
struct ID3D12Resource;
struct ID3D12Fence;
struct ID3D12DescriptorHeap;
struct CD3DX12_VIEWPORT;
struct CD3DX12_RECT;

class Window;
class CbMatrix;

// directX12�̃��b�v�N���X
class Dx12Wrapper
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Dx12Wrapper(Window& wnd);
	~Dx12Wrapper();

	/// <summary>
	/// �Ō�̃����_�[�^�[�Q�b�g�ɕ`��J�n����
	/// </summary>
	/// <param name=""></param>
	void BeginFinalRenderTarget(void);

	/// <summary>
	/// �Ō�̃����_�[�^�[�Q�b�g�̕`�揈�����I������
	/// </summary>
	/// <param name=""></param>
	void EndFinalRenderTarget(void);

	/// <summary>
	/// �Ō�̃����_�[�^�[�Q�b�g��`�悷��
	/// </summary>
	/// <param name=""></param>
	void DrawFinalRenderTarget(void);

	// �N���A�J���[���Z�b�g����
	void SetClearRenderTarget(float r, float g, float b, float a)
	{
		clearColor_[0] = r;
		clearColor_[1] = g;
		clearColor_[2] = b;
		clearColor_[3] = a;
	}

	/// <summary>
	/// �f�o�C�X�̎擾
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	ComPtr<ID3D12Device>& Device(void)
	{
		return device_;
	}

	/// <summary>
	/// �R�}���h���X�g�̎擾
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	ComPtr<ID3D12GraphicsCommandList>& CmdLlist(void)
	{
		return cmdList_;
	}

	/// <summary>
	/// �s��̎擾
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	CbMatrix& GetCbMat(void) { return *cbMat_; }

private:

	/// <summary>
	/// �f�o�C�X�̐���
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool CreateDXGIDevice(void);

	/// <summary>
	/// �R�}���h�ނ̐���
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool CreateCommand(void);

	/// <summary>
	/// �X���b�v�`�F�C���̐���
	/// </summary>
	/// <param name="wnd"></param>
	/// <returns></returns>
	bool CreateSwapChain(Window& wnd);

	/// <summary>
	/// �����_�[�^�[�Q�b�g�̐���
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool CreateFinalRenderTarget(void);

	// �f�o�C�X
	ComPtr<ID3D12Device> device_{ nullptr };

	// �R�}���h�A���P�[�^�[
	ComPtr<ID3D12CommandAllocator> cmdAllocator_{ nullptr };

	// �R�}���h���X�g
	ComPtr<ID3D12GraphicsCommandList> cmdList_{ nullptr };

	// �R�}���h�L���[
	ComPtr<ID3D12CommandQueue> cmdQueue_{ nullptr };

	// DXGI����----------------------------------------
	// DXGI�t�@�N�g���[
	ComPtr<IDXGIFactory6> dxgiFactory_{ nullptr };

	// �X���b�v�`�F�C��
	ComPtr<IDXGISwapChain4> swapChain_{ nullptr };

	// �\���֘A�̃o�b�t�@����----------------------
	// �o�b�N�o�b�t�@
	std::vector<ComPtr<ID3D12Resource>> backBuffers_;

	// �����_�[�^�[�Q�b�g�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> rtvHeap_{ nullptr };

	// �t�F���X�̒l
	std::uint64_t fenceVal_{ 0 };
	
	// �t�F���X
	ComPtr<ID3D12Fence> fence_{ nullptr };

	// �r���[�|�[�g
	std::unique_ptr<CD3DX12_VIEWPORT> viewPort_;

	// �V�U�[��`
	std::unique_ptr< CD3DX12_RECT> scissorRect_;

	// �N���A�J���[
	float clearColor_[4];

	// �s��
	std::unique_ptr<CbMatrix> cbMat_;
};

