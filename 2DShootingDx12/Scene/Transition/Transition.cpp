#include "../../GameSystem/Dx12/Render/RenderManager.h"
#include "../../GameSystem/Dx12/Resource/RenderTarget.h"
#include "../../Application.h"
#include "Transition.h"

Transition::Transition(SceneUPtr befor, SceneUPtr after, std::shared_ptr<RenderManager>& renderMng, Dx12Wrapper& dx12, Xaudio2& xaudio, std::shared_ptr<InputSystem>& input) :
	BaseScene{renderMng,dx12,xaudio,input}, stepTime_{0.0f},befor_{std::move(befor)}, after_{std::move(after)}
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

