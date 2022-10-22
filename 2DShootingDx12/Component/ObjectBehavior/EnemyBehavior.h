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
	void Update(ObjectManager& objectManager) final;
	virtual void Destory(std::unique_ptr<Object>&& obj) final;

	void SetDestination(const Math::Vector2& dest);
	void OnHit(Collider& collider);
	void SetHp(const int hp)
	{
		hp_ = hp;
	}
private:
	void Begin(void) final;
	void UpdateMove(ObjectManager& objectManager);
	void UpdateShot(ObjectManager& objectManager);

	EnemyFactory& factory_;
	std::shared_ptr< BulletFactory> bulletFactory_;
	Math::Vector2 dest_;
	Math::Vector2 moveVec_;
	void (EnemyBehavior::* update_)(ObjectManager&);
	int hp_;
};

