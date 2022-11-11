#include <fstream>
#include "../GameSystem/Dx12/Resource/Texture.h"
#include "../common/Utility.h"
#include "TextureData.h"

struct Header
{
	char sig[4] = { 't','d', 'a','t' };
	int num = 0;
};

TextureData::TextureData(Dx12Wrapper& dx12) :
	dx12_{dx12}
{
}

bool TextureData::Load(const std::wstring& fileName)
{
	std::ifstream file{fileName,std::ios::binary};

	if (!file)
	{
		return false;
	}

	Header h;
	file.read(reinterpret_cast<char*>(&h), sizeof(h));

	// 画像ファイルの名前を読み込む
	int size;
	std::string imgFileName;
	file.read(reinterpret_cast<char*>(&size), sizeof(size));
	imgFileName.resize(size);
	file.read(reinterpret_cast<char*>(imgFileName.data()), sizeof(imgFileName[0]) * size);

	if (dataMap_.contains(imgFileName))
	{
		return false;
	}

	// 画像サイズを読み込む
	Math::Vector2 imgSize;
	file.read(reinterpret_cast<char*>(&imgSize), sizeof(imgSize));
	dataMap_[imgFileName].second.second = imgSize;
	dataMap_[imgFileName].first = std::make_shared<Texture>(dx12_, Utility::StringToWidthString("Resource/image/" + imgFileName));
	while (true)
	{
		// キーの名前を読み込む
		int keyNameSize;
		std::string keyName;
		file.read(reinterpret_cast<char*>(&keyNameSize), sizeof(keyNameSize));

		if (file.eof())
		{
			break;
		}

		keyName.resize(keyNameSize);
		file.read(reinterpret_cast<char*>(keyName.data()), sizeof(keyName[0]) * keyNameSize);

		int numMax;
		file.read(reinterpret_cast<char*>(&numMax), sizeof(numMax));
		dataMap_[imgFileName].second.first[keyName].resize(numMax);
		file.read(reinterpret_cast<char*>(&dataMap_[imgFileName].second.first[keyName][0]), sizeof(dataMap_[imgFileName].second.first[keyName][0]) * numMax);
		for (auto& d : dataMap_[imgFileName].second.first[keyName])
		{
			// 誤差でぶれるので少し小さめに修正
			d.pos += 0.5f;
			d.wh -= 0.5f;
		}
	}
	return true;
}
