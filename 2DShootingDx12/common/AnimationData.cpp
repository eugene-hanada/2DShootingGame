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
		// �t�@�C���I�[�v�����s��
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

		// ���O�̃T�C�Y��ǂݍ���
		file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
		name.resize(nameSize);

		// ���O�̓ǂݍ���
		file.read(reinterpret_cast<char*>(name.data()), sizeof(name[0]) * name.size());
		file.read(reinterpret_cast<char*>(&stateCount), sizeof(stateCount));
		dataMap_[name].reserve(stateCount);
		for (int k = 0; k < stateCount; k++)
		{
			int stateNameSize{0};
			std::string state;
			int loop;
			int dataCount;

			// �X�e�[�g���̃T�C�Y��ǂݍ���
			file.read(reinterpret_cast<char*>(&stateNameSize), sizeof(stateNameSize));
			state.resize(stateNameSize);

			// �X�e�[�g����ǂݍ���
			file.read(reinterpret_cast<char*>(state.data()), sizeof(state[0]) * state.size());

			// ���[�v����ǂݍ���
			file.read(reinterpret_cast<char*>(&loop), sizeof(loop));

			// �f�[�^����ǂݍ���
			file.read(reinterpret_cast<char*>(&dataCount), sizeof(dataCount));

			dataMap_[name][state].loop = loop;
			dataMap_[name][state].idxData.resize(dataCount);

			// �A�j���[�V�����̃f�[�^���擾����
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
