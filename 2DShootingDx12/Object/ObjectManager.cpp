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
#include "../Component/ObjectBehavior/StageBehavior.h"
#include "../Component/Collider/CircleCollider.h"
#include "../Object/ObjectFactory/BulletFactory.h"
#include "../Object/ObjectFactory/EffectFactory.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager(std::shared_ptr<InputSystem>& input, Dx12Wrapper& dx12)
{
	// テクスチャデータロード
	textureData_ = std::make_shared<TextureData>(dx12);
	textureData_->Load(L"Resource/image/texture.tdat");

	// アニメーションデータロード
	animData_ = std::make_shared<AnimationData>();
	animData_->Load("Resource/animation/anim.adat");

	// 弾の生成クラス作成
	auto bulletFactory = std::make_shared<BulletFactory>();

	auto effectFactory = std::make_shared<EffectFactory>(animData_);

	// プレイヤー作成
	auto& p = objList_.emplace_front(std::make_unique<Object>());
	p->AddComponent(std::make_unique<PlayerBehavior>(input, bulletFactory));
	p->AddComponent(std::make_unique<Animator>(animData_));
	p->GetCcomponent<Animator>(ComponentID::Animator).lock()->SetState("Non");
	p->AddComponent(std::make_shared<AnimationRender>());
	p->GetCcomponent< AnimationRender>(ComponentID::Render).lock()->SetImgKey("ship");
	p->AddComponent(std::make_shared<CircleCollider>());
	p->GetCcomponent<CircleCollider>(ComponentID::Collider).lock()->SetRadius(10.0f);
	p->SetID(ObjectID::Player);
	p->Begin();

	
	// ステージ作成
	auto& stage = objList_.emplace_front(std::make_unique<Object>());
	stage->AddComponent(std::make_unique<StageBehavior>(animData_, bulletFactory, effectFactory));
	stage->Begin();

	// テクスチャを描画するクラスを作成
	texSheetRender_ = std::make_unique< TextureSheetRender>("texture.png", dx12, textureData_, 256);
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Update(void)
{
	// オブジェクト全部更新
	for (auto& obj : objList_)
	{
		obj->Update(*this);
	}

	// 当たり判定
	if (objList_.size() > 0)
	{
		auto start = objList_.begin();
		auto end = --objList_.end();
		for (auto b = start; b != end; ++b)
		{
			if (!(*b)->HaveComponent(ComponentID::Collider) && !(*b)->IsActive())
			{
				continue;
			}

			for (auto s = ++start; s != objList_.end(); ++s)
			{
				if (!(*s)->HaveComponent(ComponentID::Collider) && !(*s)->IsActive())
				{
					continue;
				}
				auto colA = (*b)->GetCcomponent<Collider>(ComponentID::Collider);
				auto colB = (*s)->GetCcomponent<Collider>(ComponentID::Collider);
				if (!colA.expired() && !colB.expired())
				{
					colA.lock()->Check(*colB.lock(), *this);
				}
			}
		}
	}


	// 非アクティブのオブジェクトの削除
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


const std::pair<ObjectManager::ObjectList::const_iterator, bool> ObjectManager::FindObject(ObjectID id)
{
	auto itr = std::find_if(objList_.begin(), objList_.end(), [id](auto& obj) { return obj->GetID() == id; });
	auto ret = itr != objList_.end();
	return { itr,ret };
}

