#pragma once
#include <list>
#include <memory>
#include "ComponentID.h"

class Object;
class ObjectManager;

// オブジェクトにくっつける機能の基底クラス
class Component
{
public:
	Component() noexcept;
	virtual ~Component();

	/// <summary>
	/// 持ち主のオブジェクトクラスをセットする
	/// </summary>
	/// <param name="owner"> 持ち主のオブジェクトクラスのポインタ </param>
	/// <returns> 成功時true失敗時false </returns>
	bool SetOwner(Object* owner);

	/// <summary>
	/// 持ち主のオブジェクトのポインタを取得する
	/// </summary>
	/// <param name=""></param>
	/// <returns> 持ち主のオブジェクトのポインタ </returns>
	Object* GetOnwer(void);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="objectManager"> オブジェクトマネージャー </param>
	virtual void Update(ObjectManager& objectManager){}

	/// <summary>
	/// オブジェクトが有効になった時の処理
	/// </summary>
	/// <param name=""></param>
	virtual void Begin(ObjectManager& objectManager){}

	/// <summary>
	/// オブジェクトが無効になった時の処理
	/// </summary>
	/// <param name=""></param>
	virtual void End(void) { }

	/// <summary>
	/// IDの取得
	/// </summary>
	/// <param name=""></param>
	/// <returns> ID </returns>
	virtual  const ComponentID GetID(void) const noexcept = 0;

	/// <summary>
	/// オブジェクトがアクティブか？
	/// </summary>
	/// <param name=""></param>
	/// <returns> アクティブの時true、そうでないときfalse </returns>
	const bool IsActive(void)const { return owner_ != nullptr; }
protected:

	// 持ち主
	Object* owner_{ nullptr };
};

