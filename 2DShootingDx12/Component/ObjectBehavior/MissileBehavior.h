#pragma once
#include "ObjectBehavior.h"
#include "../../common/Math.h"

class Sound;
class BulletFactory;
class ObjRender;
class EffectFactory;

class MissileBehavior :
    public ObjectBehavior
{
public:
	MissileBehavior(BulletFactory& factory, EffectFactory& effect);
	void SetMoveVec(const Math::Vector2& moveVec)
	{
		moveVec_ = moveVec;
	}
private:
	void Update(ObjectManager& objectManager) final;
	void Begin(ObjectManager& objectManager) final;
	void Destory(std::unique_ptr<Object>&& obj) final;

	void UpdateHoming(void);

	void UpdateNotHoming(void);

	void OnHit(Collider& collider, ObjectManager& objectManager) final;

	void (MissileBehavior::* update_)(void);

	BulletFactory& factory_;
	EffectFactory& effect_;
	Math::Vector2 moveVec_;
	Object* target_;
	std::weak_ptr<Sound> sound_;
	std::weak_ptr< ObjRender> render_;
};

