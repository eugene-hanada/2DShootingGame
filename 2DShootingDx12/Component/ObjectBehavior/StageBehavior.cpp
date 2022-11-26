#include "StageBehavior.h"
#include "../../Object/ObjectFactory/EnemyFactory.h"
#include "../../GameSystem/Window.h"
#include "../../Object/Object.h"
#include "../../Object/ObjectFactory/PowerUpItemFactory.h"
#include "../../Object/ObjectManager.h"
#include "../../Application.h"
#include "EnemyBehavior.h"

constexpr float spawnStartTime{ 3.0f };
constexpr float defShotTime{ 2.5f };

StageBehavior::StageLevelVec StageBehavior::stageLevelVec_{
	{10,{&StageBehavior::SpawnMoveToPos1,&StageBehavior::SpawnMoveToPos2}},
	{10,{&StageBehavior::SpawnMoveToPos1,&StageBehavior::SpawnMoveToPos2, &StageBehavior::SpawnMove1}},
	{15,{&StageBehavior::SpawnMoveToPos1,&StageBehavior::SpawnMoveToPos2, &StageBehavior::SpawnMove1,&StageBehavior::SpawnMove2}}
};

StageBehavior::StageBehavior(std::shared_ptr<AnimationData>& animData, std::shared_ptr<BulletFactory>& bulletFactory, std::shared_ptr< EffectFactory>& effectFactory) :
	score_{ 0u }
{
	enemyFactory_ = std::make_unique<EnemyFactory>(animData, bulletFactory, effectFactory);
	nowLevel_ = stageLevelVec_.cbegin();
	spawnItr_ = nowLevel_->second.cbegin();
	spawnTime_ = spawnStartTime;
}

void StageBehavior::Update(ObjectManager& objectManager)
{
	if ((this->*(*spawnItr_))(objectManager))
	{
		++spawnItr_;
		if (spawnItr_ == nowLevel_->second.cend())
		{
			loopCount_++;
			if (loopCount_ >= nowLevel_->first)
			{
				loopCount_ = 0;
				++nowLevel_;
				if (nowLevel_ == stageLevelVec_.end())
				{
					spawnTime_ *= 0.8f;
					nowLevel_ = --stageLevelVec_.cend();
				}
				spawnItr_ = nowLevel_->second.cbegin();
			}
			else
			{
				spawnItr_ = nowLevel_->second.cbegin();
			}
		}
	}
}

bool StageBehavior::SpawnMoveToPos1(ObjectManager& objectManager)
{
	timer_ += Time.GetDeltaTime<float>();
	if (timer_ >= spawnTime_)
	{
		timer_ = 0.0f;
		auto spPos = Math::Vector2{ ObjectManager::fieldSize_ / 2.0f };
		spPos.y = 0.0f;
		enemyFactory_->CreateMoveToPosEnemyS(objectManager, spPos, Math::Vector2{ spPos.x, spPos.y + 250.0f }, ShotType::ThreeWay, defShotTime * (spawnTime_ / spawnStartTime));
		enemyFactory_->CreateMoveToPosEnemyS(objectManager, spPos, Math::Vector2{ spPos.x + 100.0f, spPos.y + 250.0f }, ShotType::Normal, defShotTime * (spawnTime_ / spawnStartTime));
		enemyFactory_->CreateMoveToPosEnemyS(objectManager, spPos, Math::Vector2{ spPos.x - 100.0f, spPos.y + 250.0f }, ShotType::Normal, defShotTime * (spawnTime_ / spawnStartTime));
		return true;
	}
	return false;
}

