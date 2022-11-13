#include "UiManager.h"
#include "../common/TextureData.h"
#include "../GameSystem/Dx12/Render/TextureSheetRender.h"
#include "Number.h"
#include "Image.h"
#include "../Object/ObjectManager.h"
#include "../Object/Object.h"
#include "../Component/ObjectBehavior/StageBehavior.h"
#include "../Component/ObjectBehavior/PlayerBehavior.h"
#include "../Application.h"
#include "../GameSystem/Window.h"

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
			0,
			[](ObjectManager& objMng) {
				auto& [obj, result] = objMng.FindObject(ObjectID::Stage);
				if (result)
				{
					auto behavior = (*obj)->GetCcomponent<StageBehavior>(ComponentID::Behavior);
					if (!behavior.expired())
					{
						return static_cast<int>(behavior.lock()->GetScore());
					}
				}
				return 0; 
			},
			4, Math::Vector2{ 0.0f, 130.0f }, "num"
				)
	);
	uiList_.emplace_back(std::make_unique<Image>(Math::Vector2{ 0.0f, 100.0f }, "score"));

	uiList_.emplace_back(std::make_unique<Image>(Math::Vector2{ 0.0f, 200.0f }, "power"));
	uiList_.emplace_back(
		std::make_unique<Number>(
			0,
			[](ObjectManager& objMng) {
				auto& [obj, result] = objMng.FindObject(ObjectID::Player);
				if (result)
				{
					auto behavior = (*obj)->GetCcomponent<PlayerBehavior>(ComponentID::Behavior);
					if (!behavior.expired())
					{
						return static_cast<int>(behavior.lock()->GetLevel());
					}
				}
				return 0;
			},
			4, Math::Vector2{ 0.0f, 230.0f }, "num"
	));
}

void UiManager::CreateTitleUi(void)
{
	const auto scSize_ = App.GetWindow().GetSize<float>();
	uiList_.emplace_back(std::make_unique<Image>(Math::Vector2{ scSize_.x / 2.0f - 245.75f, scSize_.y/2.0f - 70.0f }, "TitleLogo"));
	uiList_.emplace_back(std::make_unique<Image>(Math::Vector2{ scSize_.x / 2.0f - 290.5f, 300.0f }, "TitleMess"));
}

void UiManager::CreateResultUi(unsigned int score)
{
	const auto scSize_ = App.GetWindow().GetSize<float>();
	uiList_.emplace_back(std::make_unique<Image>(Math::Vector2{ scSize_.x / 2.0f - 207.0f, scSize_.y / 2.0f - 70.0f }, "ResultLogo"));
	uiList_.emplace_back(std::make_unique<Image>(Math::Vector2{ scSize_.x / 2.0f - 293.0f, scSize_.y / 2.0f + 140.0f }, "ResultMess"));
	uiList_.emplace_back(
		std::make_unique<Number>(
			static_cast<int>(score),
			[](ObjectManager& objMng) {
				return 0;
			},
			5, Math::Vector2{ scSize_.x / 2.0f - 78.75f, scSize_.y / 2.0f + 31.5f }, "num"
				));
}
