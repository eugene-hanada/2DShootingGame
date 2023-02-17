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

	// �I�u�W�F�N�g�}�l�[�W���[
	std::unique_ptr<ObjectManager> objManager_;

	// Ui�̃}�l�[�W���[
	std::unique_ptr< UiManager> uiManager_;

	// �I�u�W�F�N�g�`��p�����_�[�^�[�Q�b�g
	std::unique_ptr<RenderTarget> objRt_;

	// UI�`��p�����_�[�^�[�Q�b�g
	std::unique_ptr<RenderTarget> uiRt_;

	// �e�N�X�`���f�[�^
	std::shared_ptr<TextureData> textureData_;
};

