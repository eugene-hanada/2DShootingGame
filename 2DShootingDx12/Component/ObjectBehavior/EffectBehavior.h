#pragma once
#include "ObjectBehavior.h"
#include <unordered_map>

class Animator;
class EffectFactory;

// エフェクトの種類
enum class EffectType
{
	ExpM,			// 爆発
	ExpS,			// 爆発小
	Score			// スコア
};

// エフェクト制御ようクラス
class EffectBehavior :
	public ObjectBehavior
{
public:

	EffectBehavior(EffectFactory& factory);
	void SetType(const EffectType type)
	{
		type_ = type;
	}

private:
	void Update(ObjectManager& objectManager) final;
	void Begin(ObjectManager& objectManager) final;
	void Destory(std::unique_ptr<Object>&& obj) final;

	/// <summary>
	/// 爆発Mの破棄用
	/// </summary>
	/// <param name="obj"></param>
	void DestoryExpM(std::unique_ptr<Object>&& obj);

	/// <summary>
	/// 爆発sの破棄用
	/// </summary>
	/// <param name="obj"></param>
	void DestoryExpS(std::unique_ptr<Object>&& obj);

	/// <summary>
	/// スコア用
	/// </summary>
	/// <param name="obj"></param>
	void DestoryScore(std::unique_ptr<Object>&& obj);

	// アニメーション制御クラス
	std::weak_ptr<Animator> animator_;

	// エフェクト生成クラス
	EffectFactory& factory_;

	// 敵のタイプ
	EffectType type_;

	// 破棄用の関数
	static std::unordered_map<EffectType, void(EffectBehavior::*)(std::unique_ptr<Object>&&)> destoryFunc_;
};

