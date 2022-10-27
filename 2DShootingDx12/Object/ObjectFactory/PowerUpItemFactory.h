#pragma once
#include <memory>
#include <forward_list>
#include "../../common/Math.h"

class Object;
class Component;
class ObjectManager;

class PowerUpItemFactory
{
	using ComponentShPtr = std::shared_ptr<Component>;
public:
	PowerUpItemFactory();
	void Create(ObjectManager& objectManager, const Math::Vector2& pos);
	void Destory(std::unique_ptr<Object>&& obj);
private:
	std::forward_list<ComponentShPtr> behaviorLilst_;
	std::forward_list<ComponentShPtr> renderList_;
	std::forward_list<ComponentShPtr> colliderList_;
	std::forward_list<std::unique_ptr<Object>> objPool_;
};

