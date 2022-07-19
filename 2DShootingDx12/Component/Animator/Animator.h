#pragma once
#include "../Component.h"
class Animator :
    public Component
{
public:
    Animator();
    ~Animator();

private:
    void Begin(void) final;
    void Update(void) final;
    void Begin(void) final;
    const ComponentID GetID(void) const noexcept final { return ComponentID::Animator; }
};

