#include <Windows.h>
#include "EnemyBehavior.h"
#include "../../Object/ObjectFactory/EnemyFactory.h"
#include "../../Object/Object.h"
#include "../Collider/CircleCollider.h"
#include "../../common/Random.h"
#include "../../Object/ObjectFactory/PowerUpItemFactory.h"
#include "../../Application.h"
#include "../../Object/ObjectFactory/EffectFactory.h"
#include "../../Object/ObjectManager.h"
#include "../../Component/ObjectBehavior/StageBehavior.h"
#include "../../Object/ObjectFactory/BulletFactory.h"
#include "../../common/Debug.h"

std::unordered_map<ShotType, EnemyBehavior::ShotFunc> EnemyBehavior::shotFuncTbl_
{
	{ShotType::Normal, &EnemyBehavior::ShotFront},
	{ShotType::ThreeWay, &EnemyBehavior::Shot3Way},
	{ShotType::Random, &EnemyBehavior::ShotRandom},
};

EnemyBehavior::EnemyBehavior(EnemyFactory& factory, std::shared_ptr< BulletFactory>& bulletFactory, PowerUpItemFactory& itemFactory, EffectFactory& effectFactory) :
	factory_{factory},itemFactory_{itemFactory}, hp_{0}, bulletFactory_{bulletFactory}, effectFactory_{effectFactory},
	shotSpeed_{0.0f}, shotTimer_{0.0f}, bulletSpeed_{0.0f}, moveSpeed_{0.0f}, score_{100u}
{
	shotFunc_ = shotFuncTbl_.begin()->second;
}

EnemyBehavior::~EnemyBehavior()
{
}

void EnemyBehavior::SetShotFunc(const ShotType type)
{
	if (shotFuncTbl_.contains(type))
	{
		shotFunc_ = shotFuncTbl_[type];
	}
}

void EnemyBehavior::OnHit(Collider& collider, ObjectManager& objectManager)
{
	if (collider.GetOnwer()->GetID() == ObjectID::PlayerBullet || collider.GetOnwer()->GetID() == ObjectID::Missile)
	{
		// ÉvÉåÉCÉÑÅ[ÇÃíeÇ…ìñÇΩÇ¡ÇΩéûhpÇå∏ÇÁÇ∑
		if (--hp_ <= 0)
		{
			if (Rand.GetRandom(0.9))
			{
				itemFactory_.Create(objectManager,owner_->pos_);
			}
			DebugLog("éÄñS");
			effectFactory_.CreateExpM(objectManager, owner_->pos_);
			effectFactory_.CreateScore(objectManager, owner_->pos_, std::to_string(score_));

			if (!stage_.expired())
			{
				if (stage_.lock()->IsActive())
				{
					stage_.lock()->AddScore(score_);
				}
			}

			owner_->Destory();
		}
	}
}

void EnemyBehavior::Begin(ObjectManager& objectManager)
{
	auto& [obj, result] = objectManager.FindObject(ObjectID::Stage);
	if (result)
	{
		stage_ = (*obj)->GetCcomponent<StageBehavior>(ComponentID::Behavior);
	}

	collider_ = owner_->GetCcomponent<CircleCollider>(ComponentID::Collider);
	shotTimer_ = shotSpeed_;
}

void EnemyBehavior::ShotFront(ObjectManager& objectManager)
{
	shotTimer_ += Time.GetDeltaTime<float>();
	if (IsShot())
	{
		bulletFactory_->CreateEnemyNormalBullet(objectManager, owner_->GetPos(), Math::downVector2<float>, bulletSpeed_);
		shotTimer_ = 0.0f;
	}
}

void EnemyBehavior::Shot3Way(ObjectManager& objectManager)
{
	shotTimer_ += Time.GetDeltaTime<float>();
	if (IsShot())
	{
		bulletFactory_->CreateEnemyNormalBullet(objectManager, owner_->GetPos(), Math::downVector2<float>, bulletSpeed_);
		auto angle = Math::downVector2<float>.GetAngle();
		constexpr auto rad{ Math::Deg2Rad(30.0f) };
		bulletFactory_->CreateEnemyNormalBullet(objectManager, owner_->GetPos(), Math::Vector2{std::cos(angle + rad),std::sin(angle + rad) }, bulletSpeed_);
		bulletFactory_->CreateEnemyNormalBullet(objectManager, owner_->GetPos(), Math::Vector2{ std::cos(angle - rad),std::sin(angle - rad) }, bulletSpeed_);
		shotTimer_ = 0.0f;
	}
}

void EnemyBehavior::ShotRandom(ObjectManager& objectManager)
{
	shotTimer_ += Time.GetDeltaTime<float>();
	if (IsShot())
	{
		float angle = Rand.GetRandom(0.0f, Math::pi2<float>);
		bulletFactory_->CreateEnemyNormalBullet(objectManager, owner_->GetPos(), Math::Vector2{ std::cos(angle),std::sin(angle) }, bulletSpeed_);
		shotTimer_ = 0.0f;
	}
}
