#include "StageBehavior.h"
#include "../../Object/ObjectFactory/EnemyFactory.h"
#include "../../GameSystem/Window.h"
#include "../../Object/Object.h"
#include "../../Object/ObjectFactory/PowerUpItemFactory.h"
#include "../../Object/ObjectManager.h"
#include "../../Application.h"

StageBehavior::StageBehavior(std::shared_ptr<AnimationData>& animData, std::shared_ptr<BulletFactory>& bulletFactory, std::shared_ptr< EffectFactory>& effectFactory) :
	score_{0u}
{
	enemyFactory_ = std::make_unique<EnemyFactory>(animData, bulletFactory, effectFactory);
}

void StageBehavior::Update(ObjectManager& objectManager)
{
	timer_ += Time.GetDeltaTime<float>();
	if (timer_ >= 30.0f)
	{
		timer_ = 0.0f;
		auto spPos = Math::Vector2{ ObjectManager::fieldSize_ /2.0f };
		spPos.y = 0.0f;
		enemyFactory_->CreateMoveToPosEnemyS(objectManager, spPos, Math::Vector2{ spPos.x, spPos.y + 250.0f });
		enemyFactory_->CreateMoveToPosEnemyS(objectManager, spPos, Math::Vector2{ spPos.x + 100.0f, spPos.y + 250.0f });
		enemyFactory_->CreateMoveToPosEnemyS(objectManager, spPos, Math::Vector2{ spPos.x - 100.0f, spPos.y + 250.0f });
	}
}

void StageBehavior::Begin(ObjectManager& objectManager)
{
	timer_ = 30.0f;
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
