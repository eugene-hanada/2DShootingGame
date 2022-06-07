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
	// シェーダの設定
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
		DebugLog("頂点シェーダのコンパイルに失敗");
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
		DebugLog("ピクセルシェーダのコンパイルに失敗");
		return false;
	}

	// シェーダのインプットレイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{	// 座標情報
			"POSITION",		// セマンティクス名　座標情報なのでPOSITION
			0,			// 同じセマンティクス名の時に使うので0でよい
			DXGI_FORMAT_R32G32_FLOAT,	// フォーマット
			0,		// 入力スロットインデックス
			D3D12_APPEND_ALIGNED_ELEMENT,		// データのオフセット位置これでよい
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		// これでよい
			0		// 一度に描画するインスタンスの数なので0
		},
		{	// uv情報
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
	// ルートシグネチャをセット
	gpipeline.pRootSignature = rootSignature_.Get();

	// シェーダをセット
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	// デフォルトのサンプルマスク
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	// ラスタライザ周りの設定
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;

	// 深度ステンシルの設定
	gpipeline.DepthStencilState.DepthEnable = false;
	gpipeline.DepthStencilState.StencilEnable = false;


	// ブレンド設定系
	gpipeline.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	gpipeline.BlendState.RenderTarget[0].BlendEnable = true;
	gpipeline.BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	gpipeline.BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	gpipeline.BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

	// 入力レイアウトを設定
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	// ポリゴンの表示についての設定
	gpipeline.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;		// インデックスバッファを使う
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;		// 三角形を表す
	gpipeline.NumRenderTargets = 1;		// 今は一つなので
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;		// 正規化されたRGBAを渡す

	// アンチエイリアシングに関する設定
	gpipeline.SampleDesc.Count = 1;
	gpipeline.SampleDesc.Quality = 0;

	if (FAILED(dx12_.Device()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(pipeline_.ReleaseAndGetAddressOf()))))
	{
		DebugLog("グラフィックパイプラインの生成に失敗");
		return false;
	}
	return true;
}

bool AlphaRender::CreateRootSignature(void)
{
	// ディスクリプタレンジ
	CD3DX12_DESCRIPTOR_RANGE descTblRange[4] = {};

	// 変換用行列(b0スロット)
	descTblRange[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);

	// 変形用行列(b1スロット)
	descTblRange[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1);

	// テクスチャ用(t0)
	descTblRange[2].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

	// α値変更用(b1スロット)
	descTblRange[3].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 2);

	// ルートパラメーター
	CD3DX12_ROOT_PARAMETER rootparam[4]{};
	rootparam[0].InitAsDescriptorTable(1, &descTblRange[0]);
	rootparam[1].InitAsDescriptorTable(1, &descTblRange[1]);
	rootparam[2].InitAsDescriptorTable(1, &descTblRange[2]);
	rootparam[3].InitAsDescriptorTable(1, &descTblRange[3]);

	// サンプラー設定
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
		DebugLog("ルートシグネチャのシリアライズに失敗");
		return false;
	}
	if (FAILED(dx12_.Device()->CreateRootSignature(
		0,
		rootSigBlob->GetBufferPointer(),
		rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(rootSignature_.ReleaseAndGetAddressOf())))
		)
	{
		DebugLog("ルートシグネチャの生成に失敗");
		return false;
	}

	return true;
}
