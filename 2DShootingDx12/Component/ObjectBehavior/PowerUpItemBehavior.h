#pragma once
#include "ObjectBehavior.h"

class PowerUpItemFactory;

// �p���[�A�b�v�A�C�e���̓���
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

	// �p���[�A�b�v�A�C�e���̐����N���X
	PowerUpItemFactory& factory_;
};

