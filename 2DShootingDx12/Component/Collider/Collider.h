#pragma once
#include "../Component.h"

class ObjectBehavior

class Collider :
    public Component
{
public:

private:
    const ComponentID GetID(void) const noexcept final { return ComponentID::Collider; }
    virtual void Begin(void) override;
    std::weak_ptr<ObjectBehavior>
};

