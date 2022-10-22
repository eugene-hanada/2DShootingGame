#include <Windows.h>
#include "EnemyBehavior.h"
#include "../../Object/ObjectFactory/EnemyFactory.h"
#include "../../Object/Object.h"
#include "../Collider/Collider.h"
#include "../../Application.h"


EnemyBehavior::EnemyBehavior(EnemyFactory& factory, std::shared_ptr< BulletFactory>& bulletFactory) :
	factory_{factory}, hp_{0}, bulletFactory_{ bulletFactory }, shotSpeed_{0.0f}, shotTimer_{0.0f}
{
}

EnemyBehavior::~EnemyBehavior()
{
}

void EnemyBehavior::OnHit(Collider& collider)
{
	if (collider.GetOnwer()->GetID() == ObjectID::PlayerBullet)
	{
		// ƒvƒŒƒCƒ„[‚Ì’e‚É“–‚½‚Á‚½hp‚ğŒ¸‚ç‚·
		if (--hp_ <= 0)
		{
			owner_->Destory();
		}
	}
}
