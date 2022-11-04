#pragma once
#include <list>
#include <memory>
#include "ComponentID.h"

class Object;
class ObjectManager;

// �I�u�W�F�N�g�ɂ�������@�\�̊��N���X
class Component
{
public:
	Component() noexcept;
	virtual ~Component();

	/// <summary>
	/// ������̃I�u�W�F�N�g�N���X���Z�b�g����
	/// </summary>
	/// <param name="owner"> ������̃I�u�W�F�N�g�N���X�̃|�C���^ </param>
	/// <returns> ������true���s��false </returns>
	bool SetOwner(Object* owner);

	/// <summary>
	/// ������̃I�u�W�F�N�g�̃|�C���^���擾����
	/// </summary>
	/// <param name=""></param>
	/// <returns> ������̃I�u�W�F�N�g�̃|�C���^ </returns>
	Object* GetOnwer(void);

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="objectManager"> �I�u�W�F�N�g�}�l�[�W���[ </param>
	virtual void Update(ObjectManager& objectManager){}

	/// <summary>
	/// �I�u�W�F�N�g���L���ɂȂ������̏���
	/// </summary>
	/// <param name=""></param>
	virtual void Begin(ObjectManager& objectManager){}

	/// <summary>
	/// �I�u�W�F�N�g�������ɂȂ������̏���
	/// </summary>
	/// <param name=""></param>
	virtual void End(void) { }

	/// <summary>
	/// ID�̎擾
	/// </summary>
	/// <param name=""></param>
	/// <returns> ID </returns>
	virtual  const ComponentID GetID(void) const noexcept = 0;

	/// <summary>
	/// �I�u�W�F�N�g���A�N�e�B�u���H
	/// </summary>
	/// <param name=""></param>
	/// <returns> �A�N�e�B�u�̎�true�A�����łȂ��Ƃ�false </returns>
	const bool IsActive(void)const { return owner_ != nullptr; }
protected:

	// ������
	Object* owner_{ nullptr };
};

