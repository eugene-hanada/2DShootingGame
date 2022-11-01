#include "EffectBehavior.h"
#include "../../Object/Object.h"
#include "../Animator/Animator.h"
#include "../../Object/ObjectFactory/EffectFactory.h"

#include "../../common/Debug.h"

EffectBehavior::EffectBehavior(EffectFactory& factory) :
	factory_{factory}
{
}

void EffectBehavior::Update(ObjectManager& objectManager)
{
	if (!animator_.expired())
	{
		DebugLog(animator_.lock()->GetIdx());
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

void EffectBehavior::Destory(std::unique_ptr<Object>&& obj)
{
	factory_.Delete(std::move(obj));
}
