#pragma once
#include "ObjectBehavior.h"

class PowerUpItemFactory;

// パワーアップアイテムの動き
class PowerUpItemBehavior :
	public ObjectBehavior
{
public:
	PowerUpItemBehavior(PowerUpItemFactory& factory);
	~PowerUpItemBehavior();
private:
	void Update(ObjectManager& objectManager) final;
	void Begin(ObjectManager& objectManager) final;
	void OnHit(Collider& collider, ObjectManager& objectManager) final;
	void Destory(std::unique_ptr<Object>&& obj) final;

	// パワーアップアイテムの生成クラス
	PowerUpItemFactory& factory_;
};

