#pragma once
#include "BaseScene.h"

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
private:
	SceneUPtr Update(SceneUPtr scene) final;
	void Draw(void) final;
	const SceneID GetID(void) const noexcept { return SceneID::Title; }
};

