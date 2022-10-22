#pragma once
#include <memory>
#include <unordered_map>
#include "../common/Math.h"
#include "../Component/ComponentID.h"

class Component;
class Transform;
class Dx12Wrapper;
class ObjectManager;

enum class ObjectID
{
	Player,
	PlayerBullet,
	Enemy,
	EnemyBullet,
};

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

	void Begin(void);
	void End(std::unique_ptr<Object>&& obj);

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

	bool HaveComponent(ComponentID id)
	{
		return componentMap_.contains(id);
	}

	void Destory(void)
	{
		isActive_ = false;
	}

	const bool IsActive(void) const
	{
		return isActive_;
	}

	const Math::Vector2& GetPos(void) const&
	{
		return pos_;
	}

	void SetPos(const Math::Vector2& pos)
	{
		pos_ = pos;
	}

	ObjectID GetID(void)
	{
		return objID_;
	}

	void SetID(ObjectID id)
	{
		objID_ = id;
	}
private:
	std::unordered_map<ComponentID, ComponentShPtr> componentMap_;
	Math::Vector2 pos_;
	bool isActive_;
	ObjectID objID_;
	friend class DefaultRender;
	friend class AnimationRender;
	friend class PlayerBehavior;
	friend class NormalBullet;
	friend class BulletFactory;
	friend class EnemyBehavior;
	friend class EnemyMoveToPos;
};

