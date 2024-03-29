#pragma once
#include <wrl.h>

struct IXAudio2;
struct IXAudio2MasteringVoice;

// Xaudio2クラス
class Xaudio2
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Xaudio2();
	~Xaudio2();

	// Xaudio2の取得
	ComPtr<IXAudio2>& Get(void)&
	{
		return xAudio2_;
	}
private:

	// xaudio2
	ComPtr<IXAudio2> xAudio2_;

	// マスターヴォイス
	IXAudio2MasteringVoice* masterVoice_;
};

