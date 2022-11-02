#include <Windows.h>
#include "EnemyBehavior.h"
#include "../../Object/ObjectFactory/EnemyFactory.h"
#include "../../Object/Object.h"
#include "../Collider/Collider.h"
#include "../../common/Random.h"
#include "../../Object/ObjectFactory/PowerUpItemFactory.h"
#include "../../Application.h"
#include "../../Object/ObjectFactory/EffectFactory.h"

#include "../../common/Debug.h"

EnemyBehavior::EnemyBehavior(EnemyFactory& factory, std::shared_ptr< BulletFactory>& bulletFactory, PowerUpItemFactory& itemFactory, EffectFactory& effectFactory) :
	factory_{factory},itemFactory_{itemFactory}, hp_{0}, bulletFactory_{bulletFactory}, effectFactory_{effectFactory}, shotSpeed_{0.0f}, shotTimer_{0.0f}, bulletSpeed_{0.0f}, moveSpeed_{0.0f}
{
}

EnemyBehavior::~EnemyBehavior()
{
}

void EnemyBehavior::OnHit(Collider& collider, ObjectManager& objectManager)
{
	if (collider.GetOnwer()->GetID() == ObjectID::PlayerBullet)
	{
		// ƒvƒŒƒCƒ„[‚Ì’e‚É“–‚½‚Á‚½hp‚ğŒ¸‚ç‚·
		if (--hp_ <= 0)
		{
			if (Rand.GetRandom(0.9))
			{
				itemFactory_.Create(objectManager,owner_->pos_);
			}
			DebugLog("€–S");
			effectFactory_.CreateExpM(objectManager, owner_->pos_);
			effectFactory_.CreateScore(objectManager, owner_->pos_, "100");
			owner_->Destory();
		}
	}
}
