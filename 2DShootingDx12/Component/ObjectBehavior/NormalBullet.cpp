#include <Windows.h>
#include "../../Object/Object.h"
#include "../../Object/ObjectManager.h"
#include "../../Application.h"
#include "../../Object/ObjectFactory/BulletFactory.h"
#include "../../GameSystem/Window.h"
#include "NormalBullet.h"
#include "../Collider/Collider.h"
#include "../../Object/Object.h"

#include "../../common/Debug.h"

NormalBullet::NormalBullet(BulletFactory& factory) :
	factoy_{factory},speed_{0.0f}, isAp_{false}
{
}

NormalBullet::~NormalBullet()
{
}

void NormalBullet::SetMoveVec(const Math::Vector2& moveVec)
{
	moveVec_ = moveVec;
}

void NormalBullet::SetSpeed(float speed)
{
	speed_ = speed;
}

void NormalBullet::ArmorPiercing(void)
{
	isAp_ = true;
}

void NormalBullet::OnHit(Collider& collider)
{
	if (isAp_ )
	{
		return;
	}

	if ((collider.GetOnwer()->GetID() == shooterID_) || (collider.GetOnwer()->GetID() == ObjectID::EnemyBullet) || (collider.GetOnwer()->GetID() == ObjectID::PlayerBullet))
	{
		return;
	}

	owner_->Destory();
}

void NormalBullet::Update(ObjectManager& objectManager)
{
	owner_->pos_ += moveVec_ * (speed_ * Time.GetDeltaTime<float>());
	//DebugLog("À•Wx=", owner_->pos_.x, "y=", owner_->pos_.y);
	if (owner_->pos_.x < 0 || owner_->pos_.x > App.GetWindow().GetSize<float>().x || owner_->pos_.y < 0 || owner_->pos_.y > App.GetWindow().GetSize<float>().y)
	{
		owner_->Destory();
	}
}


void NormalBullet::Destory(std::unique_ptr<Object>&& obj)
{
	factoy_.DeleteNormalBullet(std::move(obj));
}



