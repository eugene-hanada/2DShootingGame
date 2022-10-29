#include "EnemyMoveToPos.h"
#include <Windows.h>
#include "../../Application.h"
#include "../../Object/ObjectFactory/EnemyFactory.h"
#include "../../Object/ObjectFactory/BulletFactory.h"
#include "../../Object/Object.h"

#include "../../common/Debug.h"




void EnemyMoveToPos::Begin(void)
{
	update_ = &EnemyMoveToPos::UpdateMove;
	moveVec_ = (dest_ - owner_->GetPos()).Normalized();
	shotTimer_ = 0.0f;
}

EnemyMoveToPos::EnemyMoveToPos(EnemyFactory& factory, std::shared_ptr<BulletFactory>& bulletFactory, PowerUpItemFactory& itemFactory) :
	EnemyBehavior{factory, bulletFactory, itemFactory}, update_{nullptr}
{
}

void EnemyMoveToPos::SetDestination(const Math::Vector2& dest)
{
	dest_ = dest;
}

void EnemyMoveToPos::Update(ObjectManager& objectManager)
{
	(this->*update_)(objectManager);
}

void EnemyMoveToPos::Destory(std::unique_ptr<Object>&& obj)
{
	factory_.DestoryMoveToPosEnemy(std::move(obj));
}

void EnemyMoveToPos::UpdateMove(ObjectManager& objectManager)
{
	auto moveSpeed = Time.GetDeltaTime<float>() * 120.0f;
	owner_->pos_ += moveVec_ * moveSpeed;
	if ((owner_->pos_ - dest_).SqMagnitude() <= Math::Square(moveSpeed))
	{
		update_ = &EnemyMoveToPos::UpdateShot;
	}
}

void EnemyMoveToPos::UpdateShot(ObjectManager& objectManager)
{
	shotTimer_ += Time.GetDeltaTime<float>();
	if (IsShot())
	{
		bulletFactory_->CreateEnemyNormalBullet(objectManager, owner_->GetPos(), moveVec_, bulletSpeed_);
		DebugLog("”­ŽË");
		shotTimer_ = 0.0f;
	}
}
