#include "../GameSystem/Dx12/Resource/RenderTarget.h"
#include "../GameSystem/Dx12/Render/RenderManager.h"
#include "../Component/Material.h"
#include "../GameSystem/Dx12/Resource/Texture.h"
#include "../Component/Transform.h"
#include "../GameSystem/Dx12/Resource/CbValue.h"
#include "../GameSystem/Input/InputSystem.h"
#include "GameScene.h"

#include "TitleScene.h"

TitleScene::TitleScene(std::shared_ptr<RenderManager>& renderMng,Dx12Wrapper& dx12,std::shared_ptr<InputSystem>& input) :
	BaseScene{ renderMng, dx12,input}
{
	testMaterial_ = std::make_unique<Material>(TEXT("Resource/image/Logo.png"),dx12, Math::Vector2{ 100.0f,100.0f });
	testMaterial_->SetTransform(std::make_shared<Transform>(dx12));
	testMaterial_->GetTransform()->SetPos(Math::Vector2{ 100.0f,100.0f }); 
	testMaterial_->GetTransform()->Update();
	rt_->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	alpha_ = std::make_shared<CbValue<float>>(dx12_);
	alpha_->val_ = 0.1f;
	alpha_->Update();
	testMaterial_->shaderResource_.emplace_back(alpha_);
	
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
	renderMng_->Draw(*testMaterial_, rt_->GetCbMat(), RenderType::Alpha);
	rt_->DrawEnd();
}
