#pragma once
#include "EnemyBehavior.h"
class EnemyMove :
    public EnemyBehavior
{
public:
    EnemyMove(EnemyFactory& factory, std::shared_ptr<BulletFactory>& bulletFactory, PowerUpItemFactory& itemFactory, EffectFactory& effectFactory);

    /// <summary>
    /// 移動方向をセット
    /// </summary>
    /// <param name="moveDir"></param>
    void SetMoveDir(const Math::Vector2 moveDir)
    {
        moveDir_ = moveDir;
    }
private:
    void Update(ObjectManager& objectManager) final;
    void Destory(std::unique_ptr<Object>&& obj) final;
    void Begin(ObjectManager& objectManager) final;

    // 移動方向
    Math::Vector2 moveDir_;
};

