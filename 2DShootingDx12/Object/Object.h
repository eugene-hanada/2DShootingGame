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
	Object(Dx12Wrapper& dx12);
	~Object();
	void AddComponent(ComponentShPtr&& component);
	ComponentShPtr RemoveComponent(ComponentID id);
	void Update(ObjectManager& objectManager);

	void Begin(std::list<std::unique_ptr<Object>>::iterator thisItr);
	void End(void);

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


private:
	std::unordered_map<ComponentID, ComponentShPtr> componentMap_;
	std::list<std::unique_ptr<Object>>::iterator thisItr_;
	Math::Vector2 pos_;

	friend class DefaultRender;
	friend class AnimationRender;
	friend class PlayerBehavior;
	friend class NormalBullet;
	friend class BulletFactory;
};

