#include "../Component/Component.h"
#include "Object.h"

void Object::AddComponent(ComponentShPtr&& component)
{
	bool rtn =component->SetOwner(this);
	rtn =  (componentMap_.try_emplace(component->GetID(), std::move(component))).second;
	
}

std::unique_ptr<Component>&& Object::RemoveComponent(ComponentID id)
{
	auto comp = std::move(componentMap_[id]);
	componentMap_.erase(id);
	return std::move(comp);
}


void Object::Update(void)
{
}
