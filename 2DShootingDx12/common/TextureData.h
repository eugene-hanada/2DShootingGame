#pragma once
#include <string>
#include <string_view>
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
	using DataMap = std::unordered_map<std::string, TextureDataMap>;
public:
	TextureData(void);
	const std::vector<Data>& GetData(std::string_view imgKey, std::string_view dataKey)
	{
		if (!dataMap_.contains(imgKey.data()))
		{
			throw "‰æ‘œ‚ª‘¶İ‚µ‚Ü‚¹‚ñ";
		}
		if (!dataMap_[imgKey.data()].contains(dataKey.data()))
		{
			return dataMap_[imgKey.data()].begin()->second;
		}
		return dataMap_[imgKey.data()][dataKey.data()];
	}
private:
	bool Load(const std::wstring& fileName);

	// ‰æ‘œ‚Ìƒf[ƒ^
	DataMap dataMap_;

};

