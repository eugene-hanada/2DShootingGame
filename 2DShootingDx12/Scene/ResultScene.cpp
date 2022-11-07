#include "ResultScene.h"

ResultScene::ResultScene(std::shared_ptr<RenderManager>& renderMng, Dx12Wrapper& dx12, Xaudio2& xaudio, std::shared_ptr<InputSystem>& input) :
    BaseScene{renderMng, dx12, xaudio, input}
{
}

BaseScene::SceneUPtr ResultScene::Update(SceneUPtr scene)
{
    return scene;
}

void ResultScene::Draw(void)
{
}
