#pragma once
#include <memory>
#include "ObjectBehavior.h"

class InputSystem;

class PlayerBehavior :
	public ObjectBehavior
{
public:
	PlayerBehavior(std::shared_ptr<InputSystem>& input);
	~PlayerBehavior();
private:
	void Update(void) final;
	std::shared_ptr<InputSystem> input_;
};

