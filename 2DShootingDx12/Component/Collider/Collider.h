#pragma once
#include "../Component.h"

enum class CollType
{
	Non,
	Enemy = 1 <<0,
	Player = 1 << 1,
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
	virtual void Check(Collider& collider) = 0;
	virtual bool Check(CircleCollider& collider) = 0;
	void OnHit(Collider& collider);

	void SetTarget(int target)
	{
		targetType_ = target;
	}

	int GetTarget(void)
	{
		return targetType_;
	}

	void SetMyType(CollType type);
protected:
	std::weak_ptr<ObjectBehavior> behavior_;
	CollType myType_;
	int targetType_;
private:
	const ComponentID GetID(void) const noexcept final { return ComponentID::Collider; }
	virtual void Begin(void) override;
};

