#include "Object.h"
#include "../Component/ObjectBehavior/PlayerBehavior.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	auto& p = objList_.emplace_back(std::make_unique<Object>());
	p->AddComponent(std::make_unique<PlayerBehavior>());
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Update(void)
{
	for (auto& obj : objList_)
	{
		obj.Update();
	}
}
