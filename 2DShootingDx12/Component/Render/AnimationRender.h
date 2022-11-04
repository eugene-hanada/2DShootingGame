#pragma once
#include <memory>
#include "ObjRender.h"

class Animator;

// �A�j���[�V������`�悷��N���X
class AnimationRender :
    public ObjRender
{
public:
	AnimationRender();
	~AnimationRender();
private:

	void Draw(TextureSheetRender& texSheetRender) final;
	void Begin(ObjectManager& objectManager) final;
	void End(void) final;
	
	// �A�j���[�V��������N���X
	std::weak_ptr<Animator> animator_;
};

