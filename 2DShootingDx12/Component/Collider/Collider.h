#pragma once
#include "../Component.h"

enum class CollType
{
	Non = 0,
	Player = 1 << 0,
	Enemy = 1 <<1,
	PlayerBulletA = 1 << 2,
	PlayerBulletB = 1 << 3,
	EnemyBulletA = 1 << 4,
	EnemyBulletB = 1 << 5,
	All = ~Non
};

class ObjectBehavior;
class CircleCollider;

class Collider :
	public Component
{
public:
	Collider();
	~Collider();
	void Begin(void) final;
	virtual void Check(Collider& collider) = 0;
	virtual bool Check(CircleCollider& collider) = 0;
	void OnHit(Collider& collider);
protected:
	std::weak_ptr<ObjectBehavior> behavior_;
private:
	const ComponentID GetID(void) const noexcept final { return ComponentID::Collider; }
	virtual void Begin(void) override;
};

