#pragma once
#include "../Component.h"

class Collider;

// オブジェクトの動きに関するクラス
class ObjectBehavior :
	public Component
{
public:
	ObjectBehavior();
	virtual ~ObjectBehavior();

	/// <summary>
	/// 破棄時の処理
	/// </summary>
	/// <param name="obj"> 破棄するオブジェクト </param>
	virtual void Destory(std::unique_ptr<Object>&& obj){}

	/// <summary>
	/// ヒット時の処理
	/// </summary>
	/// <param name="collider"> 相手コライダー </param>
	/// <param name="objectManager"> オブジェクトマネージャー </param>
	virtual void OnHit(Collider& collider, ObjectManager& objectManager){};
private:
	const ComponentID GetID(void) const noexcept final { return ComponentID::Behavior; }
};

