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
		owner_->GetTransform()->SetPos({ 0.0f, -1.0f });
		owner_->GetTransform()->Update();
	}
	if (input_->IsPressedStay(InputID::Down))
	{
		owner_->GetTransform()->SetPos({ 0.0f, -1.0f });
		owner_->GetTransform()->Update();
	}
}

void PlayerBehavior::Begin(void)
{
	owner_->GetTransform()->SetPos({ 0.0f,0.0f });
	owner_->GetTransform()->Update();
}

