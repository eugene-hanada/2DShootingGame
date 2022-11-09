#include "Sound.h"
#include <xaudio2.h>
#include "../../GameSystem/Xaudio2/Wave.h"
#include "../../GameSystem/Xaudio2/Xaudio2.h"

Sound::Sound(Xaudio2& xaudio2, std::shared_ptr<Wave>& wave, unsigned int loopCount) :
	wave_{wave}, source_{nullptr}, isStop_{false}
{
	// 共有されたwaveファイルからフォーマットをセット
	WAVEFORMATEX format{
		wave_->GetFmt().type,
		wave_->GetFmt().channel,
		wave_->GetFmt().sample,
		wave_->GetFmt().byte,
		wave_->GetFmt().block,
		wave_->GetFmt().bit,
		0u
	};

	// ソース作成
	if (FAILED(xaudio2.Get()->CreateSourceVoice(&source_, &format)))
	{
		return;
	}

	// バッファをセット
	buffer_ = std::make_unique<XAUDIO2_BUFFER>();
	buffer_->Flags = XAUDIO2_END_OF_STREAM;
	buffer_->pAudioData = wave_->GetData().data();
	buffer_->AudioBytes = static_cast<unsigned int>(wave_->GetData().size() * sizeof(wave_->GetData()[0]));
	buffer_->LoopCount = loopCount;
	
}

Sound::~Sound()
{
	// ソースを破棄
	source_->DestroyVoice();
}

void Sound::Start(void)
{
	if (!isStop_)
	{
		// 再生中の時一度再生をやめ再度バッファをセットする
		source_->Stop();
		source_->FlushSourceBuffers();
		if (FAILED(source_->SubmitSourceBuffer(buffer_.get())))
		{
			return;
		}
	}

	// 再生を開始する
	source_->Start();
}

void Sound::Stop(void)
{
	if (isStop_)
	{
		// 停止
		return;
	}
	isStop_ = true;
	source_->Stop();
}

bool Sound::IsEnd(void) const
{
	XAUDIO2_VOICE_STATE state{};
	source_->GetState(&state);
	return state.BuffersQueued == 0;
}

void Sound::End(void)
{
	isStop_ = false;
}
