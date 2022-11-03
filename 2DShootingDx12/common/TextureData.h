#pragma once
#include <string>
#include <windows.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Math.h"

class Texture;
class Dx12Wrapper;

// �e�N�X�`�����ꖇ�ɂ܂Ƃ߂����̂������N���X
class TextureData
{
	// �摜��̍��W�ƃT�C�Y
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
	/// �f�[�^��map�ƃT�C�Y��Ԃ�
	/// </summary>
	/// <param name="imgKey"> �摜�̃L�[ </param>
	/// <returns> �f�[�^��map�ƃT�C�Y </returns>
	const TextureDataPair& GetData(const std::string& imgKey)
	{
		if (!dataMap_.contains(imgKey))
		{
			throw "�摜�����݂��܂���";
		}
		
		return dataMap_[imgKey].second;
	}

	/// <summary>
	/// �e�X�N�`���̎擾
	/// </summary>
	/// <param name="imgKey"> �摜�̃L�[ </param>
	/// <returns> �e�N�X�`�� </returns>
	std::shared_ptr<Texture>& GetTexture(const std::string& imgKey)
	{
		if (!dataMap_.contains(imgKey))
		{
			throw "�摜�����݂��܂���";
		}
		return dataMap_[imgKey].first;
	}

	/// <summary>
	/// �摜�f�[�^�̍폜
	/// </summary>
	/// <param name="imgKey"> �摜�̃L�[ </param>
	void Remove(const std::string& imgKey)
	{
		if (!dataMap_.contains(imgKey))
		{
			return;
		}
		dataMap_.erase(imgKey);
	}

	/// <summary>
	/// �摜�f�[�^�̃��[�h
	/// </summary>
	/// <param name="fileName"> �t�@�C���� </param>
	/// <returns></returns>
	bool Load(const std::wstring& fileName);
private:
	

	// �摜�̃f�[�^
	DataMap dataMap_;

	// DirectX12�̃��b�v�N���X
	Dx12Wrapper& dx12_;

};

