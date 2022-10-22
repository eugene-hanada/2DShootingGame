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

	// 左上
	vertices_[nowIdx].pos = 0.0f;
	vertices_[nowIdx].uv = data.pos;
	vertices_[nowIdx].uv /= size;
	vertices_[nowIdx].no = nowNum_;
	idices_[idicIdx] = nowIdx;

	nowIdx++;

	// 右上
	vertices_[nowIdx].pos = 0.0f;
	vertices_[nowIdx].pos.x += data.wh.x;
	vertices_[nowIdx].uv = data.pos;
	vertices_[nowIdx].uv.x += data.wh.x;
	vertices_[nowIdx].uv /= size;
	vertices_[nowIdx].no = nowNum_;
	idices_[idicIdx + 1] = nowIdx;
	idices_[idicIdx + 3] = nowIdx;

	nowIdx++;

	// 左下
	vertices_[nowIdx].pos = 0.0f;
	vertices_[nowIdx].pos.y += data.wh.y;
	vertices_[nowIdx].uv = data.pos;
	vertices_[nowIdx].uv.y += data.wh.y;
	vertices_[nowIdx].uv /= size;
	vertices_[nowIdx].no = nowNum_;
	idices_[idicIdx + 2] = nowIdx;
	idices_[idicIdx + 5] = nowIdx;

	nowIdx++;

	// 右下
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

	// 左上
	vertices_[nowIdx].no = nowNum_;
	vertices_[nowIdx].pos = lt;
	vertices_[nowIdx].uv = data.pos;
	vertices_[nowIdx].uv /= size;
	vertices_[nowIdx].no = nowNum_;
	idices_[idicIdx] = nowIdx;

	nowIdx++;

	// 右上
	vertices_[nowIdx].no = nowNum_;
	vertices_[nowIdx].pos = rt;
	vertices_[nowIdx].uv = data.pos;
	vertices_[nowIdx].uv.x += data.wh.x;
	vertices_[nowIdx].uv /= size;
	vertices_[nowIdx].no = nowNum_;
	idices_[idicIdx + 1] = nowIdx;
	idices_[idicIdx + 3] = nowIdx;

	nowIdx++;

	// 左下
	vertices_[nowIdx].no = nowNum_;
	vertices_[nowIdx].pos = lb;
	vertices_[nowIdx].uv = data.pos;
	vertices_[nowIdx].uv.y += data.wh.y;
	vertices_[nowIdx].uv /= size;
	vertices_[nowIdx].no = nowNum_;
	idices_[idicIdx + 2] = nowIdx;
	idices_[idicIdx + 5] = nowIdx;

	nowIdx++;

	// 右下
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
	// グラフィックパイプラインをセット
	dx12_.CmdLlist()->SetPipelineState(pipeline_.Get());

	// ルートシグネチャをセット
	dx12_.CmdLlist()->SetGraphicsRootSignature(rootSignature_.Get());

	// プリミティブトポロジーをセット
	dx12_.CmdLlist()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// インデクスをセット
	dx12_.CmdLlist()->IASetIndexBuffer(ibView_.get());

	// 頂点をセット
	dx12_.CmdLlist()->IASetVertexBuffers(0, 1, vbView_.get());

	// スクリーン座標系からの変換行列をセット
	ID3D12DescriptorHeap* cbmatDh[]{ cbMat.DescriptorHeap().Get() };
	dx12_.CmdLlist()->SetDescriptorHeaps(1, cbmatDh);
	dx12_.CmdLlist()->SetGraphicsRootDescriptorTable(0, cbMat.DescriptorHeap()->GetGPUDescriptorHandleForHeapStart());

	// 描画の四角一個ごとの変換行列をセット
	ID3D12DescriptorHeap* matDh[]{ mat_->DescriptorHeap().Get()};
	dx12_.CmdLlist()->SetDescriptorHeaps(1, matDh);
	dx12_.CmdLlist()->SetGraphicsRootDescriptorTable(1, mat_->DescriptorHeap()->GetGPUDescriptorHandleForHeapStart());

	// テクスチャをセット
	ID3D12DescriptorHeap* texDh[]{ texData_->GetTexture(imgKey_)->DescriptorHeap().Get()};
	dx12_.CmdLlist()->SetDescriptorHeaps(1, texDh);
	dx12_.CmdLlist()->SetGraphicsRootDescriptorTable(2, texData_->GetTexture(imgKey_)->DescriptorHeap()->GetGPUDescriptorHandleForHeapStart());

	// 描画する
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
	// ディスクリプタレンジ
	CD3DX12_DESCRIPTOR_RANGE descTblRange[3] = {};

	// 変換用行列(b0スロット)
	descTblRange[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);

	// 変形用行列(b1スロット)
	descTblRange[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1);

	// テクスチャ用(t0)
	descTblRange[2].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

	// ルートパラメーター
	CD3DX12_ROOT_PARAMETER rootparam[3]{};
	rootparam[0].InitAsDescriptorTable(1, &descTblRange[0]);
	rootparam[1].InitAsDescriptorTable(1, &descTblRange[1]);
	rootparam[2].InitAsDescriptorTable(1, &descTblRange[2]);

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
		DebugLog("頂点シェーダのコンパイルに失敗");
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
		DebugLog("ピクセルシェーダのコンパイルに失敗");
		return false;
	}

	// シェーダのインプットレイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{	// 座標情報
			"POSITION",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
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
		{	// 行列の番号
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
	// ルートシグネチャをセット
	gpipeline.pRootSignature = rootSignature_.Get();

	// シェーダをセット
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vs.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(ps.Get());

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
	gpipeline.BlendState.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_SRC_ALPHA;
	gpipeline.BlendState.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_DEST_ALPHA;

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

bool TextureSheetRender::CreateVertex(void)
{
	vertices_.resize(maxNum_ * 4);
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto vrResDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices_[0]) * vertices_.size());
	// リソース生成
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

	// 頂点情報のコピー
	if (vb_->Map(0, nullptr, reinterpret_cast<void**>(&vertMap_)) != S_OK)
	{
		return false;
	}
	std::copy(vertices_.begin(), vertices_.end(), vertMap_);
	
	// 頂点バッファービューの作成
	vbView_ = std::make_unique<D3D12_VERTEX_BUFFER_VIEW>();
	vbView_->BufferLocation = vb_->GetGPUVirtualAddress();		// バッファの仮想アドレスを入れる
	vbView_->SizeInBytes = static_cast<UINT>(sizeof(vertices_[0]) * vertices_.size());		// 総バイト数
	vbView_->StrideInBytes = sizeof(Vertex);		// 1t頂点当たりのバイト数

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

	// 作ったバッファにインデックスデータをコピー
	if (FAILED(ib_->Map(0, nullptr, (void**)&idMap_)))
	{
		return false;
	}
	std::copy(std::begin(idices_), std::end(idices_), idMap_);


	// インデックスバッファビューを作成する
	ibView_ = std::make_unique<D3D12_INDEX_BUFFER_VIEW>();
	ibView_->BufferLocation = ib_->GetGPUVirtualAddress();
	ibView_->Format = DXGI_FORMAT_R16_UINT;
	ibView_->SizeInBytes = static_cast<UINT>(sizeof(idices_[0]) * idices_.size());

	return true;
}


