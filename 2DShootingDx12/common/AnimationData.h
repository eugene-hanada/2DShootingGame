#pragma once
#include <filesystem>
#include <unordered_map>


class AnimationData
{
public:

	struct Data
	{
		int loop;
		std::vector<std::pair<int, float>> idxData;
	};

	AnimationData();
	bool Load(const std::filesystem::path& path);
	Data* GetData(const std::string& key, const std::string& state);
private:
	std::unordered_map<std::string, std::unordered_map<std::string,Data>> dataMap_;
};

