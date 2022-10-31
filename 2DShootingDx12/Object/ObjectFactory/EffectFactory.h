#pragma once
#include <memory>
#include <forward_list>
#include "../../common/Math.h"

class Component;
class ObjectManager;
class Object;
class AnimationData;

class EffectFactory
{
public:
	using ComponentShPtr = std::shared_ptr<Component>;
	EffectFactory(std::shared_ptr<AnimationData>& animData);
	void CreateExpM(ObjectManager& objectManager, const Math::Vector2& pos);
	void Delete(std::unique_ptr<Object>&& obj);
private:
	std::forward_list<std::unique_ptr<Object>> objPool_;
	std::forward_list<ComponentShPtr> animatorPool_;
	std::forward_list<ComponentShPtr> renderPool_;
	std::forward_list<ComponentShPtr> behaviorPool_;
};

