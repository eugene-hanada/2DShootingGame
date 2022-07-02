#include "../Component/Component.h"
#include "Object.h"

void Object::AddComponent(ComponentUptr&& component)
{
	bool rtn =component->SetOwner(this);
	rtn =  (componentMap_.try_emplace(component->GetID(), std::move(component))).second;
	
}


void Object::Update(void)
{
}
