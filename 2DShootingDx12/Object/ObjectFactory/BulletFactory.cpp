#include "../Object.h"
#include "../../Component/ObjectBehavior/NormalBullet.h"
#include "../ObjectManager.h"
#include "../../Component/Render/DefaultRender.h"
#include "../../Component/Collider/CircleCollider.h"
#include "BulletFactory.h"
#include "../../Component/ObjectBehavior/MissileBehavior.h"
#include "../../Component/Sound/Sound.h"
#include "../../GameSystem/Xaudio2/Wave.h"

constexpr int normalBulletMax{ 200 };
constexpr int missileMax{ 100 };
constexpr int maxBullet{ missileMax + normalBulletMax };

constexpr float bulletRadius{ 5.0f };

BulletFactory::BulletFactory(Xaudio2& xaudio2, std::shared_ptr<EffectFactory>& effectFactory) :
	effect_{ effectFactory }
{
	for (int i = 0; i < normalBulletMax; i++)
	{
		normalShotBehaviorList_.emplace_front(std::make_shared<NormalBullet>(*this));
	}
	auto wave = std::make_shared<Wave>();
	wave->Load("Resource/Sound/missile.wav");
	for (int i = 0; i < missileMax; i++)
	{
		missileList_.emplace_front(std::make_shared<MissileBehavior>(*this, *effect_));
		missileSoundList_.emplace_front(std::make_shared<Sound>(xaudio2,wave));
	}
	for (int i = 0; i < maxBullet; i++)
	{
		objPool_.emplace_front(std::make_unique<Object>());
		renderList_.emplace_front(std::make_shared<DefaultRender>());
		colliderList_.emplace_front(std::make_shared<CircleCollider>());
	}
}

void BulletFactory::CreateNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec, float speed)
{
	// オブジェクトクラスを取得
	CheckObjPool();
	auto obj = std::move(objPool_.front());
	objPool_.pop_front();

	// ビヘイビアクラスを取る
	CheckShotBehaviorPool();
	auto behavior = std::static_pointer_cast<NormalBullet>(std::move(normalShotBehaviorList_.front()));
	normalShotBehaviorList_.pop_front();
	behavior->SetMoveVec(moveVec);
	behavior->SetSpeed(speed);
	behavior->SetShooterID(ObjectID::Player);
	obj->AddComponent(std::move(behavior));

	// レンダークラスをセット
	CheckRenderPool();
	auto render = std::static_pointer_cast<DefaultRender>(std::move(renderList_.front()));
	renderList_.pop_front();
	render->SetImgKey("bulletC");
	render->SetRotation(moveVec.GetAngle());
	obj->AddComponent(std::move(render));
	obj->pos_ = pos;

	// 当たり判定クラスを追加する
	CheckColliderPool();
	auto col = std::static_pointer_cast<CircleCollider>(std::move(colliderList_.front()));
	colliderList_.pop_front();
	col->SetRadius(bulletRadius);
	obj->AddComponent(std::move(col));

	obj->SetID(ObjectID::PlayerBullet);
	objectManager.AddObject(std::move(obj));
}

void BulletFactory::DeleteNormalBullet(std::unique_ptr<Object>&& obj)
{
	normalShotBehaviorList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Behavior)));
	renderList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Render)));
	colliderList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Collider)));
	objPool_.emplace_front(std::move(obj));
}

void BulletFactory::CreateEnemyNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec, float speed)
{
	// オブジェクトクラスを取得
	CheckObjPool();
	auto obj = std::move(objPool_.front());
	objPool_.pop_front();

	// ビヘイビアクラスを取る
	CheckShotBehaviorPool();
	auto behavior = std::static_pointer_cast<NormalBullet>(std::move(normalShotBehaviorList_.front()));
	normalShotBehaviorList_.pop_front();
	behavior->SetSpeed(speed);
	behavior->SetMoveVec(moveVec);
	behavior->SetShooterID(ObjectID::Enemy);
	obj->AddComponent(std::move(behavior));

	// レンダークラスをセット
	CheckRenderPool();
	auto render = std::static_pointer_cast<DefaultRender>(std::move(renderList_.front()));
	renderList_.pop_front();
	render->SetImgKey("bulletA");
	render->SetRotation(moveVec.GetAngle());
	obj->AddComponent(std::move(render));
	obj->pos_ = pos;

	// 当たり判定クラスを追加する
	CheckColliderPool();
	auto col = std::static_pointer_cast<CircleCollider>(std::move(colliderList_.front()));
	colliderList_.pop_front();
	col->SetRadius(bulletRadius);
	obj->AddComponent(std::move(col));

	obj->SetID(ObjectID::EnemyBullet);
	objectManager.AddObject(std::move(obj));

}

