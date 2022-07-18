#include "../../GameSystem/Dx12/Render/TextureSheetRender.h"
#include "../../Object/Object.h"
#include "DefaultRender.h"

DefaultRender::DefaultRender()
{
}

DefaultRender::~DefaultRender()
{
}

void DefaultRender::Draw(TextureSheetRender& texSheetRender)
{
	texSheetRender.Draw(owner_->pos_, imgKey_);
}
