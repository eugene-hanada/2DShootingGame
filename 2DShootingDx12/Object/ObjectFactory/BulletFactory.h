#pragma once
#include <memory>
#include <forward_list>
#include "../../common/Math.h"

class ObjectManager;
class Object;
class Component;
class Xaudio2;
class EffectFactory;

// 弾の生成クラス
class BulletFactory
{
public:
	using ComponentShPtr = std::shared_ptr<Component>;
	BulletFactory(Xaudio2& xaudio2, std::shared_ptr<EffectFactory>& effectFactory);

	/// <summary>
	/// 通常の弾の生成
	/// </summary>
	/// <param name="objectManager"> オブジェクトマネージャー </param>
	/// <param name="pos"> 座標 </param>
	/// <param name="moveVec"> 移動方向 </param>
	/// <param name="speed"> 移動スピード </param>
	void CreateNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec, float speed);

	/// <summary>
	/// 通常の弾の削除
	/// </summary>
	/// <param name="obj"> オブジェクト </param>
	void DeleteNormalBullet(std::unique_ptr<Object>&& obj);

	/// <summary>
	/// 敵の弾の生成
	/// </summary>
	/// <param name="objectManager"> マネージャー </param>
	/// <param name="pos"> 座標 </param>
	/// <param name="moveVec"> 移動方向 </param>
	/// <param name="speed"> スピード </param>
	void CreateEnemyNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec, float speed);
	
	/// <summary>
	/// 貫通する弾の生成
	/// </summary>
	/// <param name="objectManager"> オブジェクトマネージャー </param>
	/// <param name="pos"> 座標 </param>
	/// <param name="moveVec"> 移動方向 </param>
	/// <param name="speed"> スピード </param>
	void CreateApBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec, float speed);

	void CreateMissile(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec);

	void DeleteMissile(std::unique_ptr<Object>&& obj);
private:
	void CheckShotBehaviorPool(void);
	void CheckRenderPool(void);
	void CheckColliderPool(void);
	void CheckMissileBehaviorPool(void);
	void CheckObjPool(void);

	std::forward_list<ComponentShPtr> normalShotBehaviorList_;
	std::forward_list<ComponentShPtr> renderList_;
	std::forward_list<ComponentShPtr> colliderList_;
	std::forward_list<ComponentShPtr> missileList_;
	std::forward_list<ComponentShPtr> missileSoundList_;
	std::forward_list<std::unique_ptr<Object>> objPool_;
	std::shared_ptr< EffectFactory> effect_;
};

