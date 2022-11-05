#pragma once
#include <wrl.h>

struct IXAudio2;
struct IXAudio2MasteringVoice;

class Xaudio2
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Xaudio2();
	~Xaudio2();
private:
	ComPtr<IXAudio2> xAudio2_;
	IXAudio2MasteringVoice* masterVoice_;
};

