#pragma once
#include <memory>

struct IXAudio2SourceVoice;
struct XAUDIO2_BUFFER;
class Xaudio2;
class Wave;

class Sound
{
public:
	Sound(Xaudio2& xaoudio2, std::shared_ptr<Wave>& wave, unsigned int loopCount = 0);
	~Sound();
	void Start(void);
	void Stop(void);
	bool IsEnd(void);
private:
	IXAudio2SourceVoice* source_;
	std::unique_ptr<XAUDIO2_BUFFER> buffer_;
	std::shared_ptr<Wave> wave_;
};

