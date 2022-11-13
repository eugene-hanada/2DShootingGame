#include <Windows.h>
#include "MissileBehavior.h"
#include "../../Object/ObjectManager.h"
#include "../../Object/Object.h"
#include "../../Application.h"
#include "../Sound/Sound.h"
#include "../Collider/Collider.h"
#include "../../Object/ObjectFactory/BulletFactory.h"
#include "../Render/ObjRender.h"

constexpr float speed_{ 120.0f };

MissileBehavior::MissileBehavior(BulletFactory& factory) :
	factory_{factory},target_{nullptr},update_{nullptr}
{
}

void MissileBehavior::Update(ObjectManager& objectManager)
{
	(this->*update_)();
}

void MissileBehavior::Begin(ObjectManager& objectManager)
{
	auto& [obj,result] = objectManager.FindNearObject(ObjectID::Enemy, owner_->GetPos());
	if (result)
	{
		update_ = &MissileBehavior::UpdateHoming;
		target_ = (*obj).get();
	}
	else
	{
		update_ = &MissileBehavior::UpdateNotHoming;
	}
	sound_ = owner_->GetCcomponent<Sound>(ComponentID::Sound);
	if (!sound_.expired())
	{
		sound_.lock()->Start();
	}

	render_ = owner_->GetCcomponent<ObjRender>(ComponentID::Render);
}

void MissileBehavior::Destory(std::unique_ptr<Object>&& obj)
{
	factory_.DeleteMissile(std::move(obj));
}

void MissileBehavior::UpdateHoming(void)
{
	if (!target_->IsActive())
	{
		update_ = &MissileBehavior::UpdateNotHoming;
		return;
	}
	moveVec_ = moveVec_ + (target_->GetPos() - owner_->GetPos()).Normalized();
	moveVec_.Normalize();
	owner_->SetPos(owner_->GetPos() + moveVec_ * (speed_ * Time.GetDeltaTime<float>()));
	if (!render_.expired())
	{
		render_.lock()->SetRotation(moveVec_.GetAngle());
	}

}

void MissileBehavior::UpdateNotHoming(void)
{
	owner_->SetPos(owner_->GetPos() + moveVec_ * (speed_ * Time.GetDeltaTime<float>()));
	if (owner_->GetPos().x < 0 || owner_->GetPos().x > ObjectManager::fieldSize_.x || owner_->GetPos().y < 0 || owner_->GetPos().y >ObjectManager::fieldSize_.y)
	{
		owner_->Destory();
	}
}

void MissileBehavior::OnHit(Collider& collider, ObjectManager& objectManager)
{
	if (collider.GetOnwer()->GetID() == ObjectID::Enemy)
	{
		if (!sound_.expired())
		{
			sound_.lock()->Start();
		}
		owner_->Destory();
	}
}
