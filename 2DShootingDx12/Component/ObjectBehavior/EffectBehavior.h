#pragma once
#include "ObjectBehavior.h"
#include <unordered_map>

class Animator;
class EffectFactory;

enum class EffectType
{
	ExpM,
	ExpS,
	Score
};

class EffectBehavior :
	public ObjectBehavior
{
public:

	EffectBehavior(EffectFactory& factory);
	void SetType(const EffectType type)
	{
		type_ = type;
	}

private:
	void Update(ObjectManager& objectManager) final;
	void Begin(ObjectManager& objectManager) final;
	void Destory(std::unique_ptr<Object>&& obj);
	void DestoryExpM(std::unique_ptr<Object>&& obj);
	void DestoryExpS(std::unique_ptr<Object>&& obj);
	void DestoryScore(std::unique_ptr<Object>&& obj);
	std::weak_ptr<Animator> animator_;
	EffectFactory& factory_;
	EffectType type_;

	static std::unordered_map<EffectType, void(EffectBehavior::*)(std::unique_ptr<Object>&&)> destoryFunc_;
};

