#include <Windows.h>
#include "EnemyMove.h"
#include "../../Application.h"
#include "../../Object/Object.h"
#include "../../Object/ObjectFactory/EnemyFactory.h"
#include "../../Object/ObjectManager.h"
#include "../../Object/ObjectFactory/BulletFactory.h"
#include "../Collider/CircleCollider.h"

EnemyMove::EnemyMove(EnemyFactory& factory, std::shared_ptr<BulletFactory>& bulletFactory, PowerUpItemFactory& itemFactory, EffectFactory& effectFactory) :
	EnemyBehavior{factory, bulletFactory, itemFactory, effectFactory}
{
}

void EnemyMove::Update(ObjectManager& objectManager)
{
	owner_->SetPos(owner_->GetPos()  + moveDir_ * moveSpeed_ * Time.GetDeltaTime<float>());
	if (owner_->GetPos().x < -collider_.lock()->GetRadius() ||
		owner_->GetPos().x > ObjectManager::fieldSize_.x + collider_.lock()->GetRadius() ||
		owner_->GetPos().y <  -collider_.lock()->GetRadius() ||
		owner_->GetPos().y >ObjectManager::fieldSize_.y + collider_.lock()->GetRadius()
		)
	{
		// 範囲外の時オブジェクトを破棄する
		owner_->Destory();
	}

	// 射撃処理
	shotTimer_ += Time.GetDeltaTime<float>();
	(this->*shotFunc_)(objectManager);
}

void EnemyMove::Destory(std::unique_ptr<Object>&& obj)
{
	factory_.DeleteMoveEnemy(std::move(obj));
}

void EnemyMove::Begin(ObjectManager& objectManager)
{
	EnemyBehavior::Begin(objectManager);
	shotTimer_ = 0.0f;
}
