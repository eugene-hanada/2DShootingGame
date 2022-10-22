#include <d3dx12.h>
#include <d3dcompiler.h>
#include "../../Dx12Wrapper.h"
#include "../../Dx12/Resource/CbMatrices.h"
#include "../../../common/TextureData.h"
#include "../../../common/Debug.h"
#include "../Resource/Texture.h"
#include "../Resource/CbMatrix.h"
#include "TextureSheetRender.h"

#include "../../../common/Debug.h"

TextureSheetRender::TextureSheetRender(const std::string& imgKey, Dx12Wrapper& dx12, std::shared_ptr< TextureData>& texData, std::uint32_t maxNum) :
	dx12_{dx12}, maxNum_{maxNum}, texData_{texData}, imgKey_{imgKey}
{
	mat_ = std::make_unique<CbMatrices>(dx12_, maxNum_);
	
	if (!CreateVertex())
	{
		assert(false);
	}

	if (!CreateIdx())
	{
		assert(false);
	}

	if (!CreateRootSignature())
	{
		assert(false);
	}
	if (!CreatePipeline())
	{
		assert(false);
	}

}

TextureSheetRender::~TextureSheetRender()
{
}

void TextureSheetRender::Draw(const Math::Vector2& pos, const std::string& key,float rot, int idx)
{
	int nowIdx = nowNum_ * 4;
	int idicIdx = nowNum_ * 6;
	auto& [texD, size] = texData_->GetData(imgKey_);
	auto& data = texD.at(key)[idx];

	//DebugLog(data.pos.x, ":", data.pos.y, "a=", idx);
	//DebugLog(idx);

	// ����
	vertices_[nowIdx].pos = 0.0f;
	vertices_[nowIdx].uv = data.pos;
	vertices_[nowIdx].uv /= size;
	vertices_[nowIdx].no = nowNum_;
	idices_[idicIdx] = nowIdx;

	nowIdx++;

	// �E��
	vertices_[nowIdx].pos = 0.0f;
	vertices_[nowIdx].pos.x += data.wh.x;
	vertices_[nowIdx].uv = data.pos;
	vertices_[nowIdx].uv.x += data.wh.x;
	vertices_[nowIdx].uv /= size;
	vertices_[nowIdx].no = nowNum_;
	idices_[idicIdx + 1] = nowIdx;
	idices_[idicIdx + 3] = nowIdx;

	nowIdx++;

	// ����
	vertices_[nowIdx].pos = 0.0f;
	vertices_[nowIdx].pos.y += data.wh.y;
	vertices_[nowIdx].uv = data.pos;
	vertices_[nowIdx].uv.y += data.wh.y;
	vertices_[nowIdx].uv /= size;
	vertices_[nowIdx].no = nowNum_;
	idices_[idicIdx + 2] = nowIdx;
	idices_[idicIdx + 5] = nowIdx;

	nowIdx++;

	// �E��
	vertices_[nowIdx].pos = 0.0f;
	vertices_[nowIdx].pos += data.wh;
	vertices_[nowIdx].uv = data.pos;
	vertices_[nowIdx].uv += data.wh;
	vertices_[nowIdx].uv /= size;
	vertices_[nowIdx].no = nowNum_;
	idices_[idicIdx + 4] = nowIdx;

	DirectX::XMStoreFloat4x4(
		&mat_->matrices_[nowNum_],
		DirectX::XMMatrixTranslation(-(data.wh.x / 2.0f), -(data.wh.y / 2.0f), 0.0f)*
		DirectX::XMMatrixRotationZ(rot) *
		DirectX::XMMatrixTranslation(pos.x, pos.y, 0.0f) 
		
		
	);

	//DirectX::XMStoreFloat4x4(
	//		&mat_->matrices_[nowNum_],
	//		DirectX::XMMatrixTranslation(pos.x, pos.y, 0.0f)*
	//		DirectX::XMMatrixRotationY(rot) *
	//		DirectX::XMMatrixTranslation(-(data.wh.x / 2.0f), -(data.wh.y / 2.0f), 0.0f)
	//		
	//		
	//	);

	
	/*DirectX::XMStoreFloat4x4(
		&mat_->matrices_[nowNum_],
		DirectX::XMMatrixIdentity()
	);*/
	
	nowNum_++;
}

