#include "../Object.h"
#include "../../Component/ObjectBehavior/NormalBullet.h"
#include "../ObjectManager.h"
#include "../../Component/Render/DefaultRender.h"
#include "BulletFactory.h"

constexpr int maxBullet{ 300 };

BulletFactory::BulletFactory()
{
	for (int i = 0; i < 100; i++)
	{
		normalShotBehaviorList_.emplace_back(std::make_shared<NormalBullet>(*this));
	}
	for (int i = 0; i < maxBullet; i++)
	{
		objPool_.emplace_back(std::make_unique<Object>());
	}
	for (int i = 0; i < maxBullet; i++)
	{
		renderList_.emplace_back(std::make_shared<DefaultRender>());
	}
}

void BulletFactory::CreateNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec)
{
	if (normalShotBehaviorList_.size() <= 0)

	{
		return;
	}
	// オブジェクトクラスを取得
	auto obj = std::move(objPool_.front());
	objPool_.pop_front();
	
	// ビヘイビアクラスを取る
	auto behavior = std::static_pointer_cast<NormalBullet>(std::move(normalShotBehaviorList_.front()));
	normalShotBehaviorList_.pop_front();
	behavior->SetMoveVec(Math::upVector2<float>);
	behavior->SetSpeed(120.0f);
	obj->AddComponent(std::move(behavior));

	// レンダークラスをセット
	auto render = std::static_pointer_cast<DefaultRender>(std::move(renderList_.front()));
	renderList_.pop_front();
	render->SetImgKey("bulletA");

	obj->AddComponent(std::move(render));
	obj->pos_ = pos;
	objectManager.AddObject(std::move(obj));
}

void BulletFactory::DeleteNormalBullet(Object& obj, ObjectManager& objectManager)
{
	/*normalShotBehaviorList_.emplace_back(std::move((*itr)->RemoveComponent(ComponentID::Behavior)));
	renderList_.emplace_back(std::move((*itr)->RemoveComponent(ComponentID::Render)));
	std::unique_ptr<Object> obj;
	obj.swap(*itr);*/

	//objPool_.emplace_back(std::move(obj));
}
