#pragma once
#include <unordered_map>
#include <memory>

enum class RenderType
{
	Basic,
	Add,
};

class MaterialBase;
class CbMatrix;
class RenderBase;
class Dx12Wrapper;

class RenderManager
{
	
public:
	RenderManager(Dx12Wrapper& dx12);
	~RenderManager();
	void Draw(MaterialBase& mat, CbMatrix& cbMat, RenderType type);
private:
	std::unordered_map<RenderType, std::unique_ptr<RenderBase>> renderMap_;
};