void TextureSheetRender::Draw(const Math::Vector2& lt, const Math::Vector2& rt, const Math::Vector2& lb, const Math::Vector2& rb, const std::string& key, int idx)
{
	auto& [texD, size] = texData_->GetData(imgKey_);
	auto& data = texD.at(key)[idx];
	int nowIdx = nowNum_ * 4;
	int idicIdx = nowNum_ * 6;

	// ����
	vertices_[nowIdx].no = nowNum_;
	vertices_[nowIdx].pos = lt;
	vertices_[nowIdx].uv = data.pos;
	vertices_[nowIdx].uv /= size;
	vertices_[nowIdx].no = nowNum_;
	idices_[idicIdx] = nowIdx;

	nowIdx++;

	// �E��
	vertices_[nowIdx].no = nowNum_;
	vertices_[nowIdx].pos = rt;
	vertices_[nowIdx].uv = data.pos;
	vertices_[nowIdx].uv.x += data.wh.x;
	vertices_[nowIdx].uv /= size;
	vertices_[nowIdx].no = nowNum_;
	idices_[idicIdx + 1] = nowIdx;
	idices_[idicIdx + 3] = nowIdx;

	nowIdx++;

	// ����
	vertices_[nowIdx].no = nowNum_;
	vertices_[nowIdx].pos = lb;
	vertices_[nowIdx].uv = data.pos;
	vertices_[nowIdx].uv.y += data.wh.y;
	vertices_[nowIdx].uv /= size;
	vertices_[nowIdx].no = nowNum_;
	idices_[idicIdx + 2] = nowIdx;
	idices_[idicIdx + 5] = nowIdx;

	nowIdx++;

	// �E��
	vertices_[nowIdx].no = nowNum_;
	vertices_[nowIdx].pos = rb;
	vertices_[nowIdx].uv = data.pos;
	vertices_[nowIdx].uv += data.wh;
	vertices_[nowIdx].uv /= size;
	vertices_[nowIdx].no = nowNum_;
	idices_[idicIdx + 4] = nowIdx;
	
	DirectX::XMStoreFloat4x4(&mat_->matrices_[nowNum_], DirectX::XMMatrixIdentity());
	nowNum_++;
}

void TextureSheetRender::Draw(CbMatrix& cbMat)
{
	// �O���t�B�b�N�p�C�v���C�����Z�b�g
	dx12_.CmdLlist()->SetPipelineState(pipeline_.Get());

	// ���[�g�V�O�l�`�����Z�b�g
	dx12_.CmdLlist()->SetGraphicsRootSignature(rootSignature_.Get());

	// �v���~�e�B�u�g�|���W�[���Z�b�g
	dx12_.CmdLlist()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �C���f�N�X���Z�b�g
	dx12_.CmdLlist()->IASetIndexBuffer(ibView_.get());

	// ���_���Z�b�g
	dx12_.CmdLlist()->IASetVertexBuffers(0, 1, vbView_.get());

	// �X�N���[�����W�n����̕ϊ��s����Z�b�g
	ID3D12DescriptorHeap* cbmatDh[]{ cbMat.DescriptorHeap().Get() };
	dx12_.CmdLlist()->SetDescriptorHeaps(1, cbmatDh);
	dx12_.CmdLlist()->SetGraphicsRootDescriptorTable(0, cbMat.DescriptorHeap()->GetGPUDescriptorHandleForHeapStart());

	// �`��̎l�p����Ƃ̕ϊ��s����Z�b�g
	ID3D12DescriptorHeap* matDh[]{ mat_->DescriptorHeap().Get()};
	dx12_.CmdLlist()->SetDescriptorHeaps(1, matDh);
	dx12_.CmdLlist()->SetGraphicsRootDescriptorTable(1, mat_->DescriptorHeap()->GetGPUDescriptorHandleForHeapStart());

	// �e�N�X�`�����Z�b�g
	ID3D12DescriptorHeap* texDh[]{ texData_->GetTexture(imgKey_)->DescriptorHeap().Get()};
	dx12_.CmdLlist()->SetDescriptorHeaps(1, texDh);
	dx12_.CmdLlist()->SetGraphicsRootDescriptorTable(2, texData_->GetTexture(imgKey_)->DescriptorHeap()->GetGPUDescriptorHandleForHeapStart());

	// �`�悷��
	dx12_.CmdLlist()->DrawIndexedInstanced(6 * nowNum_, 1, 0, 0,0);

	nowNum_ = 0;
}

