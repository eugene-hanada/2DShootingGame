#pragma once
#include <string>
#include "ObjRender.h"

// ���ʂ̕`�������N���X
class DefaultRender :
	public ObjRender
{
public:
	DefaultRender();
	~DefaultRender();
private:
	void Draw(TextureSheetRender& texSheetRender) final;
};

