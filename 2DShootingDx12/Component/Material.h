#pragma once
#include <string>
#include <Windows.h>


class MaterialBase;
class Dx12Resource;

class Material
{
public:
	//Material(const std::basic_string<TCHAR>& path,Dx12Wrapper& dx12, const Math::Vector2& size);

	Material(std::shared_ptr<Dx12Resource>& tex, Dx12Wrapper& dx12, const Math::Vector2& size);
	~Material();

private:
	std::shared_ptr<Dx12Resource> tex_;
	std::shared_ptr<MaterialBase> materialBase_;
};

