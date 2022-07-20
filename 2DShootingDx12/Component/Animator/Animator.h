#pragma once
#include "../Component.h"
class Animator :
    public Component
{
public:
    Animator();
    ~Animator();
    const int GetIdx(void) const noexcept;
private:
    void Begin(void) final;
    void Update(void) final;
    const ComponentID GetID(void) const noexcept final { return ComponentID::Animator; }
};

