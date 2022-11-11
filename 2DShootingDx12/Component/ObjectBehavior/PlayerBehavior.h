#pragma once
#include <memory>
#include <unordered_map>
#include "ObjectBehavior.h"

class InputSystem;
class Animator;
class BulletFactory;
class EffectFactory;
class Sound;

// �v���C���[�̓���
class PlayerBehavior :
	public ObjectBehavior
{
	using ShotFuncPair =std::vector< std::pair<void(PlayerBehavior::*)(ObjectManager&), unsigned int>>;
public:
	PlayerBehavior(std::shared_ptr<InputSystem>& input, std::shared_ptr< BulletFactory>& bulletFactory, std::shared_ptr< EffectFactory>& effectFactory);
	~PlayerBehavior();

	const unsigned int GetLevel(void) const;
private:

	enum class MoveState
	{
		Left,
		TiltLeft,
		Right,
		TiltRight,
		Other
	};

	void Update(ObjectManager& objectManager) final;
	void Begin(ObjectManager& objectManager) final;
	
	/// <summary>
	/// �p���[�A�b�v�A�C�e���Ɠ����������̏���
	/// </summary>
	/// <param name="collider"> ����R���C�_�[ </param>
	/// <param name="objectManager"> �I�u�W�F�N�g�}�l�[�W���[ </param>
	void HitPowerUpItem(Collider& collider, ObjectManager& objectManager);

	/// <summary>
	/// �G�Ɠ����������̏���
	/// </summary>
	/// <param name="collider"> ����R���C�_�[ </param>
	/// <param name="objectManager"> �I�u�W�F�N�g�}�l�[�W���[ </param>
	void HitEnemy(Collider& collider, ObjectManager& objectManager);

	void OnHit(Collider& collider, ObjectManager& objectManager) final;

	/// <summary>
	/// �ړ����̏���
	/// </summary>
	/// <param name=""></param>
	void Move(void);

	/// <summary>
	/// ���ړ����̏���
	/// </summary>
	/// <param name=""></param>
	void TiltLeft(void);

	/// <summary>
	/// �E�ړ����̏���
	/// </summary>
	/// <param name=""></param>
	void TiltRight(void);

	/// <summary>
	/// �E�ړ����̏���
	/// </summary>
	/// <param name=""></param>
	void Other(void);

	/// <summary>
	/// level1�̎ˌ�����
	/// </summary>
	/// <param name="objectManager"></param>
	void ShotLevel1(ObjectManager& objectManager);

	/// <summary>
	/// level2�̎ˌ�����
	/// </summary>
	/// <param name="objectManager"></param>
	void ShotLevel2(ObjectManager& objectManager);

	/// <summary>
	/// level3�̎ˌ�����
	/// </summary>
	/// <param name="objectManager"></param>
	void ShotLevel3(ObjectManager& objectManager);

	/// <summary>
	/// �ˌ�����
	/// </summary>
	/// <param name="objectManager"></param>
	void Shot(ObjectManager& objectManager);

	// �ړ����̏���
	void (PlayerBehavior::* moveStateFunc_)(void);

	// ���͌n
	std::shared_ptr<InputSystem> input_;

	// �A�j���[�V�����n
	std::weak_ptr<Animator> animator_;

	// �T�E���h
	std::weak_ptr <Sound> sound_;

	// �ړ����
	MoveState state_;

	// �e�̐����N���X
	std::shared_ptr< BulletFactory> bulletFactory_;

	// �G�t�F�N�g�����N���X
	std::shared_ptr< EffectFactory> effectFactory_;

	// �ˌ��^�C��
	float shotTime_;

	// �~�T�C���^�C��
	float missileTime_;

	// �p���[�A�b�v�A�C�e���̎擾��
	unsigned int powerItemCount_;

	// ���݂̃��x��
	unsigned int nowLevel_;

	// �ˌ�����
	ShotFuncPair::const_iterator nowShotItr_;

	// �q�b�g���̏����̃e�[�u��
	static std::unordered_map<ObjectID, void(PlayerBehavior::*)(Collider&, ObjectManager&)> hitFuncTbl_;

	// ���փ��x���A�b�v����܂ł̃p���[�A�b�v�A�C�e���̎擾���Ƃ��̃��x���̔��ˏ����̊֐����܂Ƃ߂�����
	static ShotFuncPair shotFuncs_;

};

