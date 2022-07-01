#pragma once
#include <memory>
#include <list>

class Object;
class Component;

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
	void Update(void);
private:
	std::list<std::unique_ptr<Object>> objList_;

};

