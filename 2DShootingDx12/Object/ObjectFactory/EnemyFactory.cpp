#include "EnemyFactory.h"
#include "../../Component/ObjectBehavior/EnemyMoveToPos.h"
#include "../../Component/Render/AnimationRender.h"
#include "../../Component/Collider/CircleCollider.h"
#include "../../Component/Animator/Animator.h"
#include "../../Object/Object.h"
#include "../../Object/ObjectManager.h"
#include "../ObjectFactory/PowerUpItemFactory.h"
#include "../../Component/ObjectBehavior/EnemyMove.h"

constexpr int maxEnemy{ 50 };
constexpr int maxMoveToPosEnemy{ 10 };

constexpr float typeMRedius{ 15.0f };

EnemyFactory::EnemyFactory(std::shared_ptr<AnimationData>& animData, std::shared_ptr<BulletFactory>& bulletFactory, std::shared_ptr< EffectFactory>& effectFactory) :
	effectFactory_{effectFactory}
{
	itemfactory_ = std::make_unique<PowerUpItemFactory>();
	for (int i = 0; i < maxMoveToPosEnemy; i++)
	{
		moveToPosBehaviorList_.emplace_front(std::make_shared<EnemyMoveToPos>(*this, bulletFactory, *itemfactory_, *effectFactory_));
		moveBehaviorList_.emplace_front(std::make_shared<EnemyMove>(*this, bulletFactory, *itemfactory_, *effectFactory_));
	}
	for (int i = 0; i < maxEnemy; i++)
	{
		renderList_.emplace_front(std::make_shared<AnimationRender>());
		colliderList_.emplace_front(std::make_shared<CircleCollider>());
		animatorList_.emplace_front(std::make_shared<Animator>(animData));
		objPool_.emplace_front(std::make_unique<Object>());
	}
}

void EnemyFactory::CreateMoveToPosEnemyS(ObjectManager& objManager, const Math::Vector2& start, const Math::Vector2& end, const ShotType type, float shotSpeed )
{
	if (moveToPosBehaviorList_.empty())
	{
		return;
	}

	auto obj = std::move(objPool_.front());
	objPool_.pop_front();

	// アニメーション描画用クラスを追加
	auto render = std::static_pointer_cast<AnimationRender>(std::move(renderList_.front()));
	renderList_.pop_front();
	render->SetImgKey("enemys");
	obj->AddComponent(std::move(render));

	// アニメーション制御用クラスを追加
	auto anim = std::static_pointer_cast<Animator>(std::move(animatorList_.front()));
	animatorList_.pop_front();
	obj->AddComponent(std::move(anim));
	obj->GetCcomponent<Animator>(ComponentID::Animator).lock()->SetState("Non");
	
	// ビヘイビアクラスを追加
	auto behavior = std::static_pointer_cast<EnemyMoveToPos>(std::move(moveToPosBehaviorList_.front()));
	moveToPosBehaviorList_.pop_front();
	behavior->SetDestination(end);
	behavior->SetHp(6);
	behavior->SetShotSpeed(shotSpeed);
	behavior->SetBulletSpeed(180.0f);
	behavior->SetMoveSpeed(120.0f);
	behavior->SetShotFunc(type);
	obj->AddComponent(std::move(behavior));

	// 当たり判定用クラス
	auto col = std::static_pointer_cast<CircleCollider>(std::move(colliderList_.front()));
	colliderList_.pop_front();
	col->SetRadius(typeMRedius);
	obj->AddComponent(std::move(col));

	obj->SetID(ObjectID::Enemy);
	obj->SetPos(start);
	objManager.AddObject(std::move(obj));

}

void EnemyFactory::CreateMoveToPosEnemyM(ObjectManager& objManager, const Math::Vector2& start, const Math::Vector2& end, const ShotType type, float shotSpeed)
{
	if (moveToPosBehaviorList_.empty())
	{
		return;
	}

	auto obj = std::move(objPool_.front());
	objPool_.pop_front();

	// アニメーション描画用クラスを追加
	auto render = std::static_pointer_cast<AnimationRender>(std::move(renderList_.front()));
	renderList_.pop_front();
	render->SetImgKey("enemym");
	obj->AddComponent(std::move(render));

	// アニメーション制御用クラスを追加
	auto anim = std::static_pointer_cast<Animator>(std::move(animatorList_.front()));
	animatorList_.pop_front();
	obj->AddComponent(std::move(anim));
	obj->GetCcomponent<Animator>(ComponentID::Animator).lock()->SetState("Non");

	// ビヘイビアクラスを追加
	auto behavior = std::static_pointer_cast<EnemyMoveToPos>(std::move(moveToPosBehaviorList_.front()));
	moveToPosBehaviorList_.pop_front();
	behavior->SetDestination(end);
	behavior->SetHp(12);
	behavior->SetShotSpeed(shotSpeed);
	behavior->SetBulletSpeed(200.0f);
	behavior->SetMoveSpeed(100.0f);
	behavior->SetShotFunc(type);
	obj->AddComponent(std::move(behavior));

	// 当たり判定用クラス
	auto col = std::static_pointer_cast<CircleCollider>(std::move(colliderList_.front()));
	colliderList_.pop_front();
	col->SetRadius(typeMRedius);
	obj->AddComponent(std::move(col));

	obj->SetID(ObjectID::Enemy);
	obj->SetPos(start);
	objManager.AddObject(std::move(obj));
}

