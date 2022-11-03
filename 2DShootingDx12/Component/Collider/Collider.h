#pragma once
#include "../Component.h"

enum class CollType
{
	Non,
	Enemy = 1 <<0,
	Player = 1 << 1,
	All = ~Non
};

class ObjectBehavior;
class CircleCollider;
class ObjectManager;

// 当たり判定クラス
class Collider :
	public Component
{
public:
	Collider();
	~Collider();

	/// <summary>
	/// チェックする関数
	/// </summary>
	/// <param name="target"></param>
	virtual void Check(Collider& collider, ObjectManager& objectManager) = 0;

	/// <summary>
	/// 円形とチェックする関数
	/// </summary>
	/// <param name="collider"></param>
	/// <returns></returns>
	virtual bool Check(CircleCollider& collider) = 0;
	
	/// <summary>
	/// ヒット時の処理
	/// </summary>
	/// <param name="target"></param>
	void OnHit(Collider& collider, ObjectManager& objectManager);

	/// <summary>
	/// ターゲットをセット
	/// </summary>
	/// <param name=""> ターゲットをセット </param>
	/// <returns></returns>
	void SetTarget(int target)
	{
		targetType_ = target;
	}

	/// <summary>
	/// ターゲットをの取得
	/// </summary>
	/// <returns></returns>
	int GetTarget(void)
	{
		return targetType_;
	}

	/// <summary>
	/// 自分のタイプをセット
	/// </summary>
	/// <param name="type"> タイプ </param>
	/// <returns></returns>
	void SetMyType(CollType type);
protected:

	// 動きに関するクラス
	std::weak_ptr<ObjectBehavior> behavior_;

	// 自分のタイプ
	CollType myType_;

	// 判定をとるターゲット
	int targetType_;
private:
	const ComponentID GetID(void) const noexcept final { return ComponentID::Collider; }
	virtual void Begin(void) override;
};

