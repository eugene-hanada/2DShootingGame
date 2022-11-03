#pragma once
#include <string>
#include <windows.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Math.h"

class Texture;
class Dx12Wrapper;

// テクスチャを一枚にまとめたものを扱うクラス
class TextureData
{
	// 画像上の座標とサイズ
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

	/// <summary>
	/// データのmapとサイズを返す
	/// </summary>
	/// <param name="imgKey"> 画像のキー </param>
	/// <returns> データのmapとサイズ </returns>
	const TextureDataPair& GetData(const std::string& imgKey)
	{
		if (!dataMap_.contains(imgKey))
		{
			throw "画像が存在しません";
		}
		
		return dataMap_[imgKey].second;
	}

	/// <summary>
	/// テスクチャの取得
	/// </summary>
	/// <param name="imgKey"> 画像のキー </param>
	/// <returns> テクスチャ </returns>
	std::shared_ptr<Texture>& GetTexture(const std::string& imgKey)
	{
		if (!dataMap_.contains(imgKey))
		{
			throw "画像が存在しません";
		}
		return dataMap_[imgKey].first;
	}

	/// <summary>
	/// 画像データの削除
	/// </summary>
	/// <param name="imgKey"> 画像のキー </param>
	void Remove(const std::string& imgKey)
	{
		if (!dataMap_.contains(imgKey))
		{
			return;
		}
		dataMap_.erase(imgKey);
	}

	/// <summary>
	/// 画像データのロード
	/// </summary>
	/// <param name="fileName"> ファイル名 </param>
	/// <returns></returns>
	bool Load(const std::wstring& fileName);
private:
	

	// 画像のデータ
	DataMap dataMap_;

	// DirectX12のラップクラス
	Dx12Wrapper& dx12_;

};

