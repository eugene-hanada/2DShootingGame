#pragma once
#include <list>
#include <memory>
#include "ComponentID.h"

class Object;
class ObjectManager;

class Component
{
public:
	Component() noexcept;
	virtual ~Component();

	bool SetOwner(Object* owner);
	virtual void Update(ObjectManager& objectManager){}
	virtual void Begin(void){}
	virtual void End(ObjectManager& objectManager) { }
	virtual  const ComponentID GetID(void) const noexcept = 0;
	virtual void Destory(void){}
	const bool IsActive(void)const { return owner_ != nullptr; }
protected:
	Object* owner_{ nullptr };
};

