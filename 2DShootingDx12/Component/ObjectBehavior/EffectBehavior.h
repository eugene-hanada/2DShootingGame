#pragma once
#include "ObjectBehavior.h"

class Animator;
class EffectFactory;

class EffectBehavior :
    public ObjectBehavior
{
public:
    EffectBehavior(EffectFactory& factory);
private:
    void Update(ObjectManager& objectManager) final;
    void Begin(ObjectManager& objectManager) final;
    void Destory(std::unique_ptr<Object>&& obj);
    std::weak_ptr<Animator> animator_;
    EffectFactory& factory_;
};

