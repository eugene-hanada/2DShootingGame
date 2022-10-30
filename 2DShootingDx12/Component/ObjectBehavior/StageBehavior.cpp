#include "StageBehavior.h"
#include "../../Object/ObjectFactory/EnemyFactory.h"
#include "../../GameSystem/Window.h"
#include "../../Object/Object.h"
#include "../../Object/ObjectFactory/PowerUpItemFactory.h"
#include "../../Object/ObjectManager.h"
#include "../../Application.h"

StageBehavior::StageBehavior(std::shared_ptr<AnimationData>& animData, std::shared_ptr<BulletFactory>& bulletFactory)
{
	enemyFactory_ = std::make_unique<EnemyFactory>(animData, bulletFactory);
}

void StageBehavior::Update(ObjectManager& objectManager)
{
	timer_ += Time.GetDeltaTime<float>();
	if (timer_ >= 30.0f)
	{
		timer_ = 0.0f;
		auto spPos = Math::Vector2{ ObjectManager::fieldSize_ /2.0f };
		spPos.y = 0.0f;
		enemyFactory_->CreateMoveToPosEnemy(objectManager, spPos, Math::Vector2{ spPos.x, spPos.y + 250.0f });
		enemyFactory_->CreateMoveToPosEnemy(objectManager, spPos, Math::Vector2{ spPos.x + 100.0f, spPos.y + 250.0f });
		enemyFactory_->CreateMoveToPosEnemy(objectManager, spPos, Math::Vector2{ spPos.x - 100.0f, spPos.y + 250.0f });
	}
}

void StageBehavior::Begin(void)
{
	timer_ = 30.0f;
	owner_->SetID(ObjectID::Stage);
}
