#pragma once
#include <wrl.h>

struct IXAudio2;
struct IXAudio2MasteringVoice;

// Xaudio2�N���X
class Xaudio2
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Xaudio2();
	~Xaudio2();

	// Xaudio2�̎擾
	ComPtr<IXAudio2>& Get(void)&
	{
		return xAudio2_;
	}
private:

	// xaudio2
	ComPtr<IXAudio2> xAudio2_;

	// �}�X�^�[���H�C�X
	IXAudio2MasteringVoice* masterVoice_;
};

