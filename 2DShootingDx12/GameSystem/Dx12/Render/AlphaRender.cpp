#include <d3dx12.h>
#include <d3dcompiler.h>
#include "../../Dx12Wrapper.h"
#include "../../../common/Debug.h"
#include "AlphaRender.h"

AlphaRender::AlphaRender(Dx12Wrapper& dx12) :
	RenderBase{dx12}
{
	if (!CreateRootSignature())
	{
		assert(false);
	}
	if (!CreatePipelineState())
	{
		assert(false);
	}
}

AlphaRender::~AlphaRender()
{
}

bool AlphaRender::CreatePipelineState(void)
{
	// �V�F�[�_�̐ݒ�
	RenderBase::ComPtr<ID3DBlob> vsBlob{ nullptr };
	RenderBase::ComPtr<ID3DBlob> psBlob{ nullptr };
	RenderBase::ComPtr<ID3DBlob> errorBlob{ nullptr };

	auto flag = D3DCOMPILE_SKIP_OPTIMIZATION;
#ifdef _DEBUG
	flag |= D3DCOMPILE_DEBUG;
#endif

	HRESULT result = D3DCompileFromFile(
		L"Resource/shader/Basic2DVs.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"vs_5_0",
		flag,
		0,
		&vsBlob,
		&errorBlob);
	if (FAILED(result))
	{
		DebugLog("���_�V�F�[�_�̃R���p�C���Ɏ��s");
		return false;
	}

	result = D3DCompileFromFile(
		L"Resource/shader/Basic2DPs.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"ps_5_0",
		flag,
		0,
		&psBlob,
		&errorBlob
	);
	if (FAILED(result))
	{
		DebugLog("�s�N�Z���V�F�[�_�̃R���p�C���Ɏ��s");
		return false;
	}

	// �V�F�[�_�̃C���v�b�g���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{	// ���W���
			"POSITION",		// �Z�}���e�B�N�X���@���W���Ȃ̂�POSITION
			0,			// �����Z�}���e�B�N�X���̎��Ɏg���̂�0�ł悢
			DXGI_FORMAT_R32G32_FLOAT,	// �t�H�[�}�b�g
			0,		// ���̓X���b�g�C���f�b�N�X
			D3D12_APPEND_ALIGNED_ELEMENT,		// �f�[�^�̃I�t�Z�b�g�ʒu����ł悢
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		// ����ł悢
			0		// ��x�ɕ`�悷��C���X�^���X�̐��Ȃ̂�0
		},
		{	// uv���
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
	};

	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	// ���[�g�V�O�l�`�����Z�b�g
	gpipeline.pRootSignature = rootSignature_.Get();

	// �V�F�[�_���Z�b�g
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	// �f�t�H���g�̃T���v���}�X�N
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	// ���X�^���C�U����̐ݒ�
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;

	// �[�x�X�e���V���̐ݒ�
	gpipeline.DepthStencilState.DepthEnable = false;
	gpipeline.DepthStencilState.StencilEnable = false;


	// �u�����h�ݒ�n
	gpipeline.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	gpipeline.BlendState.RenderTarget[0].BlendEnable = true;
	gpipeline.BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	gpipeline.BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	gpipeline.BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

	// ���̓��C�A�E�g��ݒ�
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	// �|���S���̕\���ɂ��Ă̐ݒ�
	gpipeline.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;		// �C���f�b�N�X�o�b�t�@���g��
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;		// �O�p�`��\��
	gpipeline.NumRenderTargets = 1;		// ���͈�Ȃ̂�
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;		// ���K�����ꂽRGBA��n��

	// �A���`�G�C���A�V���O�Ɋւ���ݒ�
	gpipeline.SampleDesc.Count = 1;
	gpipeline.SampleDesc.Quality = 0;

	if (FAILED(dx12_.Device()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(pipeline_.ReleaseAndGetAddressOf()))))
	{
		DebugLog("�O���t�B�b�N�p�C�v���C���̐����Ɏ��s");
		return false;
	}
	return true;
}

bool AlphaRender::CreateRootSignature(void)
{
	// �f�B�X�N���v�^�����W
	CD3DX12_DESCRIPTOR_RANGE descTblRange[4] = {};

	// �ϊ��p�s��(b0�X���b�g)
	descTblRange[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);

	// �ό`�p�s��(b1�X���b�g)
	descTblRange[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1);

	// �e�N�X�`���p(t0)
	descTblRange[2].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

	// ���l�ύX�p(b1�X���b�g)
	descTblRange[3].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 2);

	// ���[�g�p�����[�^�[
	CD3DX12_ROOT_PARAMETER rootparam[4]{};
	rootparam[0].InitAsDescriptorTable(1, &descTblRange[0]);
	rootparam[1].InitAsDescriptorTable(1, &descTblRange[1]);
	rootparam[2].InitAsDescriptorTable(1, &descTblRange[2]);
	rootparam[3].InitAsDescriptorTable(1, &descTblRange[3]);

	// �T���v���[�ݒ�
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc[1]{};
	samplerDesc[0].Init(0);


	CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	rootSignatureDesc.Init(static_cast<UINT>(std::size(rootparam)), rootparam, static_cast<UINT>(std::size(samplerDesc)), samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	if (FAILED(D3D12SerializeRootSignature(
		&rootSignatureDesc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&rootSigBlob,
		&errorBlob)
	))
	{
		DebugLog("���[�g�V�O�l�`���̃V���A���C�Y�Ɏ��s");
		return false;
	}
	if (FAILED(dx12_.Device()->CreateRootSignature(
		0,
		rootSigBlob->GetBufferPointer(),
		rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(rootSignature_.ReleaseAndGetAddressOf())))
		)
	{
		DebugLog("���[�g�V�O�l�`���̐����Ɏ��s");
		return false;
	}

	return true;
}
