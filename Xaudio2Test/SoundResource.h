#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <string_view>

#include <mmeapi.h>

struct Data
{
	std::vector<unsigned char> data;
	WAVEFORMATEX* waveEx;
};

class SoundResource
{
public:
	bool Load(const std::wstring& fileName);
	Data& GetData(const std::wstring& fileName);
	static SoundResource& GetInstance()
	{
		static SoundResource instance;
		return instance;
	}
private:
	SoundResource();
	~SoundResource();
	SoundResource(const SoundResource&) = delete;
	SoundResource operator=(const SoundResource&) = delete;

	std::unordered_map<std::wstring,Data> dataMap_;
};

