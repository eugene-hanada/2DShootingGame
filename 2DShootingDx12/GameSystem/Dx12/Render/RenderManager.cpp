#include <d3dcompiler.h>
#include "BasicRender.h"
#include "RenderManager.h"
#include "AlphaRender.h"
#include "../../../common/Debug.h"

RenderManager::RenderManager(Dx12Wrapper& dx12)
{
	ComPtr<ID3DBlob> basicPs{ nullptr };
	LoadPs(TEXT("Resource/shader/Basic2DPs.hlsl"), basicPs);
	ComPtr<ID3DBlob> basicVs{ nullptr };
	LoadVs(TEXT("Resource/shader/Basic2DVs.hlsl"), basicVs);

	renderMap_.emplace(RenderType::Basic, std::make_unique<BasicRender>(basicVs,basicPs,dx12));
	ComPtr<ID3DBlob> alphaPs{ nullptr };
	LoadPs(TEXT("Resource/shader/Alpha2DPs.hlsl"), alphaPs);
	renderMap_.emplace(RenderType::Alpha, std::make_unique<AlphaRender>(basicVs, alphaPs, dx12));
}

RenderManager::~RenderManager()
{
}

void RenderManager::Draw(MaterialBase& mat, CbMatrix& cbMat, RenderType type)
{
	renderMap_[type]->Draw(mat, cbMat);
}

void RenderManager::LoadVs(const std::basic_string<TCHAR>& path, ComPtr<ID3DBlob>& blob)
{
	auto flag = D3DCOMPILE_SKIP_OPTIMIZATION;
#ifdef _DEBUG
	flag |= D3DCOMPILE_DEBUG;
#endif

	ComPtr<ID3DBlob> errorBlob{nullptr};
	HRESULT result = D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"vs_5_0",
		flag,
		0,
		&blob,
		&errorBlob);
	if (FAILED(result))
	{
		DebugLog("頂点シェーダのコンパイルに失敗");
		return ;
	}
}

void RenderManager::LoadPs(const std::basic_string<TCHAR>& path, ComPtr<ID3DBlob>& blob)
{
	auto flag = D3DCOMPILE_SKIP_OPTIMIZATION;
#ifdef _DEBUG
	flag |= D3DCOMPILE_DEBUG;
#endif

	ComPtr<ID3DBlob> errorBlob{ nullptr };
	HRESULT result = D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"ps_5_0",
		flag,
		0,
		&blob,
		&errorBlob
	);
	if (FAILED(result))
	{
		DebugLog("ピクセルシェーダのコンパイルに失敗");
		return ;
	}
}
