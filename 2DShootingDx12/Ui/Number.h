#pragma once
#include "UiBase.h"
#include <functional>

class Number :
	public UiBase
{
public:
	Number(std::function<int(ObjectManager&)>&& bindFunc, const int digit, const Math::Vector2& pos, const std::string& imgKey);
private:
	void Update(ObjectManager& objectManager) final;
	void Draw(TextureSheetRender& render) final;
	std::function<int(ObjectManager&)> bindFunc_;
	const int digit_;
	int value_;
};

