#include "../../GameSystem/Dx12/Render/RenderManager.h"
#include "../../GameSystem/Dx12/Resource/RenderTarget.h"
#include "../../Application.h"
#include "Transition.h"

Transition::Transition(SceneUPtr befor, SceneUPtr after, std::shared_ptr<RenderManager>& renderMng, Dx12Wrapper& dx12, std::shared_ptr<InputSystem>& input) :
	BaseScene{renderMng,dx12,input}, stepTime_{0.0f}
{
}

Transition::~Transition()
{
}

BaseScene::SceneUPtr Transition::Update(SceneUPtr scene)
{
	stepTime_ += Time.GetDeltaTime<float>();
	if (TransitionUpdate())
	{
		return std::move(after_);
	}
	return scene;
}

void Transition::Draw(void)
{
	befor_->Draw();
	after_->Draw();

	rt_->Clear();
	rt_->DrawBegin();
	renderMng_->Draw(befor_->GetRenderTarget().GetMaterial(), rt_->GetCbMat(), RenderType::Basic);
	renderMng_->Draw(after_->GetRenderTarget().GetMaterial(), rt_->GetCbMat(), RenderType::Basic);
	rt_->DrawEnd();
}
