#pragma once
#include <memory>
#include "ObjRender.h"

class Animator;

// アニメーションを描画するクラス
class AnimationRender :
    public ObjRender
{
public:
	AnimationRender();
	~AnimationRender();
private:

	void Draw(TextureSheetRender& texSheetRender) final;
	void Begin(ObjectManager& objectManager) final;
	void End(void) final;
	
	// アニメーション制御クラス
	std::weak_ptr<Animator> animator_;
};

