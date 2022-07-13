#pragma once
#include <string>
#include <string_view>
#include <windows.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Math.h"

class Texture;

class TextureData
{
	struct Data
	{
		Math::Vector2 pos;
		Math::Vector2 wh;
	};
	using TextureDataMap = std::unordered_map<std::string, std::vector<Data>>;
	using DataMap = std::unordered_map<std::string, std::pair<std::shared_ptr<Texture>,TextureDataMap>>;
public:
	TextureData(void);
	const std::vector<Data>& GetData(std::string_view imgKey, std::string_view dataKey)
	{
		if (!dataMap_.contains(imgKey.data()))
		{
			throw "画像が存在しません";
		}
		if (!dataMap_[imgKey.data()].second.contains(dataKey.data()))
		{
			return dataMap_[imgKey.data()].second.begin()->second;
		}
		return dataMap_[imgKey.data()].second[dataKey.data()];
	}

	bool Load(const std::wstring& fileName);
private:
	

	// 画像のデータ
	DataMap dataMap_;

};