void TextureSheetRender::Update(void)
{
	std::copy(vertices_.begin(), vertices_.end(), vertMap_);
	std::copy(idices_.begin(), idices_.end(), idMap_);
	mat_->Update();
}

bool TextureSheetRender::CreateRootSignature(void)
{
	// �f�B�X�N���v�^�����W
	CD3DX12_DESCRIPTOR_RANGE descTblRange[3] = {};

	// �ϊ��p�s��(b0�X���b�g)
	descTblRange[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);

	// �ό`�p�s��(b1�X���b�g)
	descTblRange[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1);

	// �e�N�X�`���p(t0)
	descTblRange[2].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

	// ���[�g�p�����[�^�[
	CD3DX12_ROOT_PARAMETER rootparam[3]{};
	rootparam[0].InitAsDescriptorTable(1, &descTblRange[0]);
	rootparam[1].InitAsDescriptorTable(1, &descTblRange[1]);
	rootparam[2].InitAsDescriptorTable(1, &descTblRange[2]);

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

bool TextureSheetRender::CreatePipeline(void)
{
	auto flag = D3DCOMPILE_SKIP_OPTIMIZATION;
#ifdef _DEBUG
	flag |= D3DCOMPILE_DEBUG;
#endif
	ComPtr<ID3DBlob> vs{};
	ComPtr<ID3DBlob> errorBlob{ nullptr };
	HRESULT result = D3DCompileFromFile(
		L"Resource/shader/Atlas2DVs.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"vs_5_0",
		flag,
		0,
		&vs,
		&errorBlob);
	if (FAILED(result))
	{
		DebugLog("���_�V�F�[�_�̃R���p�C���Ɏ��s");
		return false;
	}

	ComPtr<ID3DBlob> ps{};
	result = D3DCompileFromFile(
		L"Resource/shader/Atlas2DPs.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"ps_5_0",
		flag,
		0,
		&ps,
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
			"POSITION",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
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
		{	// �s��̔ԍ�
			"BONE_NO",
			0,
			DXGI_FORMAT_R32_UINT,
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
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vs.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(ps.Get());

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
	gpipeline.BlendState.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_SRC_ALPHA;
	gpipeline.BlendState.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_DEST_ALPHA;

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

bool TextureSheetRender::CreateVertex(void)
{
	vertices_.resize(maxNum_ * 4);
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto vrResDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices_[0]) * vertices_.size());
	// ���\�[�X����
	if (dx12_.Device()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&vrResDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(vb_.ReleaseAndGetAddressOf())) != S_OK)
	{
		return false;
	}

	// ���_���̃R�s�[
	if (vb_->Map(0, nullptr, reinterpret_cast<void**>(&vertMap_)) != S_OK)
	{
		return false;
	}
	std::copy(vertices_.begin(), vertices_.end(), vertMap_);
	
	// ���_�o�b�t�@�[�r���[�̍쐬
	vbView_ = std::make_unique<D3D12_VERTEX_BUFFER_VIEW>();
	vbView_->BufferLocation = vb_->GetGPUVirtualAddress();		// �o�b�t�@�̉��z�A�h���X������
	vbView_->SizeInBytes = static_cast<UINT>(sizeof(vertices_[0]) * vertices_.size());		// ���o�C�g��
	vbView_->StrideInBytes = sizeof(Vertex);		// 1t���_������̃o�C�g��

	return true;
}

bool TextureSheetRender::CreateIdx(void)
{
	idices_.resize(maxNum_ * 6);
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto irResDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(idices_[0]) * idices_.size());
	if (dx12_.Device()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&irResDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(ib_.ReleaseAndGetAddressOf())) != S_OK)
	{
		return false;
	}

	// ������o�b�t�@�ɃC���f�b�N�X�f�[�^���R�s�[
	if (FAILED(ib_->Map(0, nullptr, (void**)&idMap_)))
	{
		return false;
	}
	std::copy(std::begin(idices_), std::end(idices_), idMap_);


	// �C���f�b�N�X�o�b�t�@�r���[���쐬����
	ibView_ = std::make_unique<D3D12_INDEX_BUFFER_VIEW>();
	ibView_->BufferLocation = ib_->GetGPUVirtualAddress();
	ibView_->Format = DXGI_FORMAT_R16_UINT;
	ibView_->SizeInBytes = static_cast<UINT>(sizeof(idices_[0]) * idices_.size());

	return true;
}


