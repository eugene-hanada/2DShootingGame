#pragma once

class Object;

class Component
{
public:
	Component(Object& owner);
	virtual ~Component();
	virtual void Update(void);
	virtual void Start(void);
	virtual void End(void);
protected:
	Object& owner_;
};

