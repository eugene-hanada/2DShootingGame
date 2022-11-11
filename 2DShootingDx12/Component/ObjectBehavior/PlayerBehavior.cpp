#include <unordered_map>
#include "../../GameSystem/Input/InputSystem.h"
#include "../Transform.h"
#include "../../Object/Object.h"
#include "../Animator/Animator.h"
#include "../../Object/ObjectFactory/BulletFactory.h"
#include "../../Object/ObjectFactory/EffectFactory.h"
#include "PlayerBehavior.h"
#include "../../Application.h"
#include "../Collider/Collider.h"
#include "../Sound/Sound.h"
#include "../../Object/ObjectManager.h"
#include "../../common/Debug.h"

// レベル1の射撃に使う定数類
constexpr struct Shot1
{
	float speed{ 180.0f };
	float interval{ 0.2f };
} shot1;

// レベル2の射撃に使う定数類
constexpr struct Shot2
{
	float apSpeed{ 240.0f };		// AP弾のスピード
	float speed{ 360.0f };			// 普通の弾のスピード
	float interval{ 0.1f };			// 発射interval
	float radR{ Math::Deg2Rad(270.0f + 10.0f) };		// 発射の角度
	float radL{ Math::Deg2Rad(270.0f - 10.0f) };		// 発射の角度
} shot2;

// オブジェクトごとのヒット時の処理のテーブル
std::unordered_map<ObjectID, void(PlayerBehavior::*)(Collider&, ObjectManager&)> PlayerBehavior::hitFuncTbl_
{
	{ObjectID::EnemyBullet, &PlayerBehavior::HitEnemy},
	{ObjectID::PowerUpItem, &PlayerBehavior::HitPowerUpItem},

};

// 各レベルの射撃処理と次への取得数
PlayerBehavior::ShotFuncPair PlayerBehavior::shotFuncs_
{
	{&PlayerBehavior::ShotLevel1,2},
	{&PlayerBehavior::ShotLevel2,4},
	{&PlayerBehavior::ShotLevel3,0}
};

// 移動スピード
constexpr float speed_{ 300.0f };

PlayerBehavior::PlayerBehavior(std::shared_ptr<InputSystem>& input, std::shared_ptr< BulletFactory>& bulletFactory, std::shared_ptr< EffectFactory>& effectFactory) :
	input_{input}, bulletFactory_{bulletFactory}, moveStateFunc_{nullptr},effectFactory_{effectFactory},
	shotTime_{0.0f}, state_{MoveState::Other}, powerItemCount_{0}, nowLevel_{1u}
{
	nowShotItr_ = shotFuncs_.cbegin();
}

PlayerBehavior::~PlayerBehavior()
{
}

const unsigned int PlayerBehavior::GetLevel(void) const
{
	return nowLevel_;
}

void PlayerBehavior::Update(ObjectManager& objectManager)
{
	// 移動処理
	Move();

	// 射撃処理
	Shot(objectManager);
}

void PlayerBehavior::Begin(ObjectManager& objectManager)
{
	animator_ = owner_->GetCcomponent<Animator>(ComponentID::Animator);
	state_ = MoveState::Other;
	moveStateFunc_ = &PlayerBehavior::Other;
	shotTime_ = 0.0f;
	nowShotItr_ = shotFuncs_.cbegin();
	sound_ = owner_->GetCcomponent<Sound>(ComponentID::Sound);
}

void PlayerBehavior::HitPowerUpItem(Collider& collider, ObjectManager& objectManager)
{
	DebugLog("アイテムゲット");
	if (nowShotItr_ == --shotFuncs_.end())
	{
		// 最後のレベルの射撃まで到達時処理しない
		return;
	}
	powerItemCount_++;
	if (powerItemCount_ >= nowShotItr_->second)
	{
		// レベルが上がるまでの数取得しているとき
		nowLevel_++;
		++nowShotItr_;
	}
}

void PlayerBehavior::HitEnemy(Collider& collider, ObjectManager& objectManager)
{
	nowShotItr_ = shotFuncs_.cbegin();
	powerItemCount_ = 0U;
	nowLevel_ = 0u;
	effectFactory_->CreateExpM(objectManager, owner_->pos_);
	objectManager.GameEnd();
	owner_->Destory();
}

void PlayerBehavior::OnHit(Collider& collider, ObjectManager& objectManager)
{
	if (hitFuncTbl_.contains(collider.GetOnwer()->GetID()))
	{
		(this->*hitFuncTbl_[collider.GetOnwer()->GetID()])(collider, objectManager);
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
	// 特に何もしない
}

void PlayerBehavior::ShotLevel1(ObjectManager& objectManager)
{
	shotTime_ -= Time.GetDeltaTime<float>();
	if (input_->IsPressedStay(InputID::Shot) && shotTime_ <= 0.0f)
	{
		sound_.lock()->Start();
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
		sound_.lock()->Start();
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
		sound_.lock()->Start();
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


