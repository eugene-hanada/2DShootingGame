#include <Windows.h>
#include "EnemyBehavior.h"
#include "../../Object/ObjectFactory/EnemyFactory.h"
#include "../../Object/Object.h"
#include "../Collider/Collider.h"
#include "../../Application.h"


EnemyBehavior::EnemyBehavior(EnemyFactory& factory, std::shared_ptr< BulletFactory>& bulletFactory) :
	factory_{factory}, hp_{0}, update_{nullptr}, bulletFactory_{ bulletFactory }
{
}

void EnemyBehavior::Update(ObjectManager& objectManager)
{
	(this->*update_)(objectManager);
}

void EnemyBehavior::Destory(std::unique_ptr<Object>&& obj)
{
	factory_.DestoryMoveToPosEnemy(std::move(obj));
}

void EnemyBehavior::SetDestination(const Math::Vector2& dest)
{
	dest_ = dest;
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

void EnemyBehavior::Begin(void)
{
	update_ = &EnemyBehavior::UpdateMove;
	moveVec_ = (dest_ - owner_->pos_).Normalized();
}

void EnemyBehavior::UpdateMove(ObjectManager& objectManager)
{
	auto moveSpeed = Time.GetDeltaTime<float>() * 120.0f;
	owner_->pos_ += moveVec_ * moveSpeed;
	if ((owner_->pos_ - dest_).SqMagnitude() <= Math::Square(moveSpeed))
	{
		update_ = &EnemyBehavior::UpdateShot;
	}
}

void EnemyBehavior::UpdateShot(ObjectManager& objectManager)
{
}
