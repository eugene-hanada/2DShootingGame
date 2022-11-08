#include <fstream>
#include "AnimationData.h"

struct Header
{
	char sig[4];
	int num;
};

AnimationData::AnimationData()
{
}

bool AnimationData::Load(const std::filesystem::path& path)
{
	std::ifstream file(path);
	if (!file)
	{
		// ファイルオープン失敗時
		return false;
	}
	Header h;
	file.read(reinterpret_cast<char*>(&h), sizeof(h));
	dataMap_.reserve(h.num);
	
	for (int i = 0; i < h.num; i++)
	{

		std::string name;
		int nameSize{0};
		int stateCount{0};

		// 名前のサイズを読み込む
		file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
		name.resize(nameSize);

		// 名前の読み込む
		file.read(reinterpret_cast<char*>(name.data()), sizeof(name[0]) * name.size());
		file.read(reinterpret_cast<char*>(&stateCount), sizeof(stateCount));
		dataMap_[name].reserve(stateCount);
		for (int k = 0; k < stateCount; k++)
		{
			int stateNameSize{0};
			std::string state;
			int loop;
			int dataCount;

			// ステート名のサイズを読み込む
			file.read(reinterpret_cast<char*>(&stateNameSize), sizeof(stateNameSize));
			state.resize(stateNameSize);

			// ステート名を読み込む
			file.read(reinterpret_cast<char*>(state.data()), sizeof(state[0]) * state.size());

			// ループ数を読み込む
			file.read(reinterpret_cast<char*>(&loop), sizeof(loop));

			// データ数を読み込む
			file.read(reinterpret_cast<char*>(&dataCount), sizeof(dataCount));

			dataMap_[name][state].loop = loop;
			dataMap_[name][state].idxData.resize(dataCount);

			// アニメーションのデータを取得する
			file.read(reinterpret_cast<char*>(dataMap_[name][state].idxData.data()), sizeof(dataMap_[name][state].idxData[0]) * dataMap_[name][state].idxData.size());
		}

	}

	return true;
}

AnimationData::Data* AnimationData::GetData(const std::string& key, const std::string& state)
{
	if (dataMap_.contains(key))
	{
		if (dataMap_[key].contains(state))
		{
			return &dataMap_[key][state];
		}
	}
	return nullptr;
}
