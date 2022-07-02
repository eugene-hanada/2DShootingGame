#pragma once
#include "ComponentID.h"

class Object;

class Component
{
public:
	Component() noexcept;
	virtual ~Component();

	bool SetOwner(Object* owner);
	virtual void Update(void){}
	virtual void Start(void){}
	virtual void End(void){}
	virtual  const ComponentID GetID(void) const noexcept = 0;
protected:
	Object* owner_{ nullptr };
};

