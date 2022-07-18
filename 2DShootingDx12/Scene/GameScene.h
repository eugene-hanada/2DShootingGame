#pragma once
#include "BaseScene.h"

class ObjectManager;
class TextureData;

class GameScene :
	public BaseScene
{
public:
	GameScene(std::shared_ptr<RenderManager>& renderMng,Dx12Wrapper& dx12, std::shared_ptr<InputSystem>& input);
	~GameScene();
private:
	SceneUPtr Update(SceneUPtr scene) final;
	void Draw(void) final;
	const SceneID GetID(void) const noexcept final { return SceneID::Game; }
	std::unique_ptr<ObjectManager> objManager_;
	std::shared_ptr<TextureData> textureData_;
};

