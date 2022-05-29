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

class Dx12Wrapper
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Dx12Wrapper(Window& wnd);
	~Dx12Wrapper();

	
	void BeginFinalRenderTarget(void);
	void EndFinalRenderTarget(void);
	void DrawFinalRenderTarget(void);

	void SetClearRenderTarget(float r, float g, float b, float a)
	{
		clearColor_[0] = r;
		clearColor_[1] = g;
		clearColor_[2] = b;
		clearColor_[3] = a;
	}

	ComPtr<ID3D12Device>& Device(void)
	{
		return device_;
	}

	ComPtr<ID3D12GraphicsCommandList>& CmdLlist(void)
	{
		return cmdList_;
	}

	CbMatrix& GetCbMat(void) { return *cbMat_; }

private:
	bool CreateDXGIDevice(void);

	bool CreateCommand(void);

	bool CreateSwapChain(Window& wnd);

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

	float clearColor_[4];

	std::unique_ptr<CbMatrix> cbMat_;
};

