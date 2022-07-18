#pragma once
#include <string>
#include "ObjRender.h"

class DefaultRender :
	public ObjRender
{
public:
	DefaultRender();
	~DefaultRender();
private:
	void Draw(TextureSheetRender& texSheetRender) final;
};

