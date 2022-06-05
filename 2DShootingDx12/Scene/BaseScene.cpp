#include "../GameSystem/Dx12/Render/RenderManager.h"
#include "../GameSystem/Dx12/Resource/RenderTarget.h"
#include "../Application.h"
#include "BaseScene.h"

BaseScene::BaseScene(std::shared_ptr<RenderManager>& renderMng,Dx12Wrapper& dx12, std::shared_ptr<InputSystem>& input) :
	renderMng_{renderMng}, input_{input},dx12_{dx12}
{
	rt_ = std::make_unique<RenderTarget>(dx12_, Math::Vector2{ 1280.0f,720.0f });
}

BaseScene::~BaseScene()
{
}

void BaseScene::Draw(CbMatrix& cbMat)
{
	renderMng_->Draw(rt_->GetMaterial(), cbMat, RenderType::Basic);
}
