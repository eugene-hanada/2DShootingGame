#pragma once
#include "ObjectBehavior.h"
#include <memory>
#include <unordered_map>
#include "../../common/Vector2.h"

class EnemyFactory;
class BulletFactory;
class PowerUpItemFactory;
class EffectFactory;
class StageBehavior;
class CircleCollider;

// �ˌ��^�C�v
enum class ShotType
{
	Normal,		// �ʏ�
	ThreeWay,	// 3Way
	Random,		// �����_��
};

// �G�̓����̊��N���X
class EnemyBehavior :
	public ObjectBehavior
{
public:
	using ShotFunc = void (EnemyBehavior::*)(ObjectManager&);
	EnemyBehavior(EnemyFactory& factory, std::shared_ptr<BulletFactory>& bulletFactory,PowerUpItemFactory& itemFactory, EffectFactory& effectFactory);
	virtual ~EnemyBehavior();

	/// <summary>
	/// HP���Z�b�g����
	/// </summary>
	/// <param name="hp"> �Z�b�g����HP </param>
	void SetHp(const int hp)
	{
		hp_ = hp;
	}

	/// <summary>
	/// ���˃X�s�[�h
	/// </summary>
	/// <param name="speed"> ���˃X�s�[�h </param>
	void SetShotSpeed(const float speed)
	{
		shotSpeed_ = speed;
	}

	/// <summary>
	/// �e�̃X�s�[�h���Z�b�g
	/// </summary>
	/// <param name="speed"> �e�̃X�s�[�h </param>
	void SetBulletSpeed(const float speed)
	{
		bulletSpeed_ = speed;
	}

	/// <summary>
	/// �ړ��X�s�[�h
	/// </summary>
	/// <param name="speed"> �ړ��X�s�[�h </param>
	void SetMoveSpeed(const float speed)
	{
		moveSpeed_ = speed;
	}

	/// <summary>
	/// ���S���ɉ��Z�����X�R�A
	/// </summary>
	/// <param name="score"> ���S���ɉ��Z�����X�R�A </param>
	void SetScore(unsigned int score)
	{
		score_ = score;
	}

	void SetShotFunc(const ShotType type);

protected:

	/// <summary>
	/// �q�b�g���̏���
	/// </summary>
	/// <param name="collider"> ����̓����蔻�� </param>
	/// <param name="objectManager"> �I�u�W�F�N�g�}�l�[�W���[ </param>
	void OnHit(Collider& collider, ObjectManager& objectManager) final;

	/// <summary>
	/// ���˂ł��邩�H
	/// </summary>
	/// <param name=""></param>
	/// <returns> ���˂ł��鎞true�A���˂ł��Ȃ��Ƃ�false </returns>
	bool IsShot(void) const
	{
		return shotTimer_ >= shotSpeed_;
	}

	void Begin(ObjectManager& objectManager) override;

	/// <summary>
	/// ���ʂɔ��˂���
	/// </summary>
	/// <param name="objectManager"></param>
	void ShotFront(ObjectManager& objectManager);

	/// <summary>
	/// �O�����ɔ��˂���
	/// </summary>
	/// <param name="objectManager"></param>
	void Shot3Way(ObjectManager& objectManager);

	/// <summary>
	/// �����_���ɔ��˂���
	/// </summary>
	/// <param name="objectManager"></param>
	void ShotRandom(ObjectManager& objectManager);

	// ���ˏ����̊֐��|�C���^
	void (EnemyBehavior::* shotFunc_)(ObjectManager&);

	// �G�̐����N���X
	EnemyFactory& factory_;

	// �p���[�A�b�v�A�C�e���̐����N���X
	PowerUpItemFactory& itemFactory_;

	// �G�t�F�N�g�����N���X
	EffectFactory& effectFactory_;

	// �e�̐����N���X
	std::shared_ptr< BulletFactory> bulletFactory_;

	// �X�e�[�W�N���X
	std::weak_ptr<StageBehavior> stage_;

	// �R���C�_�[
	std::weak_ptr<CircleCollider> collider_;

	// hp
	int hp_;

	// ���˃^�C�~���O��}��ϐ�
	float shotTimer_;

	// �e�̃X�s�[�h
	float bulletSpeed_;

	// �ړ��X�s�[�h
	float moveSpeed_;

	// �|���ꂽ�Ƃ����Z�����score
	unsigned int score_;

private:
	
	
	// ���˃X�s�[�h
	float shotSpeed_;

	// �ˌ��^�C�v���Ƃ̊֐��̃e�[�u��
	static std::unordered_map<ShotType, ShotFunc> shotFuncTbl_;

};

