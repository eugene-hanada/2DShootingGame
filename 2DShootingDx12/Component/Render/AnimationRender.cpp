#include "../../Object/Object.h"
#include "../Animator/Animator.h"
#include "../../GameSystem/Dx12/Render/TextureSheetRender.h"
#include "AnimationRender.h"
#include "../../common/Debug.h"

AnimationRender::AnimationRender()
{
}

AnimationRender::~AnimationRender()
{
}

void AnimationRender::Draw(TextureSheetRender& texSheetRender)
{
	if (!animator_.expired())
	{
		texSheetRender.Draw(owner_->pos_, imgKey_, rotation_,animator_.lock()->GetIdx());
	}
}

void AnimationRender::Begin(ObjectManager& objectManager)
{
	animator_ = owner_->GetCcomponent<Animator>(ComponentID::Animator);
}

void AnimationRender::End(void)
{
	animator_.reset();
}
