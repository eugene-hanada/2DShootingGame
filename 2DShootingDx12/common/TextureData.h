#pragma once
#include <string>
#include <windows.h>
#include <unordered_map>
#include <vector>
#include "Math.h"

class TextureData
{
	struct Data
	{
		Math::Vector2 pos;
		Math::Vector2 wh;
	};
	using TextureDataMap = std::unordered_map<std::string, std::vector<Data>>;
public:
	TextureData(const std::wstring& fileName);

private:
	bool Load(const std::wstring& fileName);
	TextureDataMap textureDataMap_;

};

