#include <list>
#include <string>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dx12.h>
#include "Window.h"
#include "Dx12/Resource/CbMatrix.h"
#include "Dx12Wrapper.h"

#include "../common/Debug.h"

Dx12Wrapper::Dx12Wrapper(Window& wnd)
{
	SetClearRenderTarget(1.0f, 1.0f, 1.0f, 1.0f);
	
	if (!CreateDXGIDevice())
	{
		DebugLog("�f�o�C�X�̐����Ɏ��s");
		assert(false);
	}
	DebugLog("�f�o�C�X�̐����ɐ���");

	if (FAILED(device_->CreateFence(fenceVal_, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence_.ReleaseAndGetAddressOf()))))
	{
		DebugLog("�t�F���X�����Ɏ��s");
		assert(false);
	}
	DebugLog("�t�F���X�����ɐ���");


	if (!CreateCommand())
	{
		DebugLog("�R�}���h�����Ɏ��s");
		assert(false);
	}
	DebugLog("�R�}���h�����ɐ���");

	if (!CreateSwapChain(wnd))
	{
		DebugLog("�X���b�v�`�F�C���̐����Ɏ��s");
		assert(false);
	}
	DebugLog("�X���b�v�`�F�C�������ɐ���");

	if (!CreateFinalRenderTarget())
	{
		assert(false);
	}


	cbMat_ = std::make_unique<CbMatrix>(*this);
	cbMat_->mat_.m[0][0] = 2.0f / wnd.GetSize<float>().x;
	cbMat_->mat_.m[1][1] = -2.0f / wnd.GetSize<float>().y;
	cbMat_->mat_.m[3][0] = -1.0f;
	cbMat_->mat_.m[3][1] = 1.0f;
	cbMat_->Update();
}

Dx12Wrapper::~Dx12Wrapper()
{
}

void Dx12Wrapper::BeginFinalRenderTarget(void)
{
	// �o�b�N�o�b�t�@�̃C���f�b�N�X���擾
	auto bbIdx = swapChain_->GetCurrentBackBufferIndex();
	// ���\�[�X�o���A�̐ݒ�
	auto barrierDesc = CD3DX12_RESOURCE_BARRIER::Transition(backBuffers_[bbIdx].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	cmdList_->ResourceBarrier(1, &barrierDesc);

	// �����_�[�^�[�Q�b�g���w�肷��
	// �n���h�����擾
	auto rtvH = rtvHeap_->GetCPUDescriptorHandleForHeapStart();
	// 1�̃o�b�t�@�̕��ɐi�߂�
	rtvH.ptr += static_cast<ULONG_PTR>(bbIdx) * static_cast<ULONG_PTR>(device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));


	// ��ʂ��N���A�ɂ���
	cmdList_->ClearRenderTargetView(rtvH, clearColor_, 0, nullptr);

	cmdList_->OMSetRenderTargets(1, &rtvH, false, nullptr);

	// �r���[�|�[�g�ƃV�U�[��`���Z�b�g
	cmdList_->RSSetViewports(1, viewPort_.get());
	cmdList_->RSSetScissorRects(1, scissorRect_.get());
	
}

