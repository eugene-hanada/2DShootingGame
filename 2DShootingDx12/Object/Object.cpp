#include "../Component/Component.h"
#include "../Component/Transform.h"
#include "Object.h"

Object::Object(Dx12Wrapper& dx12)
{
	transform_ = std::make_shared<Transform>(dx12);
}

Object::~Object()
{
}

void Object::AddComponent(ComponentShPtr&& component)
{
	bool rtn =component->SetOwner(this);
	rtn =  (componentMap_.try_emplace(component->GetID(), std::move(component))).second;
	
}

Object::ComponentShPtr Object::RemoveComponent(ComponentID id)
{
	auto comp = std::move(componentMap_[id]);
	componentMap_.erase(id);
	return std::move(comp);
}


void Object::Update(void)
{
	for (auto& comp : componentMap_)
	{
		comp.second->Update();
	}
}

void Object::Begin(void)
{
	for (auto& comp : componentMap_)
	{
		comp.second->Begin();
	}
}

void Object::End(void)
{
	for (auto& comp : componentMap_)
	{
		comp.second->End();
	}
}
