#pragma once
#include <memory>
#include "../Component.h"

struct IXAudio2SourceVoice;
struct XAUDIO2_BUFFER;
class Xaudio2;
class Wave;

class Sound :
	public Component
{
public:
	Sound(Xaudio2& xaudio2, std::shared_ptr<Wave>& wave, unsigned int loopCount = 0);
	~Sound();
	void Start(void);
	void Stop(void);
	bool IsEnd(void) const;
private:
	void End(void) final;
	bool isStop_;
	const ComponentID GetID(void) const noexcept
	{
		return ComponentID::Sound;
	}
	IXAudio2SourceVoice* source_;
	std::unique_ptr<XAUDIO2_BUFFER> buffer_;
	std::shared_ptr<Wave> wave_;
};

