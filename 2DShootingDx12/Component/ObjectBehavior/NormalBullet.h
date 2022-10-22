#pragma once
#include "../../common/Math.h"
#include "ObjectBehavior.h" 

class BulletFactory;

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
	/// 弾を貫通させる
	/// </summary>
	/// <param name=""></param>
	void ArmorPiercing(void);

	/// <summary>
	/// ヒット時の処理
	/// </summary>
	/// <param name="collider"></param>
	void OnHit(Collider& collider);
private:
	void Update(ObjectManager& objectManager) final;
	virtual void Destory(std::unique_ptr<Object>&& obj) final;
	void Begin(void) final;
	BulletFactory& factoy_;
	Math::Vector2 moveVec_;
	float speed_;
	bool isAp_;
};

