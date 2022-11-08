#pragma once
#include "../../common/Math.h"
#include "ObjectBehavior.h" 

class BulletFactory;

// �ʏ�̒e�̓���
class NormalBullet :
	public ObjectBehavior
{
public:
	NormalBullet(BulletFactory& factory);
	~NormalBullet();

	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="moveVec"> �ړ����� </param>
	void SetMoveVec(const Math::Vector2& moveVec);

	/// <summary>
	/// �X�s�[�h�̃Z�b�g
	/// </summary>
	/// <param name="speed"> �X�s�[�h </param>
	void SetSpeed(float speed);

	/// <summary>
	/// �e���ђʂ������Ԃɂ���
	/// </summary>
	/// <param name=""></param>
	void ArmorPiercing(void);

	/// <summary>
	/// �q�b�g���̏���
	/// </summary>
	/// <param name="collider"></param>
	void OnHit(Collider& collider);

	/// <summary>
	/// ���˂����I�u�W�F�N�g��ID
	/// </summary>
	/// <param name="id"> �I�u�W�F�N�g��ID </param>
	void SetShooterID(ObjectID id)
	{
		shooterID_ = id;
	}

private:
	void Update(ObjectManager& objectManager) final;
	virtual void Destory(std::unique_ptr<Object>&& obj) final;

	// �e�̐����N���X
	BulletFactory& factoy_;

	// �ړ�����
	Math::Vector2 moveVec_;

	// �X�s�[�h
	float speed_;

	// �ђʒe���H
	bool isAp_;

	// ����𔭎˂����I�u�W�F�N�g��ID
	ObjectID shooterID_;
};

