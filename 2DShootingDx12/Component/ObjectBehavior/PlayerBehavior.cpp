#include "../../GameSystem/Input/InputSystem.h"
#include "../Transform.h"
#include "../../Object/Object.h"
#include "PlayerBehavior.h"

PlayerBehavior::PlayerBehavior(std::shared_ptr<InputSystem>& input) :
	input_{input}
{
}

PlayerBehavior::~PlayerBehavior()
{
}

void PlayerBehavior::Update(void)
{
	Math::Vector2 moveVec;
	bool isMove = false;
	if (input_->IsPressedStay(InputID::Up))
	{
		isMove = true;
		moveVec += Math::upVector2<float> * 1.0f;
	}
	if (input_->IsPressedStay(InputID::Down))
	{
		isMove = true;
		moveVec += Math::downVector2<float> *1.0f;
	}
	if (input_->IsPressedStay(InputID::Right))
	{
		isMove = true;
		moveVec += Math::rightVector2<float> *1.0f;
	}
	if (input_->IsPressedStay(InputID::Left))
	{
		isMove = true;
		moveVec += Math::leftVector2<float> *1.0f;
	}

	if (isMove)
	{
		moveVec.Normalize();
		moveVec *= 5.0f;
		owner_->pos_ += moveVec;
	}
}

void PlayerBehavior::Begin(void)
{
	
}

