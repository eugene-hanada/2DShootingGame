#pragma once
#include <string>
#include "../Component.h"
#include "../../common/AnimationData.h"

// �A�j���[�V�����𐧌䂷��N���X
class Animator :
	public Component
{
public:
	Animator(std::shared_ptr<AnimationData>& animData);
	~Animator();

	/// <summary>
	/// ���݂̃A�j���[�V������index���擾����
	/// </summary>
	/// <param name=""></param>
	/// <returns> ���݂�index </returns>
	const int GetIdx(void) const noexcept;

	/// <summary>
	/// ���݂̃A�j���[�V�����X�e�[�g���擾����
	/// </summary>
	/// <param name=""></param>
	/// <returns> ���݂̃X�e�[�g </returns>
	const std::string& GetState(void) const;

	/// <summary>
	/// �A�j���[�V�����X�e�[�g���Z�b�g����
	/// </summary>
	/// <param name="state"> �Z�b�g����X�e�[�g </param>
	void SetState(const std::string& state);

	/// <summary>
	/// �A�j���[�V�������I�����Ă��邩�H
	/// </summary>
	/// <param name=""></param>
	/// <returns> �I����true�A�A�j���[�V������false </returns>
	const bool IsEnd(void) const;
private:
	void Begin(void) final;
	void Update(ObjectManager& objectManager) final;
	const ComponentID GetID(void) const noexcept final { return ComponentID::Animator; }
	
	// �X�e�[�g
	std::string state_;

	// �A�j���[�V�����f�[�^
	AnimationData::Data* data_;

	// ���[�v��
	int loopCount_;

	// �Đ�����
	float playTime_;

	// �Đ��ʒu�̃C�e���[�^�[
	std::vector<std::pair<int, float>>::const_iterator nowItr_;

	// �A�j���[�V�����f�[�^
	std::shared_ptr<AnimationData> animData_;
};

