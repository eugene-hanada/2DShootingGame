#include "GameScene.h"
#include "../GameSystem/Dx12/Resource/RenderTarget.h"
#include "../GameSystem/Dx12/Render/RenderManager.h"
#include "../GameSystem/Dx12/Resource/MaterialBase.h"
#include "../GameSystem/Dx12/Resource/Texture.h"
#include "../Component/Transform.h"
#include "../Object/ObjectManager.h"
#include "../GameSystem/Input/InputSystem.h"
//#include "../common/AnimationData.h"
#include "../Application.h"
#include "../common/Debug.h"
#include "../common/TextureData.h"
#include "../GameSystem/Dx12/Render/TextureSheetRender.h"
#include "../Ui/UiManager.h"
#include "../Ui/UiBase.h"
#include "Transition/FadeIn.h"
#include "ResultScene.h"
#include "../GameSystem/Window.h"

GameScene::GameScene(std::shared_ptr<RenderManager>& renderMng,Dx12Wrapper& dx12, Xaudio2& xaudio, std::shared_ptr<InputSystem>& input) :
	BaseScene{ renderMng,dx12,xaudio,input}
{
	textureData_ = std::make_shared<TextureData>(dx12);
	textureData_->Load(L"Resource/image/texture.tdat");
	textureData_->Load(L"Resource/image/GameUi.tdat");
	rt_->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	objRt_ = std::make_unique<RenderTarget>(dx12_, ObjectManager::fieldSize_);
	objRt_->SetClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	uiRt_ = std::make_unique<RenderTarget>(dx12_, Math::Vector2{ (App.GetWindow().GetSize<float>() - ObjectManager::fieldSize_).x , ObjectManager::fieldSize_ .y});
	uiRt_->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	uiRt_->GetMaterial().GetTransform()->SetPos({ ObjectManager::fieldSize_.x, 0.0f });
	uiRt_->GetMaterial().GetTransform()->Update();
	objManager_ = std::make_unique<ObjectManager>(textureData_,input_,dx12_,xaudio_);
	uiManager_ = std::make_unique<UiManager>("GameUi.png", textureData_, dx12_);
	uiManager_->CreateGameUi();
}

GameScene::~GameScene()
{
}

BaseScene::SceneUPtr GameScene::Update(SceneUPtr scene)
{
	if (objManager_->Update())
	{
		return std::make_unique<FadeIn>(std::move(scene), std::make_unique<ResultScene>(renderMng_, dx12_, xaudio_, input_), renderMng_, dx12_, xaudio_, input_);
	}
	uiManager_->Update(*objManager_);
	return scene;
}

void GameScene::Draw(void)
{
	objRt_->Clear();
	objRt_->DrawBegin();
	objManager_->Draw(*renderMng_, objRt_->GetCbMat());
	objRt_->DrawEnd();

	uiRt_->Clear();
	uiRt_->DrawBegin();
	uiManager_->Draw(*renderMng_, uiRt_->GetCbMat());
	uiRt_->DrawEnd();

	rt_->Clear();
	rt_->DrawBegin();
	renderMng_->Draw(objRt_->GetMaterial(), rt_->GetCbMat(),RenderType::Basic);
	renderMng_->Draw(uiRt_->GetMaterial(), rt_->GetCbMat(), RenderType::Basic);
	rt_->DrawEnd();
}
