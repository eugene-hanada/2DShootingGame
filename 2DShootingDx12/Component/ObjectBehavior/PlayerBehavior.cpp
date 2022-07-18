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
	if (input_->IsPressedStay(InputID::Up))
	{
		owner_->pos_ += Math::upVector2<float> * 1.0f;
	}
	if (input_->IsPressedStay(InputID::Down))
	{
		owner_->pos_ += Math::downVector2<float> *1.0f;
	}
}

void PlayerBehavior::Begin(void)
{
	owner_->GetTransform()->SetPos({ 0.0f,0.0f });
	owner_->GetTransform()->Update();
}

