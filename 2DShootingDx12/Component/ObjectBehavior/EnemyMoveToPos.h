#pragma once
#include "EnemyBehavior.h"

// �w����W�܂ňړ�����G�̓���
class EnemyMoveToPos :
	public EnemyBehavior
{
public:
	EnemyMoveToPos(EnemyFactory& factory, std::shared_ptr<BulletFactory>& bulletFactory, PowerUpItemFactory& itemFactory, EffectFactory& effectFactory);
	
	/// <summary>
	/// �ړ��ڕW���Z�b�g����
	/// </summary>
	/// <param name="dest"> �ړ��ڕW </param>
	void SetDestination(const Math::Vector2& dest);

private:
	void Update(ObjectManager& objectManager) final;
	void Destory(std::unique_ptr<Object>&& obj) final;

	/// <summary>
	/// �ړ����̍X�V����
	/// </summary>
	/// <param name="objectManager"></param>
	void UpdateMove(ObjectManager& objectManager);

	/// <summary>
	/// �ˌ����̍X�V����
	/// </summary>
	/// <param name="objectManager"></param>
	void UpdateShot(ObjectManager& objectManager);

	void Begin(ObjectManager& objectManager) final;

	// �ړ��ڕW�̍��W
	Math::Vector2 dest_;

	// �ړ�����
	Math::Vector2 moveVec_;

	// �X�V����
	void (EnemyMoveToPos::* update_)(ObjectManager&);
};

