#pragma once
#include "../GameSystem/Dx12/Resource/CbValue.h"
#include "BaseScene.h"

class MaterialBase;
class Dx12Resource;
class TextureData;
class UiManager;
class ObjectManager;

class TitleScene :
	public BaseScene
{
public:
	TitleScene(std::shared_ptr<RenderManager>& renderMng,Dx12Wrapper& dx12, Xaudio2& xaudio, std::shared_ptr<InputSystem>& input);
	~TitleScene();
private:
	SceneUPtr Update(SceneUPtr scene) final;
	void Draw(void) final;
	const SceneID GetID(void) const noexcept final { return SceneID::Title; }
	std::shared_ptr<TextureData> textureData_;
	std::unique_ptr<UiManager> uiManager_;
	std::unique_ptr<ObjectManager> objManager_;
};

