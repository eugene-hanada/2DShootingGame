#include "../../GameSystem/Dx12/Render/RenderManager.h"
#include "../../GameSystem/Dx12/Resource/RenderTarget.h"
#include "../../GameSystem/Dx12/Resource/MaterialBase.h"
#include "FadeIn.h"

constexpr float timeMax{ 2.0f };

FadeIn::FadeIn(SceneUPtr befor, SceneUPtr after, std::shared_ptr<RenderManager>& renderMng, Dx12Wrapper& dx12, Xaudio2& xaudio, std::shared_ptr<InputSystem>& input) :
	Transition{std::move(befor), std::move(after),renderMng,dx12, xaudio,input}
{
	alpha_ = std::make_shared < CbValue<float>>(dx12);
	alpha_->val_ = 0.0;
	rt_->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	alpha_->Update();
	after_->GetRenderTarget().GetMaterial().shaderResource_.emplace_back(alpha_);
}

FadeIn::~FadeIn()
{
}

void FadeIn::Draw(void)
{
	rt_->Clear();
	rt_->DrawBegin();
	renderMng_->Draw(befor_->GetRenderTarget().GetMaterial(), rt_->GetCbMat(), RenderType::Basic);
	renderMng_->Draw(after_->GetRenderTarget().GetMaterial(), rt_->GetCbMat(), RenderType::Alpha);
	rt_->DrawEnd();

}

bool FadeIn::TransitionUpdate(void)
{
	alpha_->val_ = (stepTime_ / timeMax);
	alpha_->Update();
	if (stepTime_ >= timeMax)
	{
		after_->GetRenderTarget().GetMaterial().shaderResource_.back().reset();
		return true;
	}
	return false;
}
