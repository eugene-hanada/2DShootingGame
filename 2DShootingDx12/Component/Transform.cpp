#include "Transform.h"

Transform::Transform(Dx12Wrapper& dx12) :
	CbMatrix{dx12}
{
}

Transform::~Transform()
{
}

void Transform::SetPos(const Math::Vector2& pos)
{
	DirectX::XMStoreFloat4x4(&mat_,DirectX::XMLoadFloat4x4(&mat_) * DirectX::XMMatrixTranslation(pos.x, pos.y, 0.0f));
}

const Math::Vector2 Transform::GetPos(void)
{
	Math::Vector2 ret;
	ret.x = mat_.m[3][0];
	ret.y = mat_.m[3][1];
	return ret;
}
