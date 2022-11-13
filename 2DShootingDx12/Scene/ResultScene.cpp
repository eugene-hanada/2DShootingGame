#include "ResultScene.h"
#include "../common/TextureData.h"
#include "../Ui/UiManager.h"
#include "../GameSystem/Dx12/Render/TextureSheetRender.h"
#include "../Ui/UiBase.h"
#include "../GameSystem/Dx12/Resource/RenderTarget.h"
#include "../GameSystem/Input/InputSystem.h"
#include "TitleScene.h"
#include "Transition/FadeIn.h"

ResultScene::ResultScene(unsigned int score,std::shared_ptr<RenderManager>& renderMng, Dx12Wrapper& dx12, Xaudio2& xaudio, std::shared_ptr<InputSystem>& input) :
	BaseScene{renderMng, dx12, xaudio, input}
{
	rt_->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	textureData_ = std::make_shared<TextureData>(dx12_);
	textureData_->Load(L"Resource/image/ResultUi.tdat");
	uiManager_ = std::make_unique<UiManager>("ResultUi.png", textureData_, dx12_);
	uiManager_->CreateResultUi(score);
}

BaseScene::SceneUPtr ResultScene::Update(SceneUPtr scene)
{
	if (input_->IsPressed(InputID::Shot))
	{
		return std::make_unique<FadeIn>(std::move(scene), std::make_unique<TitleScene>(renderMng_, dx12_, xaudio_, input_), renderMng_, dx12_, xaudio_, input_);
	}
	return scene;
}

void ResultScene::Draw(void)
{
	rt_->Clear();
	rt_->DrawBegin();
	uiManager_->Draw(*renderMng_, rt_->GetCbMat());
	rt_->DrawEnd();
}
