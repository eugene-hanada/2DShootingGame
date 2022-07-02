#include "../../GameSystem/Input/InputSystem.h"
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
}
