#include "Collider.h"

// 円形の当たり判定クラス
class CircleCollider :
	public Collider
{
public:
	CircleCollider();
	~CircleCollider();

	/// <summary>
	/// 当たり判定をチェックを開始する
	/// </summary>
	/// <param name="collider"> コライダー </param>
	/// <param name="objectManager"> オブジェクトマネージャー </param>
	void Check(Collider& collider, ObjectManager& objectManager) final;

	/// <summary>
	/// 円形との当たり判定をチェックする
	/// </summary>
	/// <param name="collider"> 円形の当たり判定 </param>
	/// <returns> 当たっているときtrue </returns>
	bool Check(CircleCollider& collider) final;

	/// <summary>
	/// 半径のセット
	/// </summary>
	/// <param name="radius"> 半径 </param>
	void SetRadius(const float radius)
	{
		radius_ = radius;
	}

	/// <summary>
	/// 半径の取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const float GetRadius(void) const
	{
		return radius_;
	}

private:
	// 半径
	float radius_;
};
