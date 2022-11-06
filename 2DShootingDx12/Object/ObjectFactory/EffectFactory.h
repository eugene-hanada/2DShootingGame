#pragma once
#include <memory>
#include <forward_list>
#include <string>
#include "../../common/Math.h"

class Component;
class ObjectManager;
class Object;
class AnimationData;
class Xaudio2;

class EffectFactory
{
public:
	using ComponentShPtr = std::shared_ptr<Component>;
	EffectFactory(std::shared_ptr<AnimationData>& animData, Xaudio2& xaudio2);
	void CreateExpM(ObjectManager& objectManager, const Math::Vector2& pos);
	void CreateScore(ObjectManager& objectManager, const Math::Vector2& pos,const std::string& scoreStr);
	void Delete(std::unique_ptr<Object>&& obj);
	void DeleteExpM(std::unique_ptr<Object>&& obj);
	void DeleteExpS(std::unique_ptr<Object>&& obj);
	void DeleteScore(std::unique_ptr<Object>&& obj);
private:
	std::forward_list<std::unique_ptr<Object>> objPool_;
	std::forward_list<ComponentShPtr> animatorPool_;
	std::forward_list<ComponentShPtr> renderPool_;
	std::forward_list<ComponentShPtr> behaviorPool_;
	std::forward_list<ComponentShPtr> expMSound_;
	std::forward_list<ComponentShPtr> expSSound_;
	
};

