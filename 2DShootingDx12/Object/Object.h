#pragma once
#include <memory>
#include <unordered_map>
#include "../common/Math.h"
#include "../Component/ComponentID.h"

class Component;
class Transform;
class Dx12Wrapper;
class ObjectManager;

class Object
{
	using ComponentShPtr = std::shared_ptr<Component>;

	template<class T>
	using ComponentWkPtr = std::weak_ptr<T>;

public:
	Object();
	~Object();
	void AddComponent(ComponentShPtr&& component);
	ComponentShPtr RemoveComponent(ComponentID id);
	void Update(ObjectManager& objectManager);

	void Begin(std::list<std::unique_ptr<Object>>::iterator itr);
	void End(ObjectManager& objectManager);

	// 後でコンセプトに置き換えとけ
	template<class T = Component>
	ComponentWkPtr<T> GetCcomponent(ComponentID id)
	{
		if (componentMap_.contains(id))
		{
			return ComponentWkPtr<T>{std::static_pointer_cast<T>(componentMap_.at(id))};
		}
		return ComponentWkPtr<T>{};
	}

	void Destory(void)
	{
		isActive_ = false;
	}

	const bool IsActive(void) const
	{
		return isActive_;
	}

private:
	std::unordered_map<ComponentID, ComponentShPtr> componentMap_;
	std::list<std::unique_ptr<Object>>::iterator itr_;
	Math::Vector2 pos_;
	bool isActive_;
	friend class DefaultRender;
	friend class AnimationRender;
	friend class PlayerBehavior;
	friend class NormalBullet;
	friend class BulletFactory;
};

