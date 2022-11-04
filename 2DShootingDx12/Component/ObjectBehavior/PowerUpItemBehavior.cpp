#include "PowerUpItemBehavior.h"
#include <Windows.h>
#include "../Collider/Collider.h"
#include "../../Object/Object.h"
#include "../../Object/ObjectManager.h"
#include "../../Application.h"
#include "../../Object/ObjectFactory/PowerUpItemFactory.h"
#include "../../common/Debug.h"

constexpr float startDistance{ 150.0f };
constexpr float speed{ 180.0f };

PowerUpItemBehavior::PowerUpItemBehavior(PowerUpItemFactory& factory) :
	factory_{factory}
{
}

PowerUpItemBehavior::~PowerUpItemBehavior()
{
}

void PowerUpItemBehavior::Update(ObjectManager& objectManager)
{
	auto& [itr, rtn] = objectManager.FindObject(ObjectID::Player);
	if (rtn)
	{
		auto vec = ((*itr)->GetPos() - owner_->GetPos());
		if (vec.SqMagnitude() <= Math::Square(startDistance))
		{
			owner_->SetPos(owner_->GetPos() + (vec.Normalized() * App.GetTime().GetDeltaTime<float>() * speed));
			DebugLog("ƒAƒCƒeƒ€‹zˆø");
		}
	}
}

void PowerUpItemBehavior::Begin(ObjectManager& objectManager)
{
}

void PowerUpItemBehavior::OnHit(Collider& collider, ObjectManager& objectManager)
{
	if (collider.GetOnwer()->GetID() == ObjectID::Player)
	{
		owner_->Destory();
	}
}

void PowerUpItemBehavior::Destory(std::unique_ptr<Object>&& obj)
{
	factory_.Destory(std::move(obj));
}
