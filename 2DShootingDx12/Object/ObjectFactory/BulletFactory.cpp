#include "../Object.h"
#include "../../Component/ObjectBehavior/NormalBullet.h"
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
		//objPool_.emplace_back(std::make_unique<Object>());
	}
	for (int i = 0; i < maxBullet; i++)
	{
		renderList_.emplace_back(std::make_shared<DefaultRender>());
	}
}

void BulletFactory::CreateNormalBullet(ObjectManager& objectManager, const Math::Vector2& pos, const Math::Vector2& moveVec)
{
	auto obj = std::move(objPool_.front());
	objPool_.pop_front();
	
	auto behavior = std::static_pointer_cast<NormalBullet>(std::move(normalShotBehaviorList_.front()));
	normalShotBehaviorList_.pop_front();
	behavior->SetMoveVec(moveVec);
	behavior->SetSpeed(120.0f);

	auto render = std::static_pointer_cast<DefaultRender>(std::move(renderList_.front()));
	renderList_.pop_front();
	render->SetImgKey("BulletA");

	obj->pos_ = pos;
	obj->AddComponent(std::move(behavior));

}

void BulletFactory::DeleteNormalBullet(Object& object, ObjectManager& objectManager)
{
}
