#pragma once
#include <string>
#include "../Component.h"
#include "../../common/AnimationData.h"

// アニメーションを制御するクラス
class Animator :
	public Component
{
public:
	Animator(std::shared_ptr<AnimationData>& animData);
	~Animator();

	/// <summary>
	/// 現在のアニメーションのindexを取得する
	/// </summary>
	/// <param name=""></param>
	/// <returns> 現在のindex </returns>
	const int GetIdx(void) const noexcept;

	/// <summary>
	/// 現在のアニメーションステートを取得する
	/// </summary>
	/// <param name=""></param>
	/// <returns> 現在のステート </returns>
	const std::string& GetState(void) const;

	/// <summary>
	/// アニメーションステートをセットする
	/// </summary>
	/// <param name="state"> セットするステート </param>
	void SetState(const std::string& state);

	/// <summary>
	/// アニメーションが終了しているか？
	/// </summary>
	/// <param name=""></param>
	/// <returns> 終了時true、アニメーション中false </returns>
	const bool IsEnd(void) const;
private:
	void Begin(void) final;
	void Update(ObjectManager& objectManager) final;
	const ComponentID GetID(void) const noexcept final { return ComponentID::Animator; }
	
	// ステート
	std::string state_;

	// アニメーションデータ
	AnimationData::Data* data_;

	// ループ数
	int loopCount_;

	// 再生時間
	float playTime_;

	// 再生位置のイテレーター
	std::vector<std::pair<int, float>>::const_iterator nowItr_;

	// アニメーションデータ
	std::shared_ptr<AnimationData> animData_;
};

