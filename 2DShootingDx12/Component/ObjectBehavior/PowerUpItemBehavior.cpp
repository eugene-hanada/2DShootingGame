#include "PowerUpItemBehavior.h"
#include "../Collider/Collider.h"
#include "../../Object/Object.h"

void PowerUpItemBehavior::OnHit(Collider& collider)
{
	if (collider.GetOnwer()->GetID() == ObjectID::Player)
	{
		owner_->Destory();
	}
}
