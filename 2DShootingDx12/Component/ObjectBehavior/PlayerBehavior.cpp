#include "../../GameSystem/Input/InputSystem.h"
#include "../Transform.h"
#include "../../Object/Object.h"
#include "../Animator/Animator.h"
#include "../../Object/ObjectFactory/BulletFactory.h"
#include "PlayerBehavior.h"
#include "../../Application.h"
#include "../../common/Debug.h"

PlayerBehavior::PlayerBehavior(std::shared_ptr<InputSystem>& input) :
	input_{input}
{
	bulletFactory_ = std::make_unique<BulletFactory>();
}

PlayerBehavior::~PlayerBehavior()
{
}

void PlayerBehavior::Update(ObjectManager& objectManager)
{
	Move();
	Shot(objectManager);
}

void PlayerBehavior::Begin(void)
{
	animator_ = owner_->GetCcomponent<Animator>(ComponentID::Animator);
	state_ = MoveState::Other;
	moveStateFunc_ = &PlayerBehavior::Other;
	shotTime_ = 0.0f;
}

void PlayerBehavior::Move(void)
{
	Math::Vector2 moveVec;
	bool isMove = false;
	if (input_->IsPressedStay(InputID::Up))
	{
		state_ = MoveState::Other;
		isMove = true;
		moveVec += Math::upVector2<float> *1.0f;
	}
	if (input_->IsPressedStay(InputID::Down))
	{
		state_ = MoveState::Other;
		isMove = true;
		moveVec += Math::downVector2<float> *1.0f;
	}
	if (input_->IsPressedStay(InputID::Right))
	{
		isMove = true;
		moveVec += Math::rightVector2<float> *1.0f;

		if (state_ == MoveState::Other)
		{
			if (!animator_.expired())
			{
				state_ = MoveState::TiltRight;
				animator_.lock()->SetState("TiltRight");
				moveStateFunc_ = &PlayerBehavior::TiltRight;
			}
		}

	}
	if (input_->IsPressedStay(InputID::Left))
	{
		isMove = true;
		moveVec += Math::leftVector2<float> *1.0f;
		if (state_ == MoveState::Other)
		{
			if (!animator_.expired())
			{
				state_ = MoveState::TiltLeft;
				animator_.lock()->SetState("TiltLeft");
				moveStateFunc_ = &PlayerBehavior::TiltLeft;
			}
		}
	}

	if (isMove)
	{
		moveVec.Normalize();
		moveVec *= 5.0f;
		owner_->pos_ += moveVec;
	}
	else
	{
		state_ = MoveState::Other;
		if (!animator_.expired())
		{
			animator_.lock()->SetState("Non");
			moveStateFunc_ = &PlayerBehavior::Other;
		}
	}

	(this->*moveStateFunc_)();
}

void PlayerBehavior::TiltLeft(void)
{
	if (!animator_.expired())
	{
		if (animator_.lock()->IsEnd())
		{
			state_ = MoveState::Left;
			animator_.lock()->SetState("Left");
			moveStateFunc_ = &PlayerBehavior::Other;
		}
	}
}

void PlayerBehavior::TiltRight(void)
{
	if (!animator_.expired())
	{
		if (animator_.lock()->IsEnd())
		{
			state_ = MoveState::Right;
			animator_.lock()->SetState("Right");
			moveStateFunc_ = &PlayerBehavior::Other;
		}
	}
}

void PlayerBehavior::Other(void)
{
	// “Á‚É‰½‚à‚µ‚È‚¢
}

void PlayerBehavior::Shot(ObjectManager& objectManager)
{
	shotTime_ -= Time.GetDeltaTime<float>();
	if (input_->IsPressedStay(InputID::Shot1) && shotTime_ <= 0.0f)
	{
		shotTime_ = 0.15f;
		bulletFactory_->CreateNormalBullet(objectManager, owner_->pos_, Math::zeroVector2<float>);
	}
}


