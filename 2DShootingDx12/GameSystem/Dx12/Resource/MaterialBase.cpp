#include <d3d12.h>
#include "../Resource/Mesh.h"
#include "../Render/BasicRender.h"
#include "../../../Component/Transform.h"
#include "MaterialBase.h"

MaterialBase::MaterialBase(Dx12Wrapper& dx12, const Math::Vector2& size)
{
	mesh_ = std::make_unique<Mesh>(dx12, size);
	transform_ = std::make_shared<Transform>(dx12);
}

MaterialBase::~MaterialBase()
{
}

void MaterialBase::Draw(BasicRender& render, CbMatrix& cbMat)
{
	render.Draw(*this, cbMat);
}

bool MaterialBase::PushResource(const std::shared_ptr<Dx12Resource>& resource)
{
	shaderResource.emplace_back(std::make_pair(resource, static_cast<int>(shaderResource.size()) + 2));
	return true;
}