bool StageBehavior::SpawnMoveToPos2(ObjectManager& objectManager)
{
	timer_ += Time.GetDeltaTime<float>();
	if (timer_ >= spawnTime_)
	{
		timer_ = 0.0f;
		auto spPos = Math::Vector2{ ObjectManager::fieldSize_ / 2.0f };
		spPos.y = 0.0f;
		enemyFactory_->CreateMoveToPosEnemyS(objectManager, spPos, Math::Vector2{ spPos.x + 100.0f, spPos.y + 120.0f }, ShotType::ThreeWay, defShotTime * (spawnTime_ / spawnStartTime));
		enemyFactory_->CreateMoveToPosEnemyS(objectManager, spPos, Math::Vector2{ spPos.x - 100.0f, spPos.y + 120.0f }, ShotType::ThreeWay, defShotTime * (spawnTime_ / spawnStartTime));
		return true;
	}
	return false;
}

bool StageBehavior::SpawnMoveToPos3(ObjectManager& objectManager)
{
	timer_ += Time.GetDeltaTime<float>();
	if (timer_ >= spawnTime_)
	{
		timer_ = 0.0f;
		auto spPos = Math::Vector2{ ObjectManager::fieldSize_ / 2.0f };
		spPos.y = 0.0f;;
		enemyFactory_->CreateMoveToPosEnemyM(objectManager, Math::Vector2{ spPos.x, 0.0f }, Math::Vector2{ spPos.x + 50.0f, 70.0f }, ShotType::ThreeWay, defShotTime * (spawnTime_ / spawnStartTime));
		enemyFactory_->CreateMoveToPosEnemyM(objectManager, Math::Vector2{ spPos.x, 0.0f }, Math::Vector2{ spPos.x - 50.0f, 70.0f }, ShotType::ThreeWay, defShotTime * (spawnTime_ / spawnStartTime));
		return true;
	}
	return false;
}

bool StageBehavior::SpawnMove1(ObjectManager& objectManager)
{
	timer_ += Time.GetDeltaTime<float>();
	if (timer_ >= spawnTime_)
	{
		timer_ = 0.0f;
		auto spPos = Math::Vector2{ ObjectManager::fieldSize_ / 2.0f };
		spPos.y = 0.0f;
		enemyFactory_->CreateMoveEnemyS(objectManager, spPos, Math::downVector2<float>, ShotType::Normal);
		enemyFactory_->CreateMoveEnemyS(objectManager, spPos + Math::Vector2{ 200.0f, 0.0f }, Math::downVector2<float>, ShotType::Normal, defShotTime * (spawnTime_ / spawnStartTime));
		enemyFactory_->CreateMoveEnemyS(objectManager, spPos + Math::Vector2{ -200.0f, 0.0f }, Math::downVector2<float>, ShotType::Normal, defShotTime * (spawnTime_ / spawnStartTime));
		return true;
	}
	return false;
}

bool StageBehavior::SpawnMove2(ObjectManager& objectManager)
{
	timer_ += Time.GetDeltaTime<float>();
	if (timer_ >= spawnTime_)
	{
		timer_ = 0.0f;
		auto spPos = Math::Vector2{ ObjectManager::fieldSize_ / 2.0f };
		spPos.y = 0.0f;
		enemyFactory_->CreateMoveEnemyS(objectManager, spPos, Math::downVector2<float>, ShotType::Normal);
		enemyFactory_->CreateMoveEnemyS(objectManager, spPos + Math::Vector2{ 200.0f, 0.0f }, Math::downVector2<float>, ShotType::Normal, defShotTime * (spawnTime_ / spawnStartTime));
		enemyFactory_->CreateMoveEnemyS(objectManager, spPos + Math::Vector2{ -200.0f, 0.0f }, Math::downVector2<float>, ShotType::Normal, defShotTime * (spawnTime_ / spawnStartTime));
		return true;
	}
	return false;
}

void StageBehavior::Begin(ObjectManager& objectManager)
{
	timer_ = spawnStartTime;
	owner_->SetID(ObjectID::Stage);
}

void StageBehavior::AddScore(unsigned int addValue)
{
	score_ += addValue;
}

void StageBehavior::SubScore(unsigned int subValue)
{
	if (score_ < subValue)
	{
		score_ = 0u;
	}
	else
	{
		score_ -= subValue;
	}
}
