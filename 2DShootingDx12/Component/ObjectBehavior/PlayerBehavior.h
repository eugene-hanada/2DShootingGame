#pragma once
#include <memory>
#include <unordered_map>
#include "ObjectBehavior.h"

class InputSystem;
class Animator;
class BulletFactory;

class PlayerBehavior :
	public ObjectBehavior
{
	using ShotFuncPair =std::vector< std::pair<void(PlayerBehavior::*)(ObjectManager&), unsigned int>>;
public:
	PlayerBehavior(std::shared_ptr<InputSystem>& input, std::shared_ptr< BulletFactory>& bulletFactory);
	~PlayerBehavior();
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
	void Begin(void) final;
	
	void HitPowerUpItem(Collider& collider);

	void HitEnemy(Collider& collider);

	void OnHit(Collider& collider) final;

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

	MoveState state_;
	std::shared_ptr< BulletFactory> bulletFactory_;

	float shotTime_;

	unsigned int powerItemCount_;

	ShotFuncPair::const_iterator nowShotItr_;


	static std::unordered_map<ObjectID, void(PlayerBehavior::*)(Collider&)> hitFuncTbl_;

	

	static ShotFuncPair shotFuncs_;

};

