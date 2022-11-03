#include "UiManager.h"
#include "../common/TextureData.h"
#include "../GameSystem/Dx12/Render/TextureSheetRender.h"
#include "Number.h"

UiManager::UiManager(const std::string& texFile, std::shared_ptr<TextureData>& textureData, Dx12Wrapper& dx12) :
	textureData_{textureData}
{
	// テクスチャを描画するクラスを作成
	texSheetRender_ = std::make_unique< TextureSheetRender>(texFile, dx12, textureData_, 256);


}

void UiManager::Update(void)
{
	for (auto& ui : uiList_)
	{
		ui->Update();
	}
}

void UiManager::Draw(RenderManager& renderMng, CbMatrix& cbMat)
{
	for (auto& ui : uiList_)
	{
		ui->Draw(*texSheetRender_);
	}
	texSheetRender_->Update();
	texSheetRender_->Draw(cbMat);
}

void UiManager::CreateGameUi(void)
{
	uiList_.emplace_back(std::make_unique<Number>([]() {return 100; }, 4, Math::zeroVector2<float>, "num"));
}
