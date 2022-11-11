#pragma once
#include <memory>
#include <unordered_map>
#include "ObjectBehavior.h"

class InputSystem;
class Animator;
class BulletFactory;
class EffectFactory;
class Sound;

// プレイヤーの動き
class PlayerBehavior :
	public ObjectBehavior
{
	using ShotFuncPair =std::vector< std::pair<void(PlayerBehavior::*)(ObjectManager&), unsigned int>>;
public:
	PlayerBehavior(std::shared_ptr<InputSystem>& input, std::shared_ptr< BulletFactory>& bulletFactory, std::shared_ptr< EffectFactory>& effectFactory);
	~PlayerBehavior();

	const unsigned int GetLevel(void) const;
private:

	enum class MoveState
	{
		Left,
		TiltLeft,
		Right,
		TiltRight,
		Other
	};

	void Update(ObjectManager& objectManager) final;
	void Begin(ObjectManager& objectManager) final;
	
	/// <summary>
	/// パワーアップアイテムと当たった時の処理
	/// </summary>
	/// <param name="collider"> 相手コライダー </param>
	/// <param name="objectManager"> オブジェクトマネージャー </param>
	void HitPowerUpItem(Collider& collider, ObjectManager& objectManager);

	/// <summary>
	/// 敵と当たった時の処理
	/// </summary>
	/// <param name="collider"> 相手コライダー </param>
	/// <param name="objectManager"> オブジェクトマネージャー </param>
	void HitEnemy(Collider& collider, ObjectManager& objectManager);

	void OnHit(Collider& collider, ObjectManager& objectManager) final;

	/// <summary>
	/// 移動時の処理
	/// </summary>
	/// <param name=""></param>
	void Move(void);

	/// <summary>
	/// 左移動時の処理
	/// </summary>
	/// <param name=""></param>
	void TiltLeft(void);

	/// <summary>
	/// 右移動時の処理
	/// </summary>
	/// <param name=""></param>
	void TiltRight(void);

	/// <summary>
	/// 右移動時の処理
	/// </summary>
	/// <param name=""></param>
	void Other(void);

	/// <summary>
	/// level1の射撃処理
	/// </summary>
	/// <param name="objectManager"></param>
	void ShotLevel1(ObjectManager& objectManager);

	/// <summary>
	/// level2の射撃処理
	/// </summary>
	/// <param name="objectManager"></param>
	void ShotLevel2(ObjectManager& objectManager);

	/// <summary>
	/// level3の射撃処理
	/// </summary>
	/// <param name="objectManager"></param>
	void ShotLevel3(ObjectManager& objectManager);

	/// <summary>
	/// 射撃処理
	/// </summary>
	/// <param name="objectManager"></param>
	void Shot(ObjectManager& objectManager);

	// 移動時の処理
	void (PlayerBehavior::* moveStateFunc_)(void);

	// 入力系
	std::shared_ptr<InputSystem> input_;

	// アニメーション系
	std::weak_ptr<Animator> animator_;

	// サウンド
	std::weak_ptr <Sound> sound_;

	// 移動状態
	MoveState state_;

	// 弾の生成クラス
	std::shared_ptr< BulletFactory> bulletFactory_;

	// エフェクト生成クラス
	std::shared_ptr< EffectFactory> effectFactory_;

	// 射撃タイム
	float shotTime_;

	// ミサイルタイム
	float missileTime_;

	// パワーアップアイテムの取得数
	unsigned int powerItemCount_;

	// 現在のレベル
	unsigned int nowLevel_;

	// 射撃処理
	ShotFuncPair::const_iterator nowShotItr_;

	// ヒット時の処理のテーブル
	static std::unordered_map<ObjectID, void(PlayerBehavior::*)(Collider&, ObjectManager&)> hitFuncTbl_;

	// 次へレベルアップするまでのパワーアップアイテムの取得数とそのレベルの発射処理の関数をまとめたもの
	static ShotFuncPair shotFuncs_;

};

