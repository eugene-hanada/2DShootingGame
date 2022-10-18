#include "EnemyBehavior.h"
#include "../../Object/ObjectFactory/EnemyFactory.h"
#include "../../Object/Object.h"
#include "../../Application.h"

EnemyBehavior::EnemyBehavior(EnemyFactory& factory) :
	factory_{factory}
{
}

void EnemyBehavior::Update(ObjectManager& objectManager)
{
	owner_->pos_ += Math::downVector2<float> * 2.5f;
}

void EnemyBehavior::Destory(std::unique_ptr<Object>&& obj)
{
	factory_.DestoryMoveToPosEnemy(std::move(obj));
}
