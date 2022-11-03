#include "UiManager.h"
#include "../common/TextureData.h"
#include "../GameSystem/Dx12/Render/TextureSheetRender.h"
#include "Number.h"
#include "Image.h"
#include "../Object/ObjectManager.h"
#include "../Object/Object.h"


UiManager::UiManager(const std::string& texFile, std::shared_ptr<TextureData>& textureData, Dx12Wrapper& dx12) :
	textureData_{textureData}
{
	// テクスチャを描画するクラスを作成
	texSheetRender_ = std::make_unique< TextureSheetRender>(texFile, dx12, textureData_, 256);


}

void UiManager::Update(ObjectManager& objectManager)
{
	for (auto& ui : uiList_)
	{
		ui->Update(objectManager);
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
	uiList_.emplace_back(
		std::make_unique<Number>(
			[](ObjectManager& objMng) {
				objMng.FindObject(ObjectID::Stage);
				return 100; 
			},
			4, Math::zeroVector2<float>, "num"
				)
	);
	uiList_.emplace_back(std::make_unique<Image>(Math::Vector2{ 0.0f, 100.0f }, "score"));
}
