#include "EffectBehavior.h"
#include "../../Object/Object.h"
#include "../Animator/Animator.h"

void EffectBehavior::Update(ObjectManager& objectManager)
{
	if (!animator_.expired())
	{
		if (animator_.lock()->IsEnd())
		{
			owner_->Destory();
		}
	}
}

void EffectBehavior::Begin(void)
{
	animator_ = owner_->GetCcomponent<Animator>(ComponentID::Animator);
}
