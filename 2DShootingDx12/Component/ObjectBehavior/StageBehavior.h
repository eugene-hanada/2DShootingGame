#pragma once
#include "ObjectBehavior.h"
class StageBehavior :
    public ObjectBehavior
{
public:
    StageBehavior();
    void Update(ObjectManager& objectManager) final;
    void Begin(void) final;
private:
    float timer_;
};

