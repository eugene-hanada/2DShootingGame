#pragma once
#include <filesystem>
#include <unordered_map>

// �A�j���[�V�����f�[�^�̕ۊǂƃ��[�h���s���N���X
class AnimationData
{
public:

	// �f�[�^
	struct Data
	{
		// ���[�v��
		int loop;

		// index�ƕ\������
		std::vector<std::pair<int, float>> idxData;
	};

	AnimationData();

	/// <summary>
	/// �A�j���[�V�����f�[�^�̓ǂݍ���
	/// </summary>
	/// <param name="path"> �f�[�^�̃t�@�C���p�X </param>
	/// <returns></returns>
	bool Load(const std::filesystem::path& path);

	/// <summary>
	/// �A�j���[�V�����f�[�^�̎擾
	/// </summary>
	/// <param name="key"> �L�[ </param>
	/// <param name="state"> �A�j���[�V�����X�e�[�g </param>
	/// <returns></returns>
	Data* GetData(const std::string& key, const std::string& state);
private:

	// �A�j���[�V�����f�[�^�̃}�b�v
	std::unordered_map<std::string, std::unordered_map<std::string,Data>> dataMap_;
};

