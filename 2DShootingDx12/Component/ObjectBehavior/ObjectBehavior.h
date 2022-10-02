#pragma once
#include "../Component.h"
class ObjectBehavior :
    public Component
{
public:
    ObjectBehavior();
    virtual ~ObjectBehavior();
    virtual void Destory(std::unique_ptr<Object>&& obj){}
private:
    const ComponentID GetID(void) const noexcept final { return ComponentID::Behavior; }
};

