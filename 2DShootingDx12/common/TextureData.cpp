#include <fstream>
#include "TextureData.h"

struct Header
{
	char sig[4] = { 't','d', 'a','t' };
	int sum = 0;
};

TextureData::TextureData(void)
{
}

bool TextureData::Load(const std::wstring& fileName)
{
	std::ifstream wif{fileName,std::ios::binary};

	if (!wif)
	{
		return false;
	}

	Header h;
	wif.read(reinterpret_cast<char*>(&h), sizeof(h));

	// 画像ファイルの名前を取得
	int size;
	std::string imgFileName;
	wif.read(reinterpret_cast<char*>(&size), sizeof(size));
	imgFileName.resize(size);
	wif.read(reinterpret_cast<char*>(imgFileName.data()), sizeof(imgFileName[0]) * size);

	if (!dataMap_.contains(imgFileName))
	{
		return false;
	}

	// 画像サイズを取得
	Math::Vector2 imgSize;
	wif.read(reinterpret_cast<char*>(&imgSize), sizeof(imgSize));

	while (true)
	{
		// キーの名前を取得
		int keyNameSize;
		std::string keyName;
		wif.read(reinterpret_cast<char*>(&keyNameSize), sizeof(keyNameSize));

		if (wif.eof())
		{
			break;
		}

		keyName.resize(keyNameSize);
		wif.read(reinterpret_cast<char*>(keyName.data()), sizeof(keyName[0]) * keyNameSize);

		int numMax;
		wif.read(reinterpret_cast<char*>(&numMax), sizeof(numMax));
		dataMap_[imgFileName][keyName].resize(numMax);
		wif.read(reinterpret_cast<char*>(&dataMap_[imgFileName][keyName][0]), sizeof(dataMap_[imgFileName][keyName][0]) * numMax);
	}
	return true;
}
