#pragma once
#include <memory>
#include "ObjectBehavior.h"

class InputSystem;
class Animator;

class PlayerBehavior :
	public ObjectBehavior
{
public:
	PlayerBehavior(std::shared_ptr<InputSystem>& input);
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
	
	void TiltLeft(void);
	void TiltRight(void);
	void Other(void);

	void (PlayerBehavior::* moveStateFunc_)(void);

	std::shared_ptr<InputSystem> input_;
	std::weak_ptr<Animator> animator_;
	MoveState state_;
};

