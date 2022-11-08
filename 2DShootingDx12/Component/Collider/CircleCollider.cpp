#include "../../Object/Object.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider()
{
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Check(Collider& collider, ObjectManager& objectManager)
{
	if (collider.Check(*this))
	{
		// ƒqƒbƒgŽž
		OnHit(collider, objectManager);
		collider.OnHit(*this, objectManager);
	}
}

bool CircleCollider::Check(CircleCollider& collider)
{
	return (owner_->GetPos() - collider.owner_->GetPos()).SqMagnitude() < Math::Square(collider.GetRadius() + radius_);
}
