#pragma once
#include <memory>
#include <unordered_map>
#include "../Component/ComponentID.h"

class Component;

class Object
{
	using ComponentUptr = std::unique_ptr<Component>;
public:
	Object();
	~Object();
	void AddComponent(ComponentUptr&& component);
	std::unique_ptr<Component>&& RemoveComponent(void);
	void Update(void);
private:
	std::unordered_map<ComponentID, ComponentUptr> componentMap_;
};

