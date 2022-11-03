#pragma once
#include "../common/Math.h"
#include <string>

class TextureSheetRender;
class ObjectManager;

class UiBase
{
public:
	UiBase(const Math::Vector2& pos, const std::string& imgKey);
	virtual ~UiBase();
	virtual void Update(ObjectManager& objectManager) = 0;
	virtual void Draw(TextureSheetRender& render) = 0;
protected:
	Math::Vector2 pos_;
	std::string imgKey_;
};

