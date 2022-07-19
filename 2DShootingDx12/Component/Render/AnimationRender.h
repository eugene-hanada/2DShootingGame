#pragma once
#include "ObjRender.h"
class AnimationRender :
    public ObjRender
{
public:
	AnimationRender();
	~AnimationRender();
private:
	void Draw(TextureSheetRender& texSheetRender) final;
};

