#pragma once
#include <string>
#include "../Component.h"
#include "../../common/AnimationData.h"


class Animator :
	public Component
{
public:
	Animator(std::shared_ptr<AnimationData>& animData);
	~Animator();
	const int GetIdx(void) const noexcept;
	const std::string& GetState(void) const;
	void SetState(const std::string& state);
	const bool IsEnd(void) const;
private:
	void Begin(void) final;
	void Update(ObjectManager& objectManager) final;
	const ComponentID GetID(void) const noexcept final { return ComponentID::Animator; }
	std::string state_;
	AnimationData::Data* data_;
	int loopCount_;
	float playTime_;
	std::vector<std::pair<int, float>>::const_iterator nowItr_;
	std::shared_ptr<AnimationData> animData_;
};

