#include "../../Object/Object.h"
#include "../ObjectBehavior/ObjectBehavior.h"
#include "Collider.h"

Collider::Collider():
	myType_{},targetType_{0}
{
}

Collider::~Collider()
{
}

void Collider::Begin(ObjectManager& objectManager)
{
	behavior_ = owner_->GetCcomponent<ObjectBehavior>(ComponentID::Behavior);
}

void Collider::OnHit(Collider& collider, ObjectManager& objectManager)
{
	if (!behavior_.expired())
	{
		if (behavior_.lock()->IsActive())
		{
			behavior_.lock()->OnHit(collider, objectManager);
		}
	}
}
