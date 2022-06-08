#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <wrl.h>
#include <d3dcommon.h>

enum class RenderType
{
	Basic,
	Add,
	Alpha
};

class MaterialBase;
class CbMatrix;
class RenderBase;
class Dx12Wrapper;

class RenderManager
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	RenderManager(Dx12Wrapper& dx12);
	~RenderManager();
	void Draw(MaterialBase& mat, CbMatrix& cbMat, RenderType type);
private:
	std::unordered_map<RenderType, std::unique_ptr<RenderBase>> renderMap_;
	static void LoadVs(const std::basic_string<TCHAR>& path, ComPtr<ID3DBlob>& blob);
	static void LoadPs(const std::basic_string<TCHAR>& path, ComPtr<ID3DBlob>& blob);
};

