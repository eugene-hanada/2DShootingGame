#include "EnemyMoveToPos.h"
#include <Windows.h>
#include "../../Application.h"
#include "../../Object/ObjectFactory/EnemyFactory.h"
#include "../../Object/ObjectFactory/BulletFactory.h"
#include "../../Object/Object.h"

#include "../../common/Debug.h"




void EnemyMoveToPos::Begin(ObjectManager& objectManager)
{
	EnemyBehavior::Begin(objectManager);
	update_ = &EnemyMoveToPos::UpdateMove;
	moveDir_ = (dest_ - owner_->GetPos()).Normalized();
	shotTimer_ = 0.0f;
}

EnemyMoveToPos::EnemyMoveToPos(EnemyFactory& factory, std::shared_ptr<BulletFactory>& bulletFactory, PowerUpItemFactory& itemFactory, EffectFactory& effectFactory) :
	EnemyBehavior{factory, bulletFactory, itemFactory,effectFactory }, update_{nullptr}
{
}

void EnemyMoveToPos::SetDestination(const Math::Vector2& dest)
{
	dest_ = dest;
}

void EnemyMoveToPos::Update(ObjectManager& objectManager)
{
	(this->*update_)(objectManager);
	(this->*shotFunc_)(objectManager);
}

void EnemyMoveToPos::Destory(std::unique_ptr<Object>&& obj)
{
	factory_.DeleteMoveToPosEnemy(std::move(obj));
}

void EnemyMoveToPos::UpdateMove(ObjectManager& objectManager)
{
	auto moveSpeed = Time.GetDeltaTime<float>() * moveSpeed_;
	owner_->pos_ += moveDir_ * moveSpeed;
	if ((owner_->pos_ - dest_).SqMagnitude() <= Math::Square(moveSpeed))
	{
		update_ = &EnemyMoveToPos::UpdateStop;
	}
}

void EnemyMoveToPos::UpdateStop(ObjectManager& objectManager)
{
	// ‰½‚à‚µ‚È‚¢
}
