#pragma once
#include "../../common/Math.h"
#include "ObjectBehavior.h" 

class BulletFactory;

// 通常の弾の動き
class NormalBullet :
	public ObjectBehavior
{
public:
	NormalBullet(BulletFactory& factory);
	~NormalBullet();

	/// <summary>
	/// 移動方向
	/// </summary>
	/// <param name="moveVec"> 移動方向 </param>
	void SetMoveVec(const Math::Vector2& moveVec);

	/// <summary>
	/// スピードのセット
	/// </summary>
	/// <param name="speed"> スピード </param>
	void SetSpeed(float speed);

	/// <summary>
	/// 弾を貫通させる状態にする
	/// </summary>
	/// <param name=""></param>
	void ArmorPiercing(void);

	/// <summary>
	/// ヒット時の処理
	/// </summary>
	/// <param name="collider"></param>
	void OnHit(Collider& collider);

	/// <summary>
	/// 発射したオブジェクトのID
	/// </summary>
	/// <param name="id"> オブジェクトのID </param>
	void SetShooterID(ObjectID id)
	{
		shooterID_ = id;
	}

private:
	void Update(ObjectManager& objectManager) final;
	virtual void Destory(std::unique_ptr<Object>&& obj) final;

	// 弾の生成クラス
	BulletFactory& factoy_;

	// 移動方向
	Math::Vector2 moveVec_;

	// スピード
	float speed_;

	// 貫通弾か？
	bool isAp_;

	// 自らを発射したオブジェクトのID
	ObjectID shooterID_;
};

