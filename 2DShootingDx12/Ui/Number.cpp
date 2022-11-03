#include "Number.h"
#include "../GameSystem/Dx12/Render/TextureSheetRender.h"

Number::Number(std::function<int(ObjectManager&)>&& bindFunc, const int digit, const Math::Vector2& pos, const std::string& imgKey) :
	UiBase{pos,imgKey}, bindFunc_{std::move(bindFunc)},digit_{digit}, value_{0}
{
}

void Number::Update(ObjectManager& objectManager)
{
	value_ = bindFunc_(objectManager);
}

void Number::Draw(TextureSheetRender& render)
{
	auto& size = render.GetImgSize(imgKey_);
	int tmp = value_;
	for (int i = digit_; i > 0; i--)
	{
		auto t = std::pow(10, i - 1);
		auto val = (tmp / static_cast<int>(std::pow(10, i - 1))) % 10;

		auto drawPos = pos_ + Math::Vector2{ size.x * (digit_ - i) , 0.0f};
		render.DrawLT(drawPos,imgKey_,val);
	}
}
