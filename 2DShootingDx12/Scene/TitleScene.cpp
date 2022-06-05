#include "../GameSystem/Dx12/Resource/RenderTarget.h"
#include "../GameSystem/Dx12/Render/RenderManager.h"
#include "../GameSystem/Dx12/Resource/MaterialBase.h"
#include "../GameSystem/Dx12/Resource/Texture.h"
#include "../Component/Transform.h"

#include "../GameSystem/Input/InputSystem.h"
#include "GameScene.h"

#include "TitleScene.h"

TitleScene::TitleScene(std::shared_ptr<RenderManager>& renderMng,Dx12Wrapper& dx12,std::shared_ptr<InputSystem>& input) :
	BaseScene{ renderMng, dx12,input}
{
	testMaterial_ = std::make_unique<MaterialBase>(dx12, Math::Vector2{ 100.0f,100.0f });
	testMaterial_->PushResource(std::make_shared<Texture>(dx12, TEXT("Resource/image/Logo.jpg")));
	testMaterial_->GetTransform()->SetPos(Math::Vector2{ 100.0f,100.0f });
	testMaterial_->GetTransform()->Update();
	rt_->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

TitleScene::~TitleScene()
{
}

BaseScene::SceneUPtr TitleScene::Update(SceneUPtr scene)
{

	
	if (input_->IsPressed(InputID::Shot1))
	{
		return std::make_unique<GameScene>(renderMng_, dx12_, input_);
	}
	
	return scene;
}

void TitleScene::Draw(void)
{
	rt_->Clear();
	rt_->DrawBegin();
	renderMng_->Draw(*testMaterial_, rt_->GetCbMat(), RenderType::Basic);
	rt_->DrawEnd();
}
