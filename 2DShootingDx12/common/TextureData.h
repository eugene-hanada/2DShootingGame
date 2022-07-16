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
	using TextureDataPair = std::pair<TextureDataMap, Math::Vector2>;
	using DataMap = std::unordered_map<std::string, std::pair<std::shared_ptr<Texture>, TextureDataPair>>;
public:
	TextureData(void);
	const TextureDataPair& GetData(std::string_view imgKey)
	{
		if (!dataMap_.contains(imgKey.data()))
		{
			throw "�摜�����݂��܂���";
		}
		
		return dataMap_[imgKey.data()].second;
	}

	std::shared_ptr<Texture>& GetTexture(std::string_view imgKey)
	{
		if (!dataMap_.contains(imgKey.data()))
		{
			throw "�摜�����݂��܂���";
		}
		return dataMap_[imgKey.data()].first;
	}

	void Remove(std::string_view imgKey)
	{
		if (!dataMap_.contains(imgKey.data()))
		{
			return;
		}
		dataMap_.erase(imgKey.data());
	}

	bool Load(const std::wstring& fileName);
private:
	

	// �摜�̃f�[�^
	DataMap dataMap_;

};

