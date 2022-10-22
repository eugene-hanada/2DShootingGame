#pragma once
#include <memory>
#include <list>
#include "../../common/Math.h"

class ObjectManager;
class Object;
class Component;

class BulletFactory
{
public:
	using ComponentShPtr = std::shared_ptr<Component>;
	BulletFactory();
	void CreateNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec);
	void DeleteNormalBullet(std::unique_ptr<Object>&& obj);

	void CreateEnemyNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec);
	void DeleteEnemyNormalBullet(std::unique_ptr<Object>&& obj);
private:
	void CreateNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos);
	std::list<ComponentShPtr> normalShotBehaviorList_;
	std::list<ComponentShPtr> renderList_;
	std::list<ComponentShPtr> colliderList_;
	std::list<std::unique_ptr<Object>> objPool_;

};

