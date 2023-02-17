#pragma once
#include "ObjectBehavior.h"
#include "../../common/Math.h"

class Sound;
class BulletFactory;
class ObjRender;
class EffectFactory;

class MissileBehavior :
    public ObjectBehavior
{
public:
	MissileBehavior(BulletFactory& factory, EffectFactory& effect);
	void SetMoveVec(const Math::Vector2& moveVec)
	{
		moveVec_ = moveVec;
	}
private:
	void Update(ObjectManager& objectManager) final;
	void Begin(ObjectManager& objectManager) final;
	void Destory(std::unique_ptr<Object>&& obj) final;

	void UpdateHoming(void);

	void UpdateNotHoming(void);

	void OnHit(Collider& collider, ObjectManager& objectManager) final;

	// アップデート関数の関数ポインタ
	void (MissileBehavior::* update_)(void);

	// 弾の生成用クラス
	BulletFactory& factory_;

	// エフェクト生成クラス
	EffectFactory& effect_;

	// 移動ベクトル
	Math::Vector2 moveVec_;

	// ターゲットオブジェクトのポインタ
	Object* target_;

	// サウンド
	std::weak_ptr<Sound> sound_;

	// レンダー
	std::weak_ptr< ObjRender> render_;
};

