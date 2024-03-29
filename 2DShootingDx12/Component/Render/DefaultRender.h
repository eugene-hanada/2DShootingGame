#pragma once
#include <string>
#include "ObjRender.h"

// 普通の描画をするクラス
class DefaultRender :
	public ObjRender
{
public:
	DefaultRender();
	~DefaultRender();
private:
	void Draw(TextureSheetRender& texSheetRender) final;
};

