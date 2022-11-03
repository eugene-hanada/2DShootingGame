#include "Image.h"
#include "../GameSystem/Dx12/Render/TextureSheetRender.h"

Image::Image(const Math::Vector2& pos, const std::string& imgKey) :
	UiBase{pos, imgKey}
{
}

void Image::Update(ObjectManager& objectManager)
{
}

void Image::Draw(TextureSheetRender& render)
{
	render.DrawLT(pos_, imgKey_);
}
