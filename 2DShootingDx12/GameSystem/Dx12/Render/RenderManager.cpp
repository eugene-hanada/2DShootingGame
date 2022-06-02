#include "BasicRender.h"
#include "RenderManager.h"

RenderManager::RenderManager(Dx12Wrapper& dx12)
{
	renderMap_.emplace(RenderType::Basic, std::make_unique<BasicRender>(dx12));
}

RenderManager::~RenderManager()
{
}

void RenderManager::Draw(MaterialBase& mat, CbMatrix& cbMat, RenderType type)
{
	renderMap_[type]->Draw(mat, cbMat);
}
