#include <unordered_map>
#include "../../GameSystem/Input/InputSystem.h"
#include "../Transform.h"
#include "../../Object/Object.h"
#include "../Animator/Animator.h"
#include "../../Object/ObjectFactory/BulletFactory.h"
#include "PlayerBehavior.h"
#include "../../Application.h"
#include "../Collider/Collider.h"
#include "../../common/Debug.h"

constexpr struct Shot1
{
	float speed{ 180.0f };
	float interval{ 0.2f };
} shot1;


constexpr struct Shot2
{
	float apSpeed{ 240.0f };		// AP�e�̃X�s�[�h
	float speed{ 360.0f };			// ���ʂ̒e�̃X�s�[�h
	float interval{ 0.1f };			// ����interval
	float radR{ Math::Deg2Rad(270.0f + 10.0f) };		// ���˂̊p�x
	float radL{ Math::Deg2Rad(270.0f - 10.0f) };		// ���˂̊p�x
} shot2;

std::unordered_map<ObjectID, void(PlayerBehavior::*)(Collider&)> PlayerBehavior::hitFuncTbl_
{
	{ObjectID::EnemyBullet, &PlayerBehavior::HitEnemy},
	{ObjectID::PowerUpItem, &PlayerBehavior::HitPowerUpItem},

};

PlayerBehavior::ShotFuncPair PlayerBehavior::shotFuncs_
{
	{&PlayerBehavior::ShotLevel1,2},
	{&PlayerBehavior::ShotLevel2,4},
	{&PlayerBehavior::ShotLevel3,0}
};

constexpr float speed_{ 300.0f };

PlayerBehavior::PlayerBehavior(std::shared_ptr<InputSystem>& input, std::shared_ptr< BulletFactory>& bulletFactory) :
	input_{input}, bulletFactory_{bulletFactory}, moveStateFunc_{nullptr}, shotTime_{0.0f}, state_{MoveState::Other}, powerItemCount_{0}
{
	nowShotItr_ = shotFuncs_.cbegin();
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
	nowShotItr_ = shotFuncs_.cbegin();
}

void PlayerBehavior::HitPowerUpItem(Collider& collider)
{
	DebugLog("�A�C�e���Q�b�g");
	if (nowShotItr_ == --shotFuncs_.end())
	{
		return;
	}
	powerItemCount_++;
	if (powerItemCount_ >= nowShotItr_->second)
	{
		++nowShotItr_;
	}
}

void PlayerBehavior::HitEnemy(Collider& collider)
{
	nowShotItr_ = shotFuncs_.cbegin();
	powerItemCount_ = 0U;
}

void PlayerBehavior::OnHit(Collider& collider, ObjectManager& objectManager)
{
	if (hitFuncTbl_.contains(collider.GetOnwer()->GetID()))
	{
		(this->*hitFuncTbl_[collider.GetOnwer()->GetID()])(collider);
	}
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
		moveVec *= speed_ * Time.GetDeltaTime<float>();
		if (input_->IsPressedStay(InputID::Speed))
		{
			moveVec *= 0.35f;
		}
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
	// ���ɉ������Ȃ�
}

void PlayerBehavior::ShotLevel1(ObjectManager& objectManager)
{
	shotTime_ -= Time.GetDeltaTime<float>();
	if (input_->IsPressedStay(InputID::Shot) && shotTime_ <= 0.0f)
	{
		shotTime_ = shot1.interval;
		bulletFactory_->CreateNormalBullet(objectManager, owner_->pos_ + Math::leftVector2<float> *5.0f, Math::upVector2<float>, shot1.speed);
		bulletFactory_->CreateNormalBullet(objectManager, owner_->pos_ + Math::rightVector2<float> *5.0f, Math::upVector2<float>, shot1.speed);
	}
}

void PlayerBehavior::ShotLevel2(ObjectManager& objectManager)
{
	shotTime_ -= Time.GetDeltaTime<float>();
	if (input_->IsPressedStay(InputID::Shot) && shotTime_ <= 0.0f)
	{
		shotTime_ = shot2.interval;
		bulletFactory_->CreateApBullet(objectManager, owner_->pos_ + Math::leftVector2<float> *5.0f, Math::upVector2<float>, shot2.apSpeed);
		bulletFactory_->CreateApBullet(objectManager, owner_->pos_ + Math::rightVector2<float> *5.0f, Math::upVector2<float>, shot2.apSpeed);
		bulletFactory_->CreateNormalBullet(objectManager, owner_->pos_ + Math::leftVector2<float> *5.0f, Math::Vector2{std::cos(shot2.radL), std::sin(shot2.radL)}, shot2.speed);
		bulletFactory_->CreateNormalBullet(objectManager, owner_->pos_ + Math::rightVector2<float> *5.0f, Math::Vector2{ std::cos(shot2.radR), std::sin(shot2.radR) }, shot2.speed);
	}
}

void PlayerBehavior::ShotLevel3(ObjectManager& objectManager)
{
	shotTime_ -= Time.GetDeltaTime<float>();
	if (input_->IsPressedStay(InputID::Shot) && shotTime_ <= 0.0f)
	{
		shotTime_ = shot2.interval;
		missileTime_ = shot2.interval;
		bulletFactory_->CreateApBullet(objectManager, owner_->pos_ + Math::leftVector2<float> *5.0f, Math::upVector2<float>, shot2.apSpeed);
		bulletFactory_->CreateApBullet(objectManager, owner_->pos_ + Math::rightVector2<float> *5.0f, Math::upVector2<float>, shot2.apSpeed);
		bulletFactory_->CreateNormalBullet(objectManager, owner_->pos_ + Math::leftVector2<float> *5.0f, Math::Vector2{ std::cos(shot2.radL), std::sin(shot2.radL) }, shot2.speed);
		bulletFactory_->CreateNormalBullet(objectManager, owner_->pos_ + Math::rightVector2<float> *5.0f, Math::Vector2{ std::cos(shot2.radR), std::sin(shot2.radR) }, shot2.speed);
	}
}

void PlayerBehavior::Shot(ObjectManager& objectManager)
{
	(this->*(*nowShotItr_).first)(objectManager);
}


