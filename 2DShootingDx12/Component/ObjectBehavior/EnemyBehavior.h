#pragma once
#include "ObjectBehavior.h"
#include <memory>
#include "../../common/Vector2.h"

class EnemyFactory;
class BulletFactory;

class EnemyBehavior :
	public ObjectBehavior
{
public:
	EnemyBehavior(EnemyFactory& factory, std::shared_ptr<BulletFactory>& bulletFactory);
	virtual ~EnemyBehavior();

	void OnHit(Collider& collider) final;
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
	std::shared_ptr< BulletFactory> bulletFactory_;
	int hp_;

	// ���˃^�C�~���O��}��ϐ�
	float shotTimer_;

	// �e�̃X�s�[�h
	float bulletSpeed_;

	float moveSpeed_;

private:
	// ���˃X�s�[�h
	float shotSpeed_;

	

};

