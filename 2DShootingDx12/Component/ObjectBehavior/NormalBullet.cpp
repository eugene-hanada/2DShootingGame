#include <Windows.h>
#include "../../Object/Object.h"
#include "../../Object/ObjectManager.h"
#include "../../Application.h"
#include "../../Object/ObjectFactory/BulletFactory.h"
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
	owner_->pos_ += moveVec_ * (moveVec_ * Time.GetDeltaTime<float>());
}

void NormalBullet::Destory(ObjectManager& objectManager)
{
	factoy_.DeleteNormalBullet(*owner_, objectManager);
}
