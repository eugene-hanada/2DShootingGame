#pragma once
#include "Transition.h"
#include "../../GameSystem/Dx12/Resource/CbValue.h"

class FadeIn :
	public Transition
{
public:
	FadeIn(SceneUPtr befor, SceneUPtr after, std::shared_ptr<RenderManager>& renderMng, Dx12Wrapper& dx12, Xaudio2& xaudio, std::shared_ptr<InputSystem>& input);
	~FadeIn();
private:
	void Draw(void) final;
	bool TransitionUpdate(void);

	// 定数バッファ
	std::shared_ptr<CbValue<float>> alpha_;
};

