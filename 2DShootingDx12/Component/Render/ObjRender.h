#pragma once
#include <string>
#include "../Component.h"

class TextureSheetRender;
class CbMatrix;

class ObjRender :
	public Component
{
public:
	ObjRender() noexcept;
	virtual ~ObjRender();
	virtual void Draw(TextureSheetRender& texSheetRender) = 0;
	void SetImgKey(const std::string& imgKey)
	{
		imgKey_ = imgKey;
	}
protected:
	std::string imgKey_;
private:
	const ComponentID GetID(void) const noexcept final { return ComponentID::Render; }
};

