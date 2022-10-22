#pragma once
#include <memory>
#include "ObjectBehavior.h"

class InputSystem;
class Animator;
class BulletFactory;

class PlayerBehavior :
	public ObjectBehavior
{
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
	
	// �ړ�����
	void Move(void);

	// ���ړ����̏���
	void TiltLeft(void);

	// �E�ړ����̏���
	void TiltRight(void);

	// ���̑��ړ����̏���
	void Other(void);

	void Shot(ObjectManager& objectManager);

	void (PlayerBehavior::* moveStateFunc_)(void);

	std::shared_ptr<InputSystem> input_;
	std::weak_ptr<Animator> animator_;
	MoveState state_;
	std::shared_ptr< BulletFactory> bulletFactory_;
	float shotTime_;
};

