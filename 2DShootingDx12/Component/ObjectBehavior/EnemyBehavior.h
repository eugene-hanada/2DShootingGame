#pragma once
#include "ObjectBehavior.h"
#include <memory>
#include <unordered_map>
#include "../../common/Vector2.h"

class EnemyFactory;
class BulletFactory;
class PowerUpItemFactory;
class EffectFactory;
class StageBehavior;
class CircleCollider;

// 射撃タイプ
enum class ShotType
{
	Normal,		// 通常
	ThreeWay,	// 3Way
	Random,		// ランダム
};

// 敵の動きの基底クラス
class EnemyBehavior :
	public ObjectBehavior
{
public:
	using ShotFunc = void (EnemyBehavior::*)(ObjectManager&);
	EnemyBehavior(EnemyFactory& factory, std::shared_ptr<BulletFactory>& bulletFactory,PowerUpItemFactory& itemFactory, EffectFactory& effectFactory);
	virtual ~EnemyBehavior();

	/// <summary>
	/// HPをセットする
	/// </summary>
	/// <param name="hp"> セットするHP </param>
	void SetHp(const int hp)
	{
		hp_ = hp;
	}

	/// <summary>
	/// 発射スピード
	/// </summary>
	/// <param name="speed"> 発射スピード </param>
	void SetShotSpeed(const float speed)
	{
		shotSpeed_ = speed;
	}

	/// <summary>
	/// 弾のスピードをセット
	/// </summary>
	/// <param name="speed"> 弾のスピード </param>
	void SetBulletSpeed(const float speed)
	{
		bulletSpeed_ = speed;
	}

	/// <summary>
	/// 移動スピード
	/// </summary>
	/// <param name="speed"> 移動スピード </param>
	void SetMoveSpeed(const float speed)
	{
		moveSpeed_ = speed;
	}

	/// <summary>
	/// 死亡時に加算されるスコア
	/// </summary>
	/// <param name="score"> 死亡時に加算されるスコア </param>
	void SetScore(unsigned int score)
	{
		score_ = score;
	}

	void SetShotFunc(const ShotType type);

protected:

	/// <summary>
	/// ヒット時の処理
	/// </summary>
	/// <param name="collider"> 相手の当たり判定 </param>
	/// <param name="objectManager"> オブジェクトマネージャー </param>
	void OnHit(Collider& collider, ObjectManager& objectManager) final;

	/// <summary>
	/// 発射できるか？
	/// </summary>
	/// <param name=""></param>
	/// <returns> 発射できる時true、発射できないときfalse </returns>
	bool IsShot(void) const
	{
		return shotTimer_ >= shotSpeed_;
	}

	void Begin(ObjectManager& objectManager) override;

	/// <summary>
	/// 正面に発射する
	/// </summary>
	/// <param name="objectManager"></param>
	void ShotFront(ObjectManager& objectManager);

	/// <summary>
	/// 三方向に発射する
	/// </summary>
	/// <param name="objectManager"></param>
	void Shot3Way(ObjectManager& objectManager);

	/// <summary>
	/// ランダムに発射する
	/// </summary>
	/// <param name="objectManager"></param>
	void ShotRandom(ObjectManager& objectManager);

	// 発射処理の関数ポインタ
	void (EnemyBehavior::* shotFunc_)(ObjectManager&);

	// 敵の生成クラス
	EnemyFactory& factory_;

	// パワーアップアイテムの生成クラス
	PowerUpItemFactory& itemFactory_;

	// エフェクト生成クラス
	EffectFactory& effectFactory_;

	// 弾の生成クラス
	std::shared_ptr< BulletFactory> bulletFactory_;

	// ステージクラス
	std::weak_ptr<StageBehavior> stage_;

	// コライダー
	std::weak_ptr<CircleCollider> collider_;

	// hp
	int hp_;

	// 発射タイミングを図る変数
	float shotTimer_;

	// 弾のスピード
	float bulletSpeed_;

	// 移動スピード
	float moveSpeed_;

	// 倒されたとき加算されるscore
	unsigned int score_;

private:
	
	
	// 発射スピード
	float shotSpeed_;

	// 射撃タイプごとの関数のテーブル
	static std::unordered_map<ShotType, ShotFunc> shotFuncTbl_;

};