void Dx12Wrapper::EndFinalRenderTarget(void)
{
	// �o���A������
	auto bbIdx = swapChain_->GetCurrentBackBufferIndex();
	auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(backBuffers_[bbIdx].Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	cmdList_->ResourceBarrier(1, &barrier);
}

void Dx12Wrapper::DrawFinalRenderTarget(void)
{

	// �R�}���h���X�g�̖��߂����s���邽�߂ɃN���[�Y
	auto result = cmdList_->Close();

	// �R�}���h���X�g�̖��߂����s
	ID3D12CommandList* cmdLists[]{ cmdList_.Get() };
	cmdQueue_->ExecuteCommandLists(1, cmdLists);

	// �҂���
	// �t�F���X�l���擾
	result = cmdQueue_->Signal(fence_.Get(), ++fenceVal_);
	if (fence_->GetCompletedValue() < fenceVal_)
	{
		// �C�x���g���擾
		auto ev = CreateEvent(nullptr, false, false, nullptr);

		// �C�x���g���Z�b�g
		fence_->SetEventOnCompletion(fenceVal_, ev);

		// �C�x���g����������܂ő҂�
		WaitForSingleObject(ev, INFINITE);

		// �C�x���g�����
		CloseHandle(ev);
	}

	// �R�}���h�L���[�ƃR�}���h���X�g�̖��߂̍Ď󂯓��ꏈ��
	cmdAllocator_->Reset();
	cmdList_->Reset(cmdAllocator_.Get(), nullptr);

	swapChain_->Present(1, 0);
}

bool Dx12Wrapper::CreateDXGIDevice(void)
{
	UINT flagsDXGI = 0;

#ifdef _DEBUG
	flagsDXGI |= DXGI_CREATE_FACTORY_DEBUG;
#endif

	if (FAILED(CreateDXGIFactory2(flagsDXGI, IID_PPV_ARGS(dxgiFactory_.ReleaseAndGetAddressOf()))))
	{
		DebugLog("DXGIFactory2�̐����Ɏ��s");
		return false;
	}
	DebugLog("DXGIFactory2�̐����ɐ���");

	// �A�_�v�^�[�̗񋓗p
	std::list<IDXGIAdapter*> adapters;

	// �ړI�̖��O�̃A�_�v�^�[������
	IDXGIAdapter* tmpAdapter = nullptr;

	// �A�_�v�^�[���i�[���Ă�
	for (int i = 0; dxgiFactory_->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; i++)
	{
		adapters.push_back(tmpAdapter);
	}

	// �i�[�����A�_�v�^�[�̒�����ړI�̖��O�̃A�_�v�^�[��T��
	std::wstring strDesc;
	tmpAdapter = *adapters.begin();
	for (auto& adpt : adapters)
	{
		DXGI_ADAPTER_DESC adesc{};
		adpt->GetDesc(&adesc);			// �A�_�v�^�[�̐����I�u�W�F�N�g���擾����
		strDesc = adesc.Description;
		if (strDesc.find(L"NVIDIA") != std::string::npos)
		{
			// ��v�����甲����
			tmpAdapter = adpt;
			break;
		}
	}

	// �t���[�`���[���x���̔z��
	D3D_FEATURE_LEVEL levels[]{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};
	D3D_FEATURE_LEVEL fLavel;

	
	
	for (auto& level : levels)
	{
		if (SUCCEEDED(D3D12CreateDevice(tmpAdapter, level, IID_PPV_ARGS(device_.ReleaseAndGetAddressOf()))))
		{
			// �����������߂�
			fLavel = level;
			DebugLog("Device�̐����ɐ���");
			device_->SetName(TEXT("Device"));
			return true;
		}
	}
	DebugLog("Device�̐����Ɏ��s");
	return false;
}

bool Dx12Wrapper::CreateCommand(void)
{
	// �R�}���h�A���P�[�^�[���쐬
	if (FAILED(device_->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(cmdAllocator_.ReleaseAndGetAddressOf())
	))
		)
	{
		DebugLog("�R�}���h�A���P�[�^�[�̐����Ɏ��s");
		return false;
	}
	DebugLog("�R�}���h�A���P�[�^�[�̐����ɐ���");
	//cmdAllocator_->SetName(TEXT("CommandAllocator"));

	// �R�}���h���X�g���쐬
	if (FAILED(device_->CreateCommandList(
		0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator_.Get(), nullptr, IID_PPV_ARGS(cmdList_.ReleaseAndGetAddressOf())
	)))
	{
		DebugLog("�R�}���h���X�g�̐����Ɏ��s");
		return false;
	}
	DebugLog("�R�}���h���X�g�̐����ɐ���");

	// cmdAllocator_->SetName(TEXT("CommandList"));

	// �ݒ��DESC�\���̂ōs��
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc{};

	// �^�C���A�E�g�̐ݒ�(�����ɂ���)
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	// �A�_�v�^�[�̐ݒ�(������g��Ȃ��Ƃ���0�ł���)
	cmdQueueDesc.NodeMask = 0;

	// �v���C�I���e�B���ɐݒ�Ȃ�
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;

	// �����̓R�}���h���X�g�ƍ��킹��
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	// �L���[�𐶐�
	if (FAILED(device_->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(cmdQueue_.ReleaseAndGetAddressOf()))))
	{
		DebugLog("�R�}���h�L���[�̐����Ɏ��s");
		return false;
	}
	DebugLog("�R�}���h�L���[�̐����ɐ���");
	return true;
}

