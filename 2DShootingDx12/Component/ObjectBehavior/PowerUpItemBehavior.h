#pragma once
#include "ObjectBehavior.h"

class PowerUpItemFactory;

class PowerUpItemBehavior :
    public ObjectBehavior
{
public:
    PowerUpItemBehavior(PowerUpItemFactory& factory);
    ~PowerUpItemBehavior();
private:
    void Update(ObjectManager& objectManager) final;
    void Begin(void) final;
    void OnHit(Collider& collider, ObjectManager& objectManager) final;
    void Destory(std::unique_ptr<Object>&& obj) final;
    PowerUpItemFactory& factory_;
};

