#pragma once
#include "BaseScene.h"
class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
private:
	SceneUPtr Update(SceneUPtr scene) final;
	void Draw(void) final;
	const SceneID GetID(void) const noexcept { return SceneID::Game; }
};