bool Dx12Wrapper::CreateSwapChain(Window& wnd)
{
	// �ݒ�p��DESC
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc{};

	// ��
	swapchainDesc.Width = wnd.GetSize<UINT>().x;

	// ����
	swapchainDesc.Height = wnd.GetSize<UINT>().y;

	// �s�N�Z���t�H�[�}�b�g
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// �X�e���I�\���t���O
	swapchainDesc.Stereo = false;

	// �}���`�T���v���̎w��(Count��1, Quality��0�ł悢)
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;

	// DXGI_USAGE_BACK_BUFFER����܂܂ł悩
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// �o�b�t�@�[�̐��_�u���o�b�t�@-�Ȃ̂�2
	swapchainDesc.BufferCount = 2;

	// �o�b�N�o�b�t�@-�͐L�яk�݂ł���悤�ɐݒ�
	swapchainDesc.Scaling = DXGI_SCALING_STRETCH;

	// �t���b�v��ɂ����ɔj������悤�ɐݒ�
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	// ���Ɏw�肵�Ȃ��̂�DXGI_ALPHA_MODE_UNSPECIFIED��
	swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

	// �t���X�N���[��-�E�B���h�E�̐؂�ւ��\�ɐݒ�
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


	// �X���b�v�`�F�C���̐���
	IDXGISwapChain1* swapchain = nullptr;

	if (FAILED(dxgiFactory_->CreateSwapChainForHwnd(cmdQueue_.Get(), wnd.GetWndHandle(), &swapchainDesc, nullptr, nullptr, &swapchain)))
	{
		DebugLog("�X���b�v�`�F�C���̐����Ɏ��s");
		return false;
	}
	if (FAILED(swapchain->QueryInterface(IID_PPV_ARGS(swapChain_.ReleaseAndGetAddressOf()))))
	{
		DebugLog("�X���b�v�`�F�C���̐����Ɏ��s");
		return false;
	}
	DebugLog("�X���b�v�`�F�C���̐����ɐ���");
	return true;
}

bool Dx12Wrapper::CreateFinalRenderTarget(void)
{
	// �ݒ�pDESC
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};

	// �����_�[�r���[�^�[�Q�b�g�r���[�Ȃ̂�RTV��ݒ�
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

	// ������GPU���g���Ƃ��p�Ȃ̂�0��
	heapDesc.NodeMask = 0;

	// �f�B�X�N���v�^�̐���\���̂Ń_�u���o�b�t�@�[�ɂ���̂�2�ɂ���
	heapDesc.NumDescriptors = 2;

	// �e�N�X�`���o�b�t�@�[��萔�o�b�t�@�[���g���͂Ȃ��̂�NONE��
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	// �f�B�X�N���v�^�q�[�v�𐶐�
	if (FAILED(device_->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(rtvHeap_.ReleaseAndGetAddressOf()))))
	{
		DebugLog("�����_�[�^�[�Q�b�g�p�f�X�N���v�^�q�[�v�̐����Ɏ��s");
		return false;
	}
	//rtvHeap_->SetName(TEXT("RenderTargetHeap"));

	// �X���b�v�`�F�C���ƕR�Â�����
	DXGI_SWAP_CHAIN_DESC1 swcDesc{};

	if (FAILED(swapChain_->GetDesc1(&swcDesc)))
	{
		DebugLog("�X���b�v�`�F�C���̏��擾�Ɏ��s");
		return false;
	}

	backBuffers_.resize(swcDesc.BufferCount);

	// �擪�̃|�C���^���擾
	D3D12_CPU_DESCRIPTOR_HANDLE handle = rtvHeap_->GetCPUDescriptorHandleForHeapStart();

	// SRGB�p�̃����_�[�^�[�Q�b�g�r���[�ݒ�
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	// rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	for (unsigned int i = 0; i < swcDesc.BufferCount; i++)
	{
		if (FAILED(swapChain_->GetBuffer(static_cast<UINT>(i), IID_PPV_ARGS(backBuffers_[i].ReleaseAndGetAddressOf()))))
		{
			DebugLog("�X���b�v�`�F�C���̃o�b�t�@�[�擾�Ɏ��s");
			return false;
		}

		// �����_�[�r���[�^�[�Q�b�g�ɐݒ�
		device_->CreateRenderTargetView(backBuffers_[i].Get(), &rtvDesc, handle);

		// �|�C���^�����炷
		handle.ptr += device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	}

	viewPort_ = std::make_unique<CD3DX12_VIEWPORT>(backBuffers_[0].Get());
	scissorRect_ = std::make_unique<CD3DX12_RECT>(0, 0, swcDesc.Width, swcDesc.Height);
	DebugLog("�t�@�C�i�������_�[�^�[�Q�b�g�̐����ɐ���");
	return true;
}
