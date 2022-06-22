#pragma once
#include <memory>

class Component;

class Object
{
public:
	Object();
	~Object();
	void AddComponent(std::unique_ptr<Component>&& component);
	std::unique_ptr<Component>&& RemoveComponent(void);
private:
};

