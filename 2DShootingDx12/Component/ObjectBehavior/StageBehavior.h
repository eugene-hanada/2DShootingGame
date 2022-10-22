#pragma once
#include "ObjectBehavior.h"

class AnimationData;
class EnemyFactory;

class StageBehavior :
    public ObjectBehavior
{
public:
    StageBehavior(std::shared_ptr<AnimationData>& animData);
    void Update(ObjectManager& objectManager) final;
    void Begin(void) final;
private:
    float timer_;
    std::unique_ptr<EnemyFactory> enemyFactory_;
};

