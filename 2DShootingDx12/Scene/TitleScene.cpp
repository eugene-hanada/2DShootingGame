#include "../GameSystem/Dx12/Resource/RenderTarget.h"
#include "../GameSystem/Dx12/Render/RenderManager.h"
#include "../Component/Transform.h"
#include "Transition/FadeIn.h"
#include "../common/TextureData.h"
#include "../Ui/UiManager.h"
#include "../GameSystem/Input/InputSystem.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "../GameSystem/Dx12/Render/TextureSheetRender.h"
#include "../Ui/UiBase.h"
#include "../Object/ObjectManager.h"

TitleScene::TitleScene(std::shared_ptr<RenderManager>& renderMng,Dx12Wrapper& dx12, Xaudio2& xaudio,std::shared_ptr<InputSystem>& input) :
	BaseScene{ renderMng, dx12,xaudio,input}
{
	rt_->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	textureData_ = std::make_shared<TextureData>(dx12_);
	bool t = textureData_->Load(L"Resource/image/TitleUi.tdat");

	uiManager_ = std::make_unique<UiManager>("TitleUi.png", textureData_, dx12_);
	uiManager_->CreateTitleUi();
}

TitleScene::~TitleScene()
{
}

BaseScene::SceneUPtr TitleScene::Update(SceneUPtr scene)
{

	
	if (input_->IsPressed(InputID::Shot))
	{
		return std::make_unique<FadeIn>(std::move(scene), std::make_unique<GameScene>(renderMng_, dx12_, xaudio_, input_), renderMng_, dx12_,xaudio_, input_);
	}
	return scene;
}

void TitleScene::Draw(void)
{
	rt_->Clear();
	rt_->DrawBegin();
	uiManager_->Draw(*renderMng_, rt_->GetCbMat());
	rt_->DrawEnd();
}
