#include <Windows.h>
#include "../../Object/Object.h"
#include "../../Object/ObjectManager.h"
#include "../../Application.h"
#include "../../Object/ObjectFactory/BulletFactory.h"
#include "../../GameSystem/Window.h"
#include "NormalBullet.h"

NormalBullet::NormalBullet(BulletFactory& factory) :
	factoy_{factory}
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

void NormalBullet::Update(ObjectManager& objectManager)
{
	owner_->pos_ += moveVec_ * (speed_ * Time.GetDeltaTime<float>());
	if (owner_->pos_.x < 0 || owner_->pos_.x > App.GetWindow().GetSize<float>().x || owner_->pos_.y < 0 || owner_->pos_.y > App.GetWindow().GetSize<float>().y)
	{
		owner_->Destory();
	}
}


void NormalBullet::Destory(std::unique_ptr<Object>&& obj)
{
	factoy_.DeleteNormalBullet(std::move(obj));
}


