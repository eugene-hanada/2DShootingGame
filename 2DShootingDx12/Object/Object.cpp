#include "../Component/Component.h"
#include "../Component/Transform.h"
#include "../Component/ObjectBehavior/ObjectBehavior.h"
#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::AddComponent(ComponentShPtr&& component)
{
	bool rtn =component->SetOwner(this);
	rtn =  (componentMap_.try_emplace(component->GetID(), std::move(component))).second;
	isActive_ = false;
}

Object::ComponentShPtr Object::RemoveComponent(ComponentID id)
{
	auto comp = std::move(componentMap_[id]);
	comp->SetOwner(nullptr);
	componentMap_.erase(id);
	return std::move(comp);
}


void Object::Update(ObjectManager& objectManager)
{
	for (auto& comp : componentMap_)
	{
		comp.second->Update(objectManager);
	}
}

void Object::Begin(void)
{
	isActive_ = true;
	for (auto& comp : componentMap_)
	{
		comp.second->Begin();
	}
}

void Object::End(std::unique_ptr<Object>&& obj)
{
	isActive_ = false;
	for (auto& comp : componentMap_)
	{
		comp.second->End();
	}
	std::static_pointer_cast<ObjectBehavior>(componentMap_[ComponentID::Behavior])->Destory(std::move(obj));

}
