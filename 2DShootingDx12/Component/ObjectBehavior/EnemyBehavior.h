#pragma once
#include "ObjectBehavior.h"
#include <memory>
#include "../../common/Vector2.h"

class EnemyFactory;
class BulletFactory;
class PowerUpItemFactory;
class EffectFactory;
class StageBehavior;

class EnemyBehavior :
	public ObjectBehavior
{
public:
	EnemyBehavior(EnemyFactory& factory, std::shared_ptr<BulletFactory>& bulletFactory,PowerUpItemFactory& itemFactory, EffectFactory& effectFactory);
	virtual ~EnemyBehavior();

	void OnHit(Collider& collider, ObjectManager& objectManager) final;
	void SetHp(const int hp)
	{
		hp_ = hp;
	}

	void SetShotSpeed(const float speed)
	{
		shotSpeed_ = speed;
	}

	void SetBulletSpeed(const float speed)
	{
		bulletSpeed_ = speed;
	}

	void SetMoveSpeed(const float speed)
	{
		moveSpeed_ = speed;
	}
protected:

	bool IsShot(void) const
	{
		return shotTimer_ >= shotSpeed_;
	}

	EnemyFactory& factory_;
	PowerUpItemFactory& itemFactory_;
	EffectFactory& effectFactory_;
	std::shared_ptr< BulletFactory> bulletFactory_;
	int hp_;

	// 発射タイミングを図る変数
	float shotTimer_;

	// 弾のスピード
	float bulletSpeed_;

	float moveSpeed_;

private:
	// 発射スピード
	float shotSpeed_;

	

};

