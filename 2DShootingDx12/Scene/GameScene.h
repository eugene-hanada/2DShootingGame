#pragma once
#include "BaseScene.h"

class ObjectManager;
class UiManager;
class TextureData;
class AnimationData;

class GameScene :
	public BaseScene
{
public:
	GameScene(std::shared_ptr<RenderManager>& renderMng,Dx12Wrapper& dx12, Xaudio2& xaudio, std::shared_ptr<InputSystem>& input);
	~GameScene();
private:
	SceneUPtr Update(SceneUPtr scene) final;
	void Draw(void) final;
	const SceneID GetID(void) const noexcept final { return SceneID::Game; }

	// オブジェクトマネージャー
	std::unique_ptr<ObjectManager> objManager_;

	// Uiのマネージャー
	std::unique_ptr< UiManager> uiManager_;

	// オブジェクト描画用レンダーターゲット
	std::unique_ptr<RenderTarget> objRt_;

	// UI描画用レンダーターゲット
	std::unique_ptr<RenderTarget> uiRt_;

	// テクスチャデータ
	std::shared_ptr<TextureData> textureData_;
};

