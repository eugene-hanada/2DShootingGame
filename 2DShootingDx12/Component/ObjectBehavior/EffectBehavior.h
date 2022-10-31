#pragma once
#include "ObjectBehavior.h"

class Animator;

class EffectBehavior :
    public ObjectBehavior
{
public:
private:
    void Update(ObjectManager& objectManager) final;
    void Begin(void) final;
    std::weak_ptr<Animator> animator_;
};

