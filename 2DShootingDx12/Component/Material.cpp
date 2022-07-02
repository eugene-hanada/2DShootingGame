#include "../GameSystem/Dx12/Resource/Texture.h"
#include "../GameSystem/Dx12/Resource/MaterialBase.h"
#include "Material.h"

//Material::Material(const std::basic_string<TCHAR>& path, Dx12Wrapper& dx12, const Math::Vector2& size) :
//	MaterialBase{dx12,size}
//{
//	tex_ = std::make_shared<Texture>(dx12, path);
//	shaderResource_.emplace_back(tex_);
//}

Material::Material(std::shared_ptr<Dx12Resource>& tex, Dx12Wrapper& dx12, const Math::Vector2& size)
{
	tex_ = tex;
	auto texP = std::dynamic_pointer_cast<Texture>(tex_);
	
	materialBase_ = std::make_shared<MaterialBase>(dx12, texP->GetSize());
	materialBase_->shaderResource_.emplace_back(tex_);
}

Material::~Material()
{
}
