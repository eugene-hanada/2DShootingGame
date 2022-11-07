#pragma once
#include <memory>
#include <forward_list>
#include "../../common/Math.h"

class Component;
class Object;
class ObjectManager;
class AnimationData;
class BulletFactory;
class PowerUpItemFactory;
class EffectFactory;

class EnemyFactory
{
	using ComponentShPtr = std::shared_ptr<Component>;
public:
	EnemyFactory(std::shared_ptr<AnimationData>& animData, std::shared_ptr<BulletFactory>& bulletFactory, std::shared_ptr< EffectFactory>& effectFactory);

	void CreateMoveToPosEnemyS(ObjectManager& objManager, const Math::Vector2& start, const Math::Vector2& end);
	void CreateMoveToPosEnemyM(ObjectManager& objManager, const Math::Vector2& start, const Math::Vector2& end);
	void DestoryMoveToPosEnemy(std::unique_ptr<Object>&& obj);
private:
	std::forward_list<ComponentShPtr> moveToPosBehaviorList_;
	std::forward_list<ComponentShPtr> renderList_;
	std::forward_list<ComponentShPtr> colliderList_;
	std::forward_list<ComponentShPtr> animatorList_;
	std::forward_list<std::unique_ptr<Object>> objPool_;
	std::unique_ptr< PowerUpItemFactory> itemfactory_;
	std::shared_ptr< EffectFactory> effectFactory_;
};

