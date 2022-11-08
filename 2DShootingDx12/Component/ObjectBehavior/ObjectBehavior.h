#pragma once
#include "../Component.h"

class Collider;

// �I�u�W�F�N�g�̓����Ɋւ���N���X
class ObjectBehavior :
	public Component
{
public:
	ObjectBehavior();
	virtual ~ObjectBehavior();

	/// <summary>
	/// �j�����̏���
	/// </summary>
	/// <param name="obj"> �j������I�u�W�F�N�g </param>
	virtual void Destory(std::unique_ptr<Object>&& obj){}

	/// <summary>
	/// �q�b�g���̏���
	/// </summary>
	/// <param name="collider"> ����R���C�_�[ </param>
	/// <param name="objectManager"> �I�u�W�F�N�g�}�l�[�W���[ </param>
	virtual void OnHit(Collider& collider, ObjectManager& objectManager){};
private:
	const ComponentID GetID(void) const noexcept final { return ComponentID::Behavior; }
};

