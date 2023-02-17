#pragma once
#include <memory>
#include "SceneID.h"

class RenderTarget;
class RenderManager;
class Dx12Wrapper;
class InputSystem;
class CbMatrix;
class Xaudio2;

class BaseScene
{
public:
	BaseScene(std::shared_ptr<RenderManager>& renderMng,Dx12Wrapper& dx12, Xaudio2& xaudio, std::shared_ptr<InputSystem>& input);
	virtual ~BaseScene();
	using SceneUPtr = std::unique_ptr<BaseScene>;
	virtual SceneUPtr Update(SceneUPtr scene) = 0;
	void Draw(CbMatrix& cbMat);
	virtual void Draw(void) = 0;
	RenderTarget& GetRenderTarget(void) { return *rt_; }
protected:

	// レンダーターゲット
	std::unique_ptr<RenderTarget> rt_;

	// レンダーmanager
	std::shared_ptr<RenderManager>  renderMng_;

	// 入力系
	std::shared_ptr<InputSystem> input_;

	// DirectX12のラッパークラス
	Dx12Wrapper& dx12_;

	// XAudio2のラッパークラス
	Xaudio2& xaudio_;
private:
	virtual const SceneID GetID(void) const noexcept = 0;
	

};

