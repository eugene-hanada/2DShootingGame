#pragma once
#include "../Component.h"

enum class CollType
{
	Non,
	Enemy = 1 <<0,
	Player = 1 << 1,
	All = ~Non
};

class ObjectBehavior;
class CircleCollider;
class ObjectManager;

// �����蔻��N���X
class Collider :
	public Component
{
public:
	Collider();
	~Collider();

	/// <summary>
	/// �`�F�b�N����֐�
	/// </summary>
	/// <param name="target"></param>
	virtual void Check(Collider& collider, ObjectManager& objectManager) = 0;

	/// <summary>
	/// �~�`�ƃ`�F�b�N����֐�
	/// </summary>
	/// <param name="collider"></param>
	/// <returns></returns>
	virtual bool Check(CircleCollider& collider) = 0;
	
	/// <summary>
	/// �q�b�g���̏���
	/// </summary>
	/// <param name="target"></param>
	void OnHit(Collider& collider, ObjectManager& objectManager);

	/// <summary>
	/// �^�[�Q�b�g���Z�b�g
	/// </summary>
	/// <param name=""> �^�[�Q�b�g���Z�b�g </param>
	/// <returns></returns>
	void SetTarget(int target)
	{
		targetType_ = target;
	}

	/// <summary>
	/// �^�[�Q�b�g���̎擾
	/// </summary>
	/// <returns></returns>
	int GetTarget(void)
	{
		return targetType_;
	}

	/// <summary>
	/// �����̃^�C�v���Z�b�g
	/// </summary>
	/// <param name="type"> �^�C�v </param>
	/// <returns></returns>
	void SetMyType(CollType type);
protected:

	// �����Ɋւ���N���X
	std::weak_ptr<ObjectBehavior> behavior_;

	// �����̃^�C�v
	CollType myType_;

	// ������Ƃ�^�[�Q�b�g
	int targetType_;
private:
	const ComponentID GetID(void) const noexcept final { return ComponentID::Collider; }
	virtual void Begin(void) override;
};