void BulletFactory::CreateApBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec, float speed)
{
	// オブジェクトクラスを取得
	CheckObjPool();
	auto obj = std::move(objPool_.front());
	objPool_.pop_front();

	// ビヘイビアクラスを取る
	CheckShotBehaviorPool();
	auto behavior = std::static_pointer_cast<NormalBullet>(std::move(normalShotBehaviorList_.front()));
	normalShotBehaviorList_.pop_front();
	behavior->SetMoveVec(Math::upVector2<float>);
	behavior->SetSpeed(speed);
	behavior->SetShooterID(ObjectID::Player);
	behavior->ArmorPiercing();
	obj->AddComponent(std::move(behavior));

	// レンダークラスをセット
	CheckRenderPool();
	auto render = std::static_pointer_cast<DefaultRender>(std::move(renderList_.front()));
	renderList_.pop_front();
	render->SetImgKey("bulletD");
	render->SetRotation(moveVec.GetAngle());
	obj->AddComponent(std::move(render));
	obj->pos_ = pos;

	// 当たり判定クラスを追加する
	CheckColliderPool();
	auto col = std::static_pointer_cast<CircleCollider>(std::move(colliderList_.front()));
	colliderList_.pop_front();
	col->SetRadius(bulletRadius);
	obj->AddComponent(std::move(col));

	obj->SetID(ObjectID::PlayerBullet);
	objectManager.AddObject(std::move(obj));
}

void BulletFactory::CreateMissile(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec)
{
	if (missileSoundList_.empty())
	{
		return;
	}

	// オブジェクトクラスを取得
	CheckObjPool();
	auto obj = std::move(objPool_.front());
	objPool_.pop_front();

	// ビヘイビアクラスを取る
	CheckMissileBehaviorPool();
	auto behavior = std::static_pointer_cast<MissileBehavior>(std::move(missileList_.front()));
	missileList_.pop_front();
	behavior->SetMoveVec(moveVec);
	obj->AddComponent(std::move(behavior));

	// レンダークラスをセット
	CheckRenderPool();
	auto render = std::static_pointer_cast<DefaultRender>(std::move(renderList_.front()));
	renderList_.pop_front();
	render->SetImgKey("missileB");
	render->SetRotation(moveVec.GetAngle());
	obj->AddComponent(std::move(render));
	obj->pos_ = pos;

	// 当たり判定クラスを追加する
	CheckColliderPool();
	auto col = std::static_pointer_cast<CircleCollider>(std::move(colliderList_.front()));
	colliderList_.pop_front();
	col->SetRadius(bulletRadius);
	obj->AddComponent(std::move(col));

	// サウンドを追加
	auto sound = std::static_pointer_cast<Sound>(std::move(missileSoundList_.front()));
	missileSoundList_.pop_front();
	obj->AddComponent(std::move(sound));
	obj->SetID(ObjectID::Missile);
	objectManager.AddObject(std::move(obj));
}

void BulletFactory::DeleteMissile(std::unique_ptr<Object>&& obj)
{
	missileSoundList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Sound)));
	colliderList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Collider)));
	renderList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Render)));
	missileList_.emplace_front(std::move(obj->RemoveComponent(ComponentID::Behavior)));
	objPool_.emplace_front(std::move(obj));
}

void BulletFactory::CheckShotBehaviorPool(void)
{
	if (normalShotBehaviorList_.empty())
	{
		normalShotBehaviorList_.emplace_front(std::make_shared<NormalBullet>(*this));
	}
}

void BulletFactory::CheckRenderPool(void)
{
	if (renderList_.empty())
	{
		renderList_.emplace_front(std::make_shared<DefaultRender>());
	}
}

void BulletFactory::CheckColliderPool(void)
{
	if (colliderList_.empty())
	{
		colliderList_.emplace_front(std::make_shared<CircleCollider>());
	}
}

void BulletFactory::CheckMissileBehaviorPool(void)
{
	if (missileList_.empty())
	{
		missileList_.emplace_front(std::make_shared<MissileBehavior>(*this, *effect_));
	}
}


void BulletFactory::CheckObjPool(void)
{
	if (objPool_.empty())
	{
		objPool_.emplace_front(std::make_unique<Object>());
	}
}

