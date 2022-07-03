#pragma once
#include <memory>
#include <list>

class Object;
class Component;
class InputSystem;

class ObjectManager
{
public:
	ObjectManager(std::shared_ptr<InputSystem>& input);
	~ObjectManager();
	void Update(void);
	void Draw(void);
private:
	std::list<std::unique_ptr<Object>> objList_;
};

