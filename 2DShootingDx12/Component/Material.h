#pragma once
#include <string>
#include "Component.h"
#include "../common/Math.h"

class MaterialBase;
class Dx12Resource;
class Dx12Wrapper;
class RenderManager;
class CbMatrix;

class Material :
	public Component
{
public:
	//Material(const std::basic_string<TCHAR>& path,Dx12Wrapper& dx12, const Math::Vector2& size);

	Material(std::shared_ptr<Dx12Resource>& tex, Dx12Wrapper& dx12);
	~Material();
	MaterialBase& GetMaterialBase(void) { return *materialBase_; }
	
	void Draw(RenderManager& renderMng, CbMatrix& cbMat);
private:
	void Begin(void) final;

	const ComponentID GetID(void)const noexcept final { return ComponentID::Material; }
	std::shared_ptr<Dx12Resource> tex_;
	std::shared_ptr<MaterialBase> materialBase_;
};

