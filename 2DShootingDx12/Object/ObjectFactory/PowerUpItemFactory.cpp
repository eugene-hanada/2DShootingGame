#include "PowerUpItemFactory.h"
#include "../Object.h"
#include "../../Component/Render/DefaultRender.h"
#include "../../Component/Collider/CircleCollider.h"
#include "../../Component/ObjectBehavior/PowerUpItemBehavior.h"
#include "../ObjectManager.h"

constexpr int itemMax{ 10 };

PowerUpItemFactory::PowerUpItemFactory()
{
	for (int i = 0; i < itemMax; i++)
	{
		objPool_.emplace_front(std::make_unique<Object>());
		behaviorLilst_.emplace_front(std::make_unique<PowerUpItemBehavior>());
		renderList_.emplace_front(std::make_shared<DefaultRender>());
		colliderList_.emplace_front(std::make_shared<CircleCollider>());
	}
}

void PowerUpItemFactory::Create(ObjectManager& objectManager, const Math::Vector2& pos)
{
	if (behaviorLilst_.empty())
	{
		return;
	}

	// オブジェクトクラスを取得
	auto obj = std::move(objPool_.front());
	objPool_.pop_front();

	obj->AddComponent(std::move(behaviorLilst_.front()));
	behaviorLilst_.pop_front();

	obj->AddComponent(std::move(renderList_.front()));
	renderList_.pop_front();

	obj->AddComponent(std::move(colliderList_.front()));
	colliderList_.pop_front();
}

void PowerUpItemFactory::Destory(std::unique_ptr<Object>&& obj)
{
	behaviorLilst_.emplace_front(std::move(obj->GetCcomponent<PowerUpItemBehavior>(ComponentID::Behavior)));
	renderList_.emplace_front(std::move(obj->GetCcomponent<DefaultRender>(ComponentID::Render)));
	colliderList_.emplace_front(std::move(obj->GetCcomponent<CircleCollider>(ComponentID::Collider)));
	objPool_.emplace_front(std::move(obj));
}
