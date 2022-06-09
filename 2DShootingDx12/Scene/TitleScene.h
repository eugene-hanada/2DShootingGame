#pragma once
#include "../GameSystem/Dx12/Resource/CbValue.h"
#include "BaseScene.h"

class MaterialBase;



class TitleScene :
	public BaseScene
{
public:
	TitleScene(std::shared_ptr<RenderManager>& renderMng,Dx12Wrapper& dx12, std::shared_ptr<InputSystem>& input);
	~TitleScene();
private:
	SceneUPtr Update(SceneUPtr scene) final;
	void Draw(void) final;
	const SceneID GetID(void) const noexcept final { return SceneID::Title; }

	std::unique_ptr< MaterialBase> testMaterial_;
	std::unique_ptr< MaterialBase> testMaterial2_;
	std::shared_ptr<CbValue<float>> alpha_;
};

