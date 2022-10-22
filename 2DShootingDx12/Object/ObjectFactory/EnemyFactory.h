#pragma once
#include <memory>
#include <list>
#include "../../common/Math.h"

class Component;
class Object;
class ObjectManager;
class AnimationData;
class BulletFactory;

class EnemyFactory
{
	using ComponentShPtr = std::shared_ptr<Component>;
public:
	EnemyFactory(std::shared_ptr<AnimationData>& animData, std::shared_ptr<BulletFactory>& bulletFactory);

	void CreateMoveToPosEnemy(ObjectManager& objManager, const Math::Vector2& start, const Math::Vector2& end);
	void DestoryMoveToPosEnemy(std::unique_ptr<Object>&& obj);
private:
	std::list<ComponentShPtr> moveToPosBehaviorList_;
	std::list<ComponentShPtr> renderList_;
	std::list<ComponentShPtr> colliderList_;
	std::list<ComponentShPtr> animatorList_;
	std::list<std::unique_ptr<Object>> objPool_;
};

