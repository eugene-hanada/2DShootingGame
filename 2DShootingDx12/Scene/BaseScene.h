#pragma once
#include <memory>
#include "SceneID.h"



class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	using SceneUPtr = std::unique_ptr<BaseScene>;
	virtual SceneUPtr Update(SceneUPtr scene) = 0;
	virtual void Draw(void) = 0;
private:
	SceneUPtr scene_;
private:
	virtual const SceneID GetID(void) const noexcept = 0;
	

};

