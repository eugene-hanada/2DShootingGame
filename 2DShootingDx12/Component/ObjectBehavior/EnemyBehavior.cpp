#include <Windows.h>
#include "EnemyBehavior.h"
#include "../../Object/ObjectFactory/EnemyFactory.h"
#include "../../Object/Object.h"
#include "../Collider/Collider.h"
#include "../../common/Random.h"
#include "../../Object/ObjectFactory/PowerUpItemFactory.h"
#include "../../Application.h"
#include "../../Object/ObjectFactory/EffectFactory.h"
#include "../../Object/ObjectManager.h"
#include "../../Component/ObjectBehavior/StageBehavior.h"
#include "../../Object/ObjectFactory/BulletFactory.h"
#include "../../common/Debug.h"

std::unordered_map<ShotType, EnemyBehavior::ShotFunc> EnemyBehavior::shotFuncTbl
{
	{ShotType::Normal, &EnemyBehavior::ShotFront},
	{ShotType::ThreeWay, &EnemyBehavior::Shot3Way},
	{ShotType::Random, &EnemyBehavior::ShotRandom},
};

EnemyBehavior::EnemyBehavior(EnemyFactory& factory, std::shared_ptr< BulletFactory>& bulletFactory, PowerUpItemFactory& itemFactory, EffectFactory& effectFactory) :
	factory_{factory},itemFactory_{itemFactory}, hp_{0}, bulletFactory_{bulletFactory}, effectFactory_{effectFactory},
	shotSpeed_{0.0f}, shotTimer_{0.0f}, bulletSpeed_{0.0f}, moveSpeed_{0.0f}, score_{100u}
{
	shotFunc_ = shotFuncTbl.begin()->second;
}

EnemyBehavior::~EnemyBehavior()
{
}

void EnemyBehavior::SetShotFunc(const ShotType type)
{
	if (shotFuncTbl.contains(type))
	{
		shotFunc_ = shotFuncTbl[type];
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
}

void EnemyBehavior::ShotFront(const Math::Vector2& front, ObjectManager& objectManager)
{
	shotTimer_ += Time.GetDeltaTime<float>();
	if (IsShot())
	{
		bulletFactory_->CreateEnemyNormalBullet(objectManager, owner_->GetPos(), front, bulletSpeed_);
		shotTimer_ = 0.0f;
	}
}

void EnemyBehavior::Shot3Way(const Math::Vector2& front, ObjectManager& objectManager)
{
	shotTimer_ += Time.GetDeltaTime<float>();
	if (IsShot())
	{
		bulletFactory_->CreateEnemyNormalBullet(objectManager, owner_->GetPos(), front, bulletSpeed_);
		auto angleA = front.GetAngle();
		auto angleB = angleA + Math::Deg2Rad(30);
		angleA -= Math::Deg2Rad(30);
		bulletFactory_->CreateEnemyNormalBullet(objectManager, owner_->GetPos(), Math::Vector2{std::cos(angleA),std::sin(angleA)}, bulletSpeed_);
		bulletFactory_->CreateEnemyNormalBullet(objectManager, owner_->GetPos(), Math::Vector2{ std::cos(angleB),std::sin(angleB) }, bulletSpeed_);
		shotTimer_ = 0.0f;
	}
}

void EnemyBehavior::ShotRandom(const Math::Vector2& front, ObjectManager& objectManager)
{
	shotTimer_ += Time.GetDeltaTime<float>();
	if (IsShot())
	{
		float angle = Rand.GetRandom(0.0f, Math::pi2<float>);
		bulletFactory_->CreateEnemyNormalBullet(objectManager, owner_->GetPos(), Math::Vector2{ std::cos(angle),std::sin(angle) }, bulletSpeed_);
		shotTimer_ = 0.0f;
	}
}
