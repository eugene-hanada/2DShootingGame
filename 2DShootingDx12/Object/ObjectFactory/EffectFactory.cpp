#include "EffectFactory.h"
#include "../Object.h"
#include "../../Component/ObjectBehavior/EffectBehavior.h"
#include "../../Component/Render/AnimationRender.h"
#include "../../Component/Animator/Animator.h"

EffectFactory::EffectFactory(std::shared_ptr<AnimationData>& animData)
{
	for (int i = 0; i < 50; i++)
	{
		objPool_.emplace_front(std::make_unique<Object>());
		renderPool_.emplace_front(std::make_shared<AnimationRender>());
		behaviorPool_.emplace_front(std::make_shared<EffectBehavior>(*this));
		animatorPool_.emplace_front(std::make_shared<Animator>(animData));
	}
}

void EffectFactory::CreateExpM(ObjectManager& objectManager, const Math::Vector2& pos)
{
	if (objPool_.empty())
	{
		return;
	}
	auto obj = std::move(objPool_.front());
	objPool_.pop_front();

	auto render = std::static_pointer_cast<AnimationRender>(std::move(renderPool_.front()));
	render->SetImgKey("expm");
	obj->AddComponent(std::move(render));
	renderPool_.pop_front();

	obj->AddComponent(std::move(behaviorPool_.front()));
	behaviorPool_.pop_front();

	auto anim = std::static_pointer_cast<Animator>(std::move(animatorPool_.front()));
	anim->SetState("expm");
	obj->AddComponent(std::move(anim));
}

void EffectFactory::Delete(std::unique_ptr<Object>&& obj)
{
	animatorPool_.emplace_front(obj->RemoveComponent(ComponentID::Animator));
	renderPool_.emplace_front(obj->RemoveComponent(ComponentID::Render));
	behaviorPool_.emplace_front(obj->RemoveComponent(ComponentID::Behavior));
	objPool_.emplace_front(std::move(obj));

}