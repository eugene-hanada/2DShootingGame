#pragma once
#include "ObjectBehavior.h"

class AnimationData;
class EnemyFactory;
class BulletFactory;
class EffectFactory;

class StageBehavior :
    public ObjectBehavior
{
public:
    StageBehavior(std::shared_ptr<AnimationData>& animData, std::shared_ptr<BulletFactory>& bulletFactory, std::shared_ptr< EffectFactory>& effectFactory);
    void Update(ObjectManager& objectManager) final;
    void Begin(void) final;
private:
    float timer_;
    std::unique_ptr<EnemyFactory> enemyFactory_;
};

