#pragma once
#include "UiBase.h"
class Image :
    public UiBase
{
public:
    Image(const Math::Vector2& pos, const std::string& imgKey);
private:
    void Update(ObjectManager& objectManager) final;
    void Draw(TextureSheetRender& render) final;
};

