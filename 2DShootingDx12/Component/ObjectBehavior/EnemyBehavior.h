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

	void SetScore(unsigned int score)
	{
		score_ = score;
	}

protected:

	bool IsShot(void) const
	{
		return shotTimer_ >= shotSpeed_;
	}

	void Begin(ObjectManager& objectManager) override;

	EnemyFactory& factory_;
	PowerUpItemFactory& itemFactory_;
	EffectFactory& effectFactory_;
	std::shared_ptr< BulletFactory> bulletFactory_;

	std::weak_ptr<StageBehavior> stage_;

	int hp_;

	// ���˃^�C�~���O��}��ϐ�
	float shotTimer_;

	// �e�̃X�s�[�h
	float bulletSpeed_;

	float moveSpeed_;

	// �|���ꂽ�Ƃ����Z�����score
	unsigned int score_;

private:
	
	// ���˃X�s�[�h
	float shotSpeed_;

	

};

