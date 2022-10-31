#pragma once
#include "EnemyBehavior.h"
class EnemyMoveToPos :
	public EnemyBehavior
{
public:
	EnemyMoveToPos(EnemyFactory& factory, std::shared_ptr<BulletFactory>& bulletFactory, PowerUpItemFactory& itemFactory);
	void SetDestination(const Math::Vector2& dest);

private:
	void Update(ObjectManager& objectManager) final;
	void Destory(std::unique_ptr<Object>&& obj) final;
	void UpdateMove(ObjectManager& objectManager);
	void UpdateShot(ObjectManager& objectManager);
	void Begin(void) final;
	Math::Vector2 dest_;
	Math::Vector2 moveVec_;
	void (EnemyMoveToPos::* update_)(ObjectManager&);
};

