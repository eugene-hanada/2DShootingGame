#include "EnemyFactory.h"
#include "../../Component/ObjectBehavior/EnemyMoveToPos.h"
#include "../../Component/Render/AnimationRender.h"
#include "../../Component/Collider/CircleCollider.h"
#include "../../Component/Animator/Animator.h"
#include "../../Object/Object.h"
#include "../../Object/ObjectManager.h"
#include "../ObjectFactory/PowerUpItemFactory.h"

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
	}
	for (int i = 0; i < maxEnemy; i++)
	{
		renderList_.emplace_front(std::make_shared<AnimationRender>());
		colliderList_.emplace_front(std::make_shared<CircleCollider>());
		animatorList_.emplace_front(std::make_shared<Animator>(animData));
		objPool_.emplace_front(std::make_unique<Object>());
	}
}

void EnemyFactory::CreateMoveToPosEnemy(ObjectManager& objManager, const Math::Vector2& start, const Math::Vector2& end)
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
	behavior->SetShotSpeed(5.0f);
	behavior->SetBulletSpeed(180.0f);
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

void EnemyFactory::DestoryMoveToPosEnemy(std::unique_ptr<Object>&& obj)
{
	renderList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Render)));
	animatorList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Animator)));
	moveToPosBehaviorList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Behavior)));
	colliderList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Collider)));
	objPool_.emplace_front(std::move(obj));
}
