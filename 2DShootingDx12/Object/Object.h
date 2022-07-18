#pragma once
#include <memory>
#include <unordered_map>
#include "../common/Math.h"
#include "../Component/ComponentID.h"

class Component;
class Transform;
class Dx12Wrapper;

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
	void Update(void);

	void Begin(void);
	void End(void);

	// ��ŃR���Z�v�g�ɒu�������Ƃ�
	template<class T>
	ComponentWkPtr<T> GetCcomponent(ComponentID id)
	{
		if (componentMap_.contains(id))
		{
			return ComponentWkPtr<T>{std::static_pointer_cast<T>(componentMap_.at(id))};
		}
		return ComponentWkPtr<T>{};
	}

	std::shared_ptr<Transform>& GetTransform(void) { return transform_; }

private:
	std::unordered_map<ComponentID, ComponentShPtr> componentMap_;
	std::shared_ptr<Transform> transform_;
	Math::Vector2 pos_;

	friend class DefaultRender;
	friend class PlayerBehavior;
};

