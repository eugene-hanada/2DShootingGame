#include <d3d12.h>
#include "../Resource/Mesh.h"
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


