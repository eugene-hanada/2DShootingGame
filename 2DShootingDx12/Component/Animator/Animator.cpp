#include <Windows.h>
#include "../../Application.h"
#include "../../Object/Object.h"
#include "../Render/ObjRender.h"
#include "Animator.h"

Animator::Animator(std::shared_ptr<AnimationData>& animData) :
	animData_{animData}
{
	playTime_ = 0.0f;
}

Animator::~Animator()
{
}

const int Animator::GetIdx(void) const noexcept
{
	return nowItr_->first;
}

const std::string& Animator::GetState(void) const
{
	return state_;
}

void Animator::SetState(const std::string& state)
{
	if (state_ != state)
	{
		// ���݂̃X�e�[�g�ƈ�v���Ă��Ȃ��Ƃ�
		state_ = state;
		auto render = owner_->GetCcomponent<ObjRender>(ComponentID::Render);
		if (!render.expired())
		{
			// �A�j���[�V�������Z�b�g����
			data_ = animData_->GetData(render.lock()->GetImgKey(), state_);
			nowItr_ = data_->idxData.begin();
			playTime_ = 0.0f;
			loopCount_ = 0;
		}
	}
	
}

const bool Animator::IsEnd(void) const
{
	return loopCount_ >= data_->loop && data_->loop != -1;
}

void Animator::Begin(ObjectManager& objectManager)
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

void Animator::Update(ObjectManager& objectManager)
{
	playTime_ += Time.GetDeltaTime<float>();
	if (nowItr_->second <= playTime_)
	{
		++nowItr_;
		playTime_ = 0.0f;
		if (nowItr_ == data_->idxData.end())
		{
			// �I�[�܂ōĐ������Ƃ�
			loopCount_++;
			if (data_->loop == -1 || loopCount_ < data_->loop)
			{
				// ���[�v���Đ��������͖������[�v�Đ��̎�
				nowItr_ = data_->idxData.begin();
			}
			else
			{
				// ���[�v���Ȃ��Ƃ����[���ێ�
				nowItr_ = --data_->idxData.end();
			}
		}
		
	}
}
