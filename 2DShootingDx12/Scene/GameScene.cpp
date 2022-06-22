#include "../GameSystem/Dx12/Resource/RenderTarget.h"
#include "../GameSystem/Dx12/Render/RenderManager.h"
#include "../GameSystem/Dx12/Resource/MaterialBase.h"
#include "../GameSystem/Dx12/Resource/Texture.h"
#include "../Component/Transform.h"
#include "GameScene.h"

GameScene::GameScene(std::shared_ptr<RenderManager>& renderMng,Dx12Wrapper& dx12, std::shared_ptr<InputSystem>& input) :
	BaseScene{ renderMng,dx12,input}
{
	rt_->SetClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

GameScene::~GameScene()
{
}

BaseScene::SceneUPtr GameScene::Update(SceneUPtr scene)
{
	return scene;
}

void GameScene::Draw(void)
{
	rt_->Clear();
	rt_->DrawBegin();
	rt_->DrawEnd();
}
