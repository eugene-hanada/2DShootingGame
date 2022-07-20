#pragma once
#include <memory>
#include "ObjRender.h"

class Animator;

class AnimationRender :
    public ObjRender
{
public:
	AnimationRender();
	~AnimationRender();
private:
	void Draw(TextureSheetRender& texSheetRender) final;
	void Begin(void) final;
	void End(void) final;
	std::weak_ptr<Animator> animator_;
};