void EnemyFactory::CreateMoveEnemyS(ObjectManager& objManager, const Math::Vector2& pos, const Math::Vector2& moveDir, const ShotType type, float shotSpeed)
{
	if (moveBehaviorList_.empty())
	{
		return;
	}
	auto obj = std::move(objPool_.front());
	objPool_.pop_front();

	// アニメーション描画用クラスを追加
	auto render = std::static_pointer_cast<AnimationRender>(std::move(renderList_.front()));
	renderList_.pop_front();
	render->SetImgKey("enemys");
	obj->AddComponent(std::move(render));

	// アニメーション制御用クラスを追加
	auto anim = std::static_pointer_cast<Animator>(std::move(animatorList_.front()));
	animatorList_.pop_front();
	obj->AddComponent(std::move(anim));
	obj->GetCcomponent<Animator>(ComponentID::Animator).lock()->SetState("Non");

	// ビヘイビアクラスを追加
	auto behavior = std::static_pointer_cast<EnemyMove>(std::move(moveBehaviorList_.front()));
	moveBehaviorList_.pop_front();
	behavior->SetMoveDir(moveDir);
	behavior->SetHp(6);
	behavior->SetShotSpeed(shotSpeed);
	behavior->SetBulletSpeed(180.0f);
	behavior->SetShotFunc(type);
	behavior->SetMoveSpeed(120.0f);
	obj->AddComponent(std::move(behavior));

	// 当たり判定用クラス
	auto col = std::static_pointer_cast<CircleCollider>(std::move(colliderList_.front()));
	colliderList_.pop_front();
	col->SetRadius(typeMRedius);
	obj->AddComponent(std::move(col));

	obj->SetID(ObjectID::Enemy);
	obj->SetPos(pos);
	objManager.AddObject(std::move(obj));
}

void EnemyFactory::CreateMoveEnemyM(ObjectManager& objManager, const Math::Vector2& pos, const Math::Vector2& moveDir, const ShotType type, float shotSpeed)
{
	if (moveBehaviorList_.empty())
	{
		return;
	}
	auto obj = std::move(objPool_.front());
	objPool_.pop_front();

	// アニメーション描画用クラスを追加
	auto render = std::static_pointer_cast<AnimationRender>(std::move(renderList_.front()));
	renderList_.pop_front();
	render->SetImgKey("enemym");
	obj->AddComponent(std::move(render));

	// アニメーション制御用クラスを追加
	auto anim = std::static_pointer_cast<Animator>(std::move(animatorList_.front()));
	animatorList_.pop_front();
	obj->AddComponent(std::move(anim));
	obj->GetCcomponent<Animator>(ComponentID::Animator).lock()->SetState("Non");

	// ビヘイビアクラスを追加
	auto behavior = std::static_pointer_cast<EnemyMove>(std::move(moveBehaviorList_.front()));
	moveBehaviorList_.pop_front();
	behavior->SetMoveDir(moveDir);
	behavior->SetHp(12);
	behavior->SetShotSpeed(shotSpeed);
	behavior->SetBulletSpeed(200.0f);
	behavior->SetShotFunc(type);
	behavior->SetMoveSpeed(100.0f);
	obj->AddComponent(std::move(behavior));

	// 当たり判定用クラス
	auto col = std::static_pointer_cast<CircleCollider>(std::move(colliderList_.front()));
	colliderList_.pop_front();
	col->SetRadius(typeMRedius);
	obj->AddComponent(std::move(col));

	obj->SetID(ObjectID::Enemy);
	obj->SetPos(pos);
	objManager.AddObject(std::move(obj));
}

void EnemyFactory::DeleteMoveToPosEnemy(std::unique_ptr<Object>&& obj)
{
	renderList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Render)));
	animatorList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Animator)));
	moveToPosBehaviorList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Behavior)));
	colliderList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Collider)));
	objPool_.emplace_front(std::move(obj));
}

void EnemyFactory::DeleteMoveEnemy(std::unique_ptr<Object>&& obj)
{
	renderList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Render)));
	animatorList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Animator)));
	moveBehaviorList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Behavior)));
	colliderList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Collider)));
	objPool_.emplace_front(std::move(obj));
}
