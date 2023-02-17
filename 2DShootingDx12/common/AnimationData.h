#pragma once
#include <filesystem>
#include <unordered_map>

// アニメーションデータの保管とロードを行うクラス
class AnimationData
{
public:

	// データ
	struct Data
	{
		// ループ回数
		int loop;

		// indexと表示時間
		std::vector<std::pair<int, float>> idxData;
	};

	AnimationData();

	/// <summary>
	/// アニメーションデータの読み込み
	/// </summary>
	/// <param name="path"> データのファイルパス </param>
	/// <returns></returns>
	bool Load(const std::filesystem::path& path);

	/// <summary>
	/// アニメーションデータの取得
	/// </summary>
	/// <param name="key"> キー </param>
	/// <param name="state"> アニメーションステート </param>
	/// <returns></returns>
	Data* GetData(const std::string& key, const std::string& state);
private:

	// アニメーションデータのマップ
	std::unordered_map<std::string, std::unordered_map<std::string,Data>> dataMap_;
};

