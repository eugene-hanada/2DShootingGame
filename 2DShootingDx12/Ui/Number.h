#pragma once
#include "UiBase.h"
#include <functional>

class Number :
	public UiBase
{
public:
	Number(std::function<int(void)>&& bindFunc, const int digit, const Math::Vector2& pos, const std::string& imgKey);
private:
	void Update(void) final;
	void Draw(TextureSheetRender& render) final;
	std::function<int(void)> bindFunc_;
	const int digit_;
	int value_;
};

