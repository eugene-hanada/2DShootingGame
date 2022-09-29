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
		texSheetRender.Draw(owner_->pos_, imgKey_, animator_.lock()->GetIdx());
	}
}

void AnimationRender::Begin(void)
{
	animator_ = owner_->GetCcomponent<Animator>(ComponentID::Animator);
}

void AnimationRender::End(ObjectManager& objectManager)
{
	animator_.reset();
}
