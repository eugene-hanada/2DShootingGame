#include "Object.h"
#include "../Component/ObjectBehavior/PlayerBehavior.h"
#include "../Component/Material.h"
#include "../GameSystem/Dx12/Resource/Texture.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager(std::shared_ptr<InputSystem>& input, Dx12Wrapper& dx12)
{
	auto& p = objList_.emplace_back(std::make_unique<Object>(dx12));
	p->AddComponent(std::make_unique<PlayerBehavior>(input));
	tex_ = std::make_shared<Texture>(dx12, TEXT("Resource/image/Logo.png"));
	p->AddComponent(std::make_shared<Material>(tex_, dx12));
	p->Begin();
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
		auto com = obj->GetCcomponent<Material>(ComponentID::Material);
		if (!com.expired())
		{
			com.lock()->Draw(renderMng, cbMat);
		}
	}
}
