#pragma once
#include <memory>
#include <forward_list>
#include "../../common/Math.h"

class ObjectManager;
class Object;
class Component;

// �e�̐����N���X
class BulletFactory
{
public:
	using ComponentShPtr = std::shared_ptr<Component>;
	BulletFactory();

	/// <summary>
	/// �ʏ�̒e�̐���
	/// </summary>
	/// <param name="objectManager"> �I�u�W�F�N�g�}�l�[�W���[ </param>
	/// <param name="pos"> ���W </param>
	/// <param name="moveVec"> �ړ����� </param>
	/// <param name="speed"> �ړ��X�s�[�h </param>
	void CreateNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec, float speed);

	/// <summary>
	/// �ʏ�̒e�̍폜
	/// </summary>
	/// <param name="obj"> �I�u�W�F�N�g </param>
	void DeleteNormalBullet(std::unique_ptr<Object>&& obj);

	/// <summary>
	/// �G�̒e�̐���
	/// </summary>
	/// <param name="objectManager"> �}�l�[�W���[ </param>
	/// <param name="pos"> ���W </param>
	/// <param name="moveVec"> �ړ����� </param>
	/// <param name="speed"> �X�s�[�h </param>
	void CreateEnemyNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec, float speed);
	
	/// <summary>
	/// �ђʂ���e�̐���
	/// </summary>
	/// <param name="objectManager"> �I�u�W�F�N�g�}�l�[�W���[ </param>
	/// <param name="pos"> ���W </param>
	/// <param name="moveVec"> �ړ����� </param>
	/// <param name="speed"> �X�s�[�h </param>
	void CreateApBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec, float speed);
private:
	std::forward_list<ComponentShPtr> normalShotBehaviorList_;
	std::forward_list<ComponentShPtr> renderList_;
	std::forward_list<ComponentShPtr> colliderList_;
	std::forward_list<std::unique_ptr<Object>> objPool_;

};

