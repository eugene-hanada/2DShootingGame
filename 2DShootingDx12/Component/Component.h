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
	Object* GetOnwer(void);
	virtual void Update(ObjectManager& objectManager){}
	virtual void Begin(void){}
	virtual void End(void) { }
	virtual  const ComponentID GetID(void) const noexcept = 0;
	const bool IsActive(void)const { return owner_ != nullptr; }
protected:
	Object* owner_{ nullptr };
};

