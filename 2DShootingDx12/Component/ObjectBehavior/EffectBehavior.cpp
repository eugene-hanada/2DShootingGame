#include "EffectBehavior.h"
#include "../../Object/Object.h"
#include "../Animator/Animator.h"
#include "../../Object/ObjectFactory/EffectFactory.h"

#include "../../common/Debug.h"

std::unordered_map<EffectType, void(EffectBehavior::*)(std::unique_ptr<Object>&&)> EffectBehavior::destoryFunc_{
	{ EffectType::ExpM,&EffectBehavior::DestoryExpM },
	{ EffectType::ExpS,&EffectBehavior::DestoryExpS },
	{ EffectType::Score,&EffectBehavior::DestoryScore }
};

EffectBehavior::EffectBehavior(EffectFactory& factory) :
	factory_{factory}, type_{EffectType::Score}
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

void EffectBehavior::Begin(ObjectManager& objectManager)
{
	animator_ = owner_->GetCcomponent<Animator>(ComponentID::Animator);
}

void EffectBehavior::Destory(std::unique_ptr<Object>&& obj)
{
	if (destoryFunc_.contains(type_))
	{
		(this->*destoryFunc_[type_])(std::move(obj));
	}
}

void EffectBehavior::DestoryExpM(std::unique_ptr<Object>&& obj)
{
}

void EffectBehavior::DestoryExpS(std::unique_ptr<Object>&& obj)
{

}

void EffectBehavior::DestoryScore(std::unique_ptr<Object>&& obj)
{
	factory_.Delete(std::move(obj));
}
