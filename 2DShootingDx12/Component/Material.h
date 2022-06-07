#pragma once
#include <string>
#include <Windows.h>
#include "../GameSystem/Dx12/Resource/MaterialBase.h"



class Material :
	public MaterialBase
{
public:
	Material(const std::basic_string<TCHAR>& path,Dx12Wrapper& dx12, const Math::Vector2& size);
	~Material();

private:
	std::shared_ptr<Dx12Resource> tex_;
};

