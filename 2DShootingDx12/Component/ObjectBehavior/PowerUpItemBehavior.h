#pragma once
#include "ObjectBehavior.h"
class PowerUpItemBehavior :
    public ObjectBehavior
{
public:
private:
    void OnHit(Collider& collider) final;
};

