#include <fstream>
#include "TextureData.h"

struct Header
{
	char sig[4] = { 't','d', 'a','t' };
	int sum = 0;
};

TextureData::TextureData(const std::wstring& fileName)
{
	Load(fileName);
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

	// �摜�t�@�C���̖��O���擾
	int size;
	std::string imgFileName;
	wif.read(reinterpret_cast<char*>(&size), sizeof(size));
	imgFileName.resize(size);
	wif.read(reinterpret_cast<char*>(imgFileName.data()), sizeof(imgFileName[0]) * size);

	// �L�[�̖��O���擾
	int keyNameSize;
	std::string keyName;
	wif.read(reinterpret_cast<char*>(&keyNameSize), sizeof(keyNameSize));
	keyName.resize(keyNameSize);
	wif.read(reinterpret_cast<char*>(keyName.data()), sizeof(keyName[0]) * keyNameSize);

	int numMax;
	wif.read(reinterpret_cast<char*>(&numMax), sizeof(numMax));
	textureDataMap_[keyName].resize(numMax);
	wif.read(reinterpret_cast<char*>(&textureDataMap_[keyName][0]), sizeof(textureDataMap_[keyName][0]) * numMax);
	std::reverse(textureDataMap_[keyName].begin(), textureDataMap_[keyName].end());
	return false;
}