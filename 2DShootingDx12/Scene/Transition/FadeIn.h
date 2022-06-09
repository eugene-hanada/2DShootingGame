#pragma once
#include "Transition.h"
#include "../../GameSystem/Dx12/Resource/CbValue.h"

class FadeIn :
	public Transition
{
public:
	FadeIn(SceneUPtr befor, SceneUPtr after, std::shared_ptr<RenderManager>& renderMng, Dx12Wrapper& dx12, std::shared_ptr<InputSystem>& input);
	~FadeIn();
private:
	void Draw(void) final;
	bool TransitionUpdate(void);
	std::shared_ptr<CbValue<float>> alpha_;
};

