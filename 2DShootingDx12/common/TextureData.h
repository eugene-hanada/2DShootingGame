#pragma once
#include <string>
#include <windows.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Math.h"

class Texture;
class Dx12Wrapper;

class TextureData
{
	struct Data
	{
		Math::Vector2 pos;
		Math::Vector2 wh;
	};
	using TextureDataMap = std::unordered_map<std::string, std::vector<Data>>;
	using TextureDataPair = std::pair<TextureDataMap, Math::Vector2>;
	using DataMap = std::unordered_map<std::string, std::pair<std::shared_ptr<Texture>, TextureDataPair>>;
public:
	TextureData(Dx12Wrapper& dx12);
	const TextureDataPair& GetData(const std::string& imgKey)
	{
		if (!dataMap_.contains(imgKey))
		{
			throw "‰æ‘œ‚ª‘¶İ‚µ‚Ü‚¹‚ñ";
		}
		
		return dataMap_[imgKey].second;
	}

	std::shared_ptr<Texture>& GetTexture(const std::string& imgKey)
	{
		if (!dataMap_.contains(imgKey))
		{
			throw "‰æ‘œ‚ª‘¶İ‚µ‚Ü‚¹‚ñ";
		}
		return dataMap_[imgKey].first;
	}

	void Remove(const std::string& imgKey)
	{
		if (!dataMap_.contains(imgKey))
		{
			return;
		}
		dataMap_.erase(imgKey);
	}

	bool Load(const std::wstring& fileName);
private:
	

	// ‰æ‘œ‚Ìƒf[ƒ^
	DataMap dataMap_;

	Dx12Wrapper& dx12_;

};

