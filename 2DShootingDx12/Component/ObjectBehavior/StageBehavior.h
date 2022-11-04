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
    void Begin(ObjectManager& objectManager) final;
    const unsigned int GetScore(void) const
    {
        return score_;
    }

    void AddScore(unsigned int addValue);

    void SubScore(unsigned int subValue);

private:
    float timer_;
    std::unique_ptr<EnemyFactory> enemyFactory_;
    unsigned int score_;
};

