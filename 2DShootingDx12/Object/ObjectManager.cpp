#include "Object.h"
#include "../Component/ObjectBehavior/PlayerBehavior.h"
#include "../Component/Material.h"
#include "../GameSystem/Dx12/Resource/Texture.h"
#include "../Component/Render/ObjRender.h"
#include "../GameSystem/Dx12/Render/TextureSheetRender.h"
#include "../common/TextureData.h"
#include "../Component/Render/DefaultRender.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager(std::shared_ptr<TextureData>& textureData, std::shared_ptr<InputSystem>& input, Dx12Wrapper& dx12)
{
	auto& p = objList_.emplace_back(std::make_unique<Object>(dx12));
	p->AddComponent(std::make_unique<PlayerBehavior>(input));
	
	p->AddComponent(std::make_shared<DefaultRender>());
	p->GetCcomponent<ObjRender>(ComponentID::Render).lock()->SetImgKey("ship");
	p->Begin();

	
	texSheetRender_ = std::make_unique< TextureSheetRender>("texture.png", dx12, textureData, 256);
}

ObjectManager::~ObjectManager()
{
	for (auto& obj : objList_)
	{
		obj->End();
	}
}

void ObjectManager::Update(void)
{
	for (auto& obj : objList_)
	{
		obj->Update();
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

void ObjectManager::AddAnimationRender(Object& obj)
{
	
	obj.AddComponent(std::move(animeRenderPool_.back()));
	animeRenderPool_.pop_back();
}

void ObjectManager::RemoveAnimationRender(Object& obj)
{
	animeRenderPool_.emplace_back(obj.RemoveComponent(ComponentID::Render));
}
