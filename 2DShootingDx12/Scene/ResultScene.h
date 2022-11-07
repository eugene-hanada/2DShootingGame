#pragma once
#include "BaseScene.h"
class ResultScene :
    public BaseScene
{
public:
	ResultScene(std::shared_ptr<RenderManager>& renderMng, Dx12Wrapper& dx12, Xaudio2& xaudio, std::shared_ptr<InputSystem>& input);
private:
	SceneUPtr Update(SceneUPtr scene) final;
	void Draw(void) final;
	const SceneID GetID(void) const noexcept final { return SceneID::Result; }
};

