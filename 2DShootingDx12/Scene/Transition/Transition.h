#pragma once
#include "../BaseScene.h"
class Transition :
    public BaseScene
{
public:
    Transition(SceneUPtr befor, SceneUPtr after ,std::shared_ptr<RenderManager>& renderMng, Dx12Wrapper& dx12, Xaudio2& xaudio, std::shared_ptr<InputSystem>& input);
    virtual ~Transition();
protected:
    virtual bool TransitionUpdate(void) = 0;
    SceneUPtr befor_;
    SceneUPtr after_;

    // �o�ߎ���
    float stepTime_;
private:
    SceneUPtr Update(SceneUPtr scene) final;
    const SceneID GetID(void) const noexcept final { return SceneID::Transition; }
};

