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

	if (dataMap_.contains(imgFileName))
	{
		return false;
	}

	// 画像サイズを取得
	Math::Vector2 imgSize;
	wif.read(reinterpret_cast<char*>(&imgSize), sizeof(imgSize));
	dataMap_[imgFileName].second.second = imgSize;
	dataMap_[imgFileName].first = std::make_shared<Texture>(dx12_, Utility::StringToWidthString("Resource/image/" + imgFileName));
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
		dataMap_[imgFileName].second.first[keyName].resize(numMax);
		wif.read(reinterpret_cast<char*>(&dataMap_[imgFileName].second.first[keyName][0]), sizeof(dataMap_[imgFileName].second.first[keyName][0]) * numMax);
		for (auto& d : dataMap_[imgFileName].second.first[keyName])
		{
			// 誤差でぶれるので少し小さめに修正
			d.pos += 0.5f;
			d.wh -= 0.5f;
		}
	}
	return true;
}
