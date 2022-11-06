#pragma once
#include <filesystem>
#include <vector>

class Wave
{
public:
	struct FMT
	{
		unsigned int size;
		unsigned short type;
		unsigned short channel;
		unsigned int sample;
		unsigned int byte;
		unsigned short block;
		unsigned short bit;
	};

	Wave();
	bool Load(const std::filesystem::path& path);
	const FMT& GetFmt(void) const&
	{
		return fmt_;
	}

	const std::vector<unsigned char>& GetData(void) const&
	{
		return data_;
	}

private:
	std::vector<unsigned char> data_;
	FMT fmt_;
	struct RIFF
	{
		char id[4];
		unsigned int size;
		char type[4];
	};

	

	struct DataHeader
	{
		char id[4];
		unsigned int size;
	};

};

