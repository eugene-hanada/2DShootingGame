#pragma once
#include <string>
#include "ObjRender.h"

// •’Ê‚Ì•`‰æ‚ğ‚·‚éƒNƒ‰ƒX
class DefaultRender :
	public ObjRender
{
public:
	DefaultRender();
	~DefaultRender();
private:
	void Draw(TextureSheetRender& texSheetRender) final;
};

