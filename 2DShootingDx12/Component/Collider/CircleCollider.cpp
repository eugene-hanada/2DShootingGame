#include "../../Object/Object.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider()
{
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Check(Collider& collider)
{
	if (collider.Check(*this))
	{
		OnHit(collider);
		collider.OnHit(*this);
	}
}

bool CircleCollider::Check(CircleCollider& collider)
{
	return (owner_->GetPos() - collider.owner_->GetPos()).SqMagnitude() < Math::Square(collider.GetRadius() + radius_);
}
