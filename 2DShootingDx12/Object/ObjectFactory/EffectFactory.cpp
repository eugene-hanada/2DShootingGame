#include "EffectFactory.h"
#include "../Object.h"
#include "../../Component/ObjectBehavior/EffectBehavior.h"
#include "../../Component/Render/AnimationRender.h"
#include "../../Component/Animator/Animator.h"
#include "../ObjectManager.h"
#include "../../GameSystem/Xaudio2/Wave.h"
#include "../../Component/Sound/Sound.h"

#include "../../common/Debug.h"

constexpr int expMMax{ 20 };

EffectFactory::EffectFactory(std::shared_ptr<AnimationData>& animData, Xaudio2& xaudio2)
{
	std::shared_ptr<Wave> expM = std::make_shared<Wave>();
	expM->Load("Resource/Sound/ExpM.wav");
	for (int i = 0; i < expMMax; i++)
	{
		expMSound_.emplace_front(std::make_shared<Sound>(xaudio2,expM));
	}

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
	if (expMSound_.empty() || objPool_.empty())
	{
		return;
	}
	auto obj = std::move(objPool_.front());
	objPool_.pop_front();

	auto render = std::static_pointer_cast<AnimationRender>(std::move(renderPool_.front()));
	render->SetImgKey("expm");
	obj->AddComponent(std::move(render));
	renderPool_.pop_front();

	auto behavior = std::static_pointer_cast<EffectBehavior>(std::move(behaviorPool_.front()));
	behavior->SetType(EffectType::ExpM);
	obj->AddComponent(std::move(behavior));
	behaviorPool_.pop_front();

	// サウンドのやつを追加
	auto sound = std::static_pointer_cast<Sound>(std::move(expMSound_.front()));
	expMSound_.pop_front();
	sound->Start();
	obj->AddComponent(std::move(sound));
	

	auto anim = std::static_pointer_cast<Animator>(std::move(animatorPool_.front()));
	animatorPool_.pop_front();
	obj->AddComponent(anim);
	anim->SetState("exp");
	obj->SetPos(pos);
	obj->SetID(ObjectID::Effect);
	objectManager.AddObject(std::move(obj));

}

void EffectFactory::CreateExpS(ObjectManager& objectManager, const Math::Vector2& pos)
{
	if (objPool_.empty() || expMSound_.empty())
	{
		return;
	}
	auto obj = std::move(objPool_.front());
	objPool_.pop_front();

	auto render = std::static_pointer_cast<AnimationRender>(std::move(renderPool_.front()));
	render->SetImgKey("exps");
	obj->AddComponent(std::move(render));
	renderPool_.pop_front();

	auto behavior = std::static_pointer_cast<EffectBehavior>(std::move(behaviorPool_.front()));
	behavior->SetType(EffectType::ExpS);
	obj->AddComponent(std::move(behavior));
	behaviorPool_.pop_front();

	// サウンドのやつを追加
	std::static_pointer_cast<Sound>(expMSound_.front())->Start();
	obj->AddComponent(std::move(expMSound_.front()));
	expMSound_.pop_front();

	auto anim = std::static_pointer_cast<Animator>(std::move(animatorPool_.front()));
	animatorPool_.pop_front();
	obj->AddComponent(anim);
	anim->SetState("exp");
	obj->SetPos(pos);
	obj->SetID(ObjectID::Effect);

	objectManager.AddObject(std::move(obj));
}

void EffectFactory::CreateScore(ObjectManager& objectManager, const Math::Vector2& pos, const std::string& scoreStr)
{
	if (objPool_.empty())
	{
		return;
	}
	auto obj = std::move(objPool_.front());
	objPool_.pop_front();

	auto render = std::static_pointer_cast<AnimationRender>(std::move(renderPool_.front()));
	render->SetImgKey("score");
	obj->AddComponent(std::move(render));
	renderPool_.pop_front();

	auto behavior = std::static_pointer_cast<EffectBehavior>(std::move(behaviorPool_.front()));
	behavior->SetType(EffectType::Score);
	obj->AddComponent(std::move(behavior));
	behaviorPool_.pop_front();

	auto anim = std::static_pointer_cast<Animator>(std::move(animatorPool_.front()));
	animatorPool_.pop_front();
	obj->AddComponent(anim);
	anim->SetState(scoreStr);
	obj->SetPos(pos + ((Math::upVector2<float> + Math::leftVector2<float>).Normalized() * 10.0f));
	obj->SetID(ObjectID::Effect);
	objectManager.AddObject(std::move(obj));
}

void EffectFactory::Delete(std::unique_ptr<Object>&& obj)
{
	
}

void EffectFactory::DeleteExpM(std::unique_ptr<Object>&& obj)
{
	
	animatorPool_.emplace_front(obj->RemoveComponent(ComponentID::Animator));
	renderPool_.emplace_front(obj->RemoveComponent(ComponentID::Render));
	behaviorPool_.emplace_front(obj->RemoveComponent(ComponentID::Behavior));
	expMSound_.emplace_front(obj->RemoveComponent(ComponentID::Sound));
	objPool_.emplace_front(std::move(obj));
}

void EffectFactory::DeleteExpS(std::unique_ptr<Object>&& obj)
{
	animatorPool_.emplace_front(obj->RemoveComponent(ComponentID::Animator));
	renderPool_.emplace_front(obj->RemoveComponent(ComponentID::Render));
	behaviorPool_.emplace_front(obj->RemoveComponent(ComponentID::Behavior));
	expSSound_.emplace_front(obj->RemoveComponent(ComponentID::Sound));
	objPool_.emplace_front(std::move(obj));

}

void EffectFactory::DeleteScore(std::unique_ptr<Object>&& obj)
{
	animatorPool_.emplace_front(obj->RemoveComponent(ComponentID::Animator));
	renderPool_.emplace_front(obj->RemoveComponent(ComponentID::Render));
	behaviorPool_.emplace_front(obj->RemoveComponent(ComponentID::Behavior));
	objPool_.emplace_front(std::move(obj));

}
