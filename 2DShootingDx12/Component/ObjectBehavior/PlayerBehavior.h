#pragma once
#include <memory>
#include <unordered_map>
#include "ObjectBehavior.h"

class InputSystem;
class Animator;
class BulletFactory;
class EffectFactory;
class Sound;

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
	
	void HitPowerUpItem(Collider& collider, ObjectManager& objectManager);

	void HitEnemy(Collider& collider, ObjectManager& objectManager);

	void OnHit(Collider& collider, ObjectManager& objectManager) final;

	// �ړ�����
	void Move(void);

	// ���ړ����̏���
	void TiltLeft(void);

	// �E�ړ����̏���
	void TiltRight(void);

	// ���̑��ړ����̏���
	void Other(void);

	void ShotLevel1(ObjectManager& objectManager);

	void ShotLevel2(ObjectManager& objectManager);

	void ShotLevel3(ObjectManager& objectManager);

	void Shot(ObjectManager& objectManager);

	void (PlayerBehavior::* moveStateFunc_)(void);

	std::shared_ptr<InputSystem> input_;

	std::weak_ptr<Animator> animator_;

	std::weak_ptr <Sound> sound_;

	MoveState state_;
	std::shared_ptr< BulletFactory> bulletFactory_;
	std::shared_ptr< EffectFactory> effectFactory_;

	float shotTime_;

	float missileTime_;

	unsigned int powerItemCount_;

	unsigned int nowLevel_;

	ShotFuncPair::const_iterator nowShotItr_;



	static std::unordered_map<ObjectID, void(PlayerBehavior::*)(Collider&, ObjectManager&)> hitFuncTbl_;

	

	static ShotFuncPair shotFuncs_;

};

