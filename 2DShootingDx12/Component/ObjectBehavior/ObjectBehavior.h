#pragma once
#include "../Component.h"
class ObjectBehavior :
    public Component
{
public:
    ObjectBehavior();
    virtual ~ObjectBehavior();
private:
    const ComponentID GetID(void) const noexcept final { return ComponentID::Behavior; }
};

