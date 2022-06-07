#include "../GameSystem/Dx12/Resource/Texture.h"
#include "Material.h"

Material::Material(const std::basic_string<TCHAR>& path, Dx12Wrapper& dx12, const Math::Vector2& size) :
	MaterialBase{dx12,size}
{
	tex_ = std::make_shared<Texture>(dx12, path);
	shaderResource_.emplace_back(tex_);
}

Material::~Material()
{
}
