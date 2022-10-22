#include "../Object.h"
#include "../../Component/ObjectBehavior/NormalBullet.h"
#include "../ObjectManager.h"
#include "../../Component/Render/DefaultRender.h"
#include "../../Component/Collider/CircleCollider.h"
#include "BulletFactory.h"

constexpr int maxBullet{ 300 };
constexpr int normalBulletMax{ 200 };

BulletFactory::BulletFactory()
{
	for (int i = 0; i < normalBulletMax; i++)
	{
		normalShotBehaviorList_.emplace_back(std::make_shared<NormalBullet>(*this));
	}
	for (int i = 0; i < maxBullet; i++)
	{
		objPool_.emplace_back(std::make_unique<Object>());
		renderList_.emplace_back(std::make_shared<DefaultRender>());
		colliderList_.emplace_back(std::make_shared<CircleCollider>());
	}
}

void BulletFactory::CreateNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec)
{
	if (normalShotBehaviorList_.size() <= 0)

	{
		return;
	}
	CreateNormalBullet(objectManager, pos + (Math::rightVector2<float> * 5.0f));
	CreateNormalBullet(objectManager, pos + (Math::leftVector2<float> *5.0f));
}

void BulletFactory::DeleteNormalBullet(std::unique_ptr<Object>&& obj)
{
	normalShotBehaviorList_.emplace_back(std::move(obj->RemoveComponent(ComponentID::Behavior)));
	renderList_.emplace_back(std::move(obj->RemoveComponent(ComponentID::Render)));
	objPool_.emplace_back(std::move(obj));
}

void BulletFactory::CreateEnemyNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec)
{

}

void BulletFactory::DeleteEnemyNormalBullet(std::unique_ptr<Object>&& obj)
{
}

void BulletFactory::CreateNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos)
{
	// オブジェクトクラスを取得
	auto obj = std::move(objPool_.front());
	objPool_.pop_front();

	// ビヘイビアクラスを取る
	auto behavior = std::static_pointer_cast<NormalBullet>(std::move(normalShotBehaviorList_.front()));
	normalShotBehaviorList_.pop_front();
	behavior->SetMoveVec(Math::upVector2<float>);
	behavior->SetSpeed(180.0f);
	obj->AddComponent(std::move(behavior));

	// レンダークラスをセット
	auto render = std::static_pointer_cast<DefaultRender>(std::move(renderList_.front()));
	renderList_.pop_front();
	render->SetImgKey("bulletA");
	obj->AddComponent(std::move(render));
	obj->pos_ = pos;

	// 当たり判定クラスを追加する
	auto col = std::static_pointer_cast<CircleCollider>(std::move(colliderList_.front()));
	colliderList_.pop_front();
	col->SetRadius(5.0f);
	obj->AddComponent(std::move(col));

	obj->SetID(ObjectID::PlayerBullet);
	objectManager.AddObject(std::move(obj));
}
