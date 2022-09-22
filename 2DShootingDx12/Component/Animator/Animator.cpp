#include <Windows.h>
#include "../../Application.h"
#include "../../Object/Object.h"
#include "../Render/ObjRender.h"
#include "Animator.h"

Animator::Animator(std::shared_ptr<AnimationData>& animData) :
	animData_{animData}
{
}

Animator::~Animator()
{
}

const int Animator::GetIdx(void) const noexcept
{
	return 0;
}

const std::string& Animator::GetState(void) const
{
	return state_;
}

void Animator::SetState(const std::string& state)
{
	state_ = state;
}

void Animator::Begin(void)
{
	auto render = owner_->GetCcomponent<ObjRender>(ComponentID::Render);
	if (!render.expired())
	{
		data_ = animData_->GetData(render.lock()->GetImgKey(), state_);
		nowItr_ = data_->idxData.begin();
		playTime_ = 0.0f;
		loopCount_ = 0;
	}
}

void Animator::Update(void)
{
	playTime_ += Time.GetDeltaTime<float>();
	if (nowItr_->second <= playTime_)
	{
		loopCount_++;
		++nowItr_;
		if (nowItr_ == data_->idxData.end())
		{
			if (data_->loop == -1 || loopCount_ <= data_->loop)
			{
				nowItr_ = --data_->idxData.end();
			}
			else
			{
				nowItr_ = data_->idxData.begin();
			}
		}
		
	}
}
