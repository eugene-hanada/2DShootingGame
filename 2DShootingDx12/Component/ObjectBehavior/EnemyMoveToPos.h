#pragma once
#include "EnemyBehavior.h"

// 指定座標まで移動する敵の動き
class EnemyMoveToPos :
	public EnemyBehavior
{
public:
	EnemyMoveToPos(EnemyFactory& factory, std::shared_ptr<BulletFactory>& bulletFactory, PowerUpItemFactory& itemFactory, EffectFactory& effectFactory);
	
	/// <summary>
	/// 移動目標をセットする
	/// </summary>
	/// <param name="dest"> 移動目標 </param>
	void SetDestination(const Math::Vector2& dest);

private:
	void Update(ObjectManager& objectManager) final;
	void Destory(std::unique_ptr<Object>&& obj) final;

	/// <summary>
	/// 移動時の更新処理
	/// </summary>
	/// <param name="objectManager"></param>
	void UpdateMove(ObjectManager& objectManager);

	/// <summary>
	/// 射撃時の更新処理
	/// </summary>
	/// <param name="objectManager"></param>
	void UpdateShot(ObjectManager& objectManager);

	void Begin(ObjectManager& objectManager) final;

	// 移動目標の座標
	Math::Vector2 dest_;

	// 移動方向
	Math::Vector2 moveVec_;

	// 更新処理
	void (EnemyMoveToPos::* update_)(ObjectManager&);
};

