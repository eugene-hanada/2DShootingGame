#pragma once
#include "ObjectBehavior.h"

class AnimationData;
class EnemyFactory;
class BulletFactory;
class EffectFactory;

class StageBehavior :
	public ObjectBehavior
{
public:
	StageBehavior(std::shared_ptr<AnimationData>& animData, std::shared_ptr<BulletFactory>& bulletFactory, std::shared_ptr< EffectFactory>& effectFactory);
	void Update(ObjectManager& objectManager) final;
	void Begin(ObjectManager& objectManager) final;
	const unsigned int GetScore(void) const
	{
		return score_;
	}

	/// <summary>
	/// スコアの加算する
	/// </summary>
	/// <param name="addValue"> 加算するスコアの値 </param>
	void AddScore(unsigned int addValue);

	/// <summary>
	/// スコアを減算する
	/// </summary>
	/// <param name="subValue"> 減算するスコアの値 </param>
	void SubScore(unsigned int subValue);

private:

	// タイム
	float timer_;

	// 敵の生成クラス
	std::unique_ptr<EnemyFactory> enemyFactory_;

	// スコア
	unsigned int score_;
};

