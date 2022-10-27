#pragma once
#include <memory>
#include <forward_list>
#include "../../common/Math.h"

class ObjectManager;
class Object;
class Component;

class BulletFactory
{
public:
	using ComponentShPtr = std::shared_ptr<Component>;
	BulletFactory();
	void CreateNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec, float speed);
	void DeleteNormalBullet(std::unique_ptr<Object>&& obj);

	void CreateEnemyNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec, float speed);
	
	void CreateApBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec, float speed);
private:
	std::forward_list<ComponentShPtr> normalShotBehaviorList_;
	std::forward_list<ComponentShPtr> renderList_;
	std::forward_list<ComponentShPtr> colliderList_;
	std::forward_list<std::unique_ptr<Object>> objPool_;

};

