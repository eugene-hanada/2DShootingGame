#pragma once
#include "EnemyBehavior.h"
class EnemyMove :
    public EnemyBehavior
{
public:
    EnemyMove(EnemyFactory& factory, std::shared_ptr<BulletFactory>& bulletFactory, PowerUpItemFactory& itemFactory, EffectFactory& effectFactory);
private:
    void Update(ObjectManager& objectManager) final;
    void Destory(std::unique_ptr<Object>&& obj) final;
    void Begin(ObjectManager& objectManager) final;
};

