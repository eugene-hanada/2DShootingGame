#include "../../Object/Object.h"
#include "../ObjectBehavior/ObjectBehavior.h"
#include "Collider.h"

void Collider::Begin(void)
{
	auto b = owner_->GetCcomponent<ObjectBehavior>(ComponentID::Behavior);
}
