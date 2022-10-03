#include "Object.h"
#include "../Component/ObjectBehavior/PlayerBehavior.h"
#include "../Component/Material.h"
#include "../GameSystem/Dx12/Resource/Texture.h"
#include "../Component/Render/ObjRender.h"
#include "../GameSystem/Dx12/Render/TextureSheetRender.h"
#include "../common/TextureData.h"
#include "../Component/Render/DefaultRender.h"
#include "../Component/Render/AnimationRender.h"
#include "../Component/Animator/Animator.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager(std::shared_ptr<TextureData>& textureData, std::shared_ptr< AnimationData>& animData, std::shared_ptr<InputSystem>& input, Dx12Wrapper& dx12)
{
	auto& p = objList_.emplace_front(std::make_unique<Object>());
	p->AddComponent(std::make_unique<PlayerBehavior>(input));
	p->AddComponent(std::make_unique<Animator>(animData));
	p->GetCcomponent<Animator>(ComponentID::Animator).lock()->SetState("Non");
	p->AddComponent(std::make_shared<AnimationRender>());
	p->GetCcomponent< AnimationRender>(ComponentID::Render).lock()->SetImgKey("ship");
	p->Begin();

	
	texSheetRender_ = std::make_unique< TextureSheetRender>("texture.png", dx12, textureData, 256);
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Update(void)
{
	for (auto& obj : objList_)
	{
		obj->Update(*this);
	}

	auto itr = std::find_if(objList_.begin(), objList_.end(), [](auto& obj) {
		return !obj->IsActive();
		});
	if (itr != objList_.end())
	{
		(*itr)->End(std::move(*itr));
		objList_.erase(itr);
	}
}

void ObjectManager::Draw(RenderManager& renderMng, CbMatrix& cbMat)
{
	for (auto& obj : objList_)
	{
		auto com = obj->GetCcomponent<ObjRender>(ComponentID::Render);
		if (!com.expired())
		{
			com.lock()->Draw(*texSheetRender_);
		}
	}
	texSheetRender_->Update();
	texSheetRender_->Draw(cbMat);
}

void ObjectManager::AddObject(std::unique_ptr<Object>&& object)
{
	objList_.emplace_front(std::move(object));
	auto itr = objList_.begin();
	(*itr)->Begin();
}

std::unique_ptr<Object> ObjectManager::RemovObjecte(std::list<std::unique_ptr<Object>>::iterator itr)
{
	auto obj = std::move(*itr);
	objList_.erase(itr);
	return std::move(obj);
}


