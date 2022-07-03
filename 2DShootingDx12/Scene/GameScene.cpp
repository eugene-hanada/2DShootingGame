#include "../GameSystem/Dx12/Resource/RenderTarget.h"
#include "../GameSystem/Dx12/Render/RenderManager.h"
#include "../GameSystem/Dx12/Resource/MaterialBase.h"
#include "../GameSystem/Dx12/Resource/Texture.h"
#include "../Component/Transform.h"
#include "../Object/ObjectManager.h"
#include "../GameSystem/Input/InputSystem.h"
#include "GameScene.h"

GameScene::GameScene(std::shared_ptr<RenderManager>& renderMng,Dx12Wrapper& dx12, std::shared_ptr<InputSystem>& input) :
	BaseScene{ renderMng,dx12,input}
{
	rt_->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	objManager_ = std::make_unique<ObjectManager>(input_,dx12_);

}

GameScene::~GameScene()
{
}

BaseScene::SceneUPtr GameScene::Update(SceneUPtr scene)
{
	objManager_->Update();
	return scene;
}

void GameScene::Draw(void)
{
	rt_->Clear();
	rt_->DrawBegin();
	objManager_->Draw(*renderMng_, rt_->GetCbMat());
	rt_->DrawEnd();
}
