#pragma once
#include <memory>
#include <unordered_map>
#include "../Component/ComponentID.h"

class Component;

class Object
{
	using ComponentShPtr = std::shared_ptr<Component>;

	template<class T>
	using ComponentWkPtr = std::weak_ptr<T>;

public:
	Object();
	~Object();
	void AddComponent(ComponentShPtr&& component);
	std::unique_ptr<Component>&& RemoveComponent(ComponentID id);
	void Update(void);
	
	// 後でコンセプトに置き換えとけ
	template<class T>
	ComponentWkPtr<T> GetCcomponent(Component id)
	{
		if (componentMap_.contains(id))
		{
			return ComponentWkPtr<T>(std::dynamic_pointer_cast<T>{(componentMap_.at(id))};
		}
		return ComponentWkPtr<T>{nullptr};
	}

private:
	std::unordered_map<ComponentID, ComponentShPtr> componentMap_;
};

