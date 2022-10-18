#pragma once
#include "ObjectBehavior.h"

class EnemyFactory;

class EnemyBehavior :
    public ObjectBehavior
{
public:
    EnemyBehavior(EnemyFactory& factory);
    void Update(ObjectManager& objectManager) final;
    virtual void Destory(std::unique_ptr<Object>&& obj) final;
private:
    EnemyFactory& factory_;
};

