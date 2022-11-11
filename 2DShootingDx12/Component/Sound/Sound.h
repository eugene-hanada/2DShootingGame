#pragma once
#include <memory>
#include "../Component.h"

struct IXAudio2SourceVoice;
struct XAUDIO2_BUFFER;
class Xaudio2;
class Wave;

// �T�E���h�Đ��N���X
class Sound :
	public Component
{
public:
	Sound(Xaudio2& xaudio2, std::shared_ptr<Wave>& wave, unsigned int loopCount = 0);
	~Sound();

	/// <summary>
	/// �T�E���h�̍Đ�����
	/// </summary>
	/// <param name=""></param>
	void Start(void);

	/// <summary>
	/// �Đ����~����
	/// </summary>
	/// <param name=""></param>
	void Stop(void);

	/// <summary>
	/// �Đ��I���������H
	/// </summary>
	/// <param name=""></param>
	/// <returns> �I����true�A�Đ���false </returns>
	bool IsEnd(void) const;
private:
	void End(void) final;

	// ��~���Ă��邩�̃t���O
	bool isStop_;
	const ComponentID GetID(void) const noexcept
	{
		return ComponentID::Sound;
	}

	// xaudio2�̃\�[�X
	IXAudio2SourceVoice* source_;

	// xaudio2�̃o�b�t�@
	std::unique_ptr<XAUDIO2_BUFFER> buffer_;

	// wave�t�@�C���̃f�[�^
	std::shared_ptr<Wave> wave_;
};

