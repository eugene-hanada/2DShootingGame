#pragma once
#include "SceneID.h"



class BaseScene
{
public:
	virtual void Update(void) = 0;
	virtual void Draw(void);
private:
	virtual const SceneID GetID(void) const noexcept = 0;
};

