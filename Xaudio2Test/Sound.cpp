#include "Sound.h"
#include <xaudio2.h>
#include "Wave.h"
#include "Xaudio2.h"

Sound::Sound(Xaudio2& xaoudio2, std::shared_ptr<Wave>& wave, unsigned int loopCount) :
	wave_{wave}, source_{nullptr}
{
	WAVEFORMATEX format{
		wave_->GetFmt().type,
		wave_->GetFmt().channel,
		wave_->GetFmt().sample,
		wave_->GetFmt().byte,
		wave_->GetFmt().block,
		wave_->GetFmt().bit,
		0u
	};

	if (FAILED(xaoudio2.Get()->CreateSourceVoice(&source_, &format)))
	{
		return;
	}

	buffer_ = std::make_unique<XAUDIO2_BUFFER>();
	buffer_->Flags = XAUDIO2_END_OF_STREAM;
	buffer_->pAudioData = wave_->GetData().data();
	buffer_->AudioBytes = wave_->GetData().size() * sizeof(wave_->GetData()[0]);
	//buffer_->LoopCount = loopCount;
	source_->SubmitSourceBuffer(buffer_.get());
}

Sound::~Sound()
{
	source_->DestroyVoice();
}

void Sound::Start(void)
{
	source_->Start();
}

void Sound::Stop(void)
{
	source_->Stop();
}

bool Sound::IsEnd(void) 
{
	XAUDIO2_VOICE_STATE state{};
	source_->GetState(&state);
	return state.BuffersQueued == 0;
}
