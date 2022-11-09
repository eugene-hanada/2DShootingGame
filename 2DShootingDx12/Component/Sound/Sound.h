#pragma once
#include <memory>
#include "../Component.h"

struct IXAudio2SourceVoice;
struct XAUDIO2_BUFFER;
class Xaudio2;
class Wave;

// サウンド再生クラス
class Sound :
	public Component
{
public:
	Sound(Xaudio2& xaudio2, std::shared_ptr<Wave>& wave, unsigned int loopCount = 0);
	~Sound();

	/// <summary>
	/// サウンドの再生する
	/// </summary>
	/// <param name=""></param>
	void Start(void);

	/// <summary>
	/// 再生を停止する
	/// </summary>
	/// <param name=""></param>
	void Stop(void);

	/// <summary>
	/// 再生終了したか？
	/// </summary>
	/// <param name=""></param>
	/// <returns> 終了時true、再生中false </returns>
	bool IsEnd(void) const;
private:
	void End(void) final;

	// 停止しているかのフラグ
	bool isStop_;
	const ComponentID GetID(void) const noexcept
	{
		return ComponentID::Sound;
	}

	// xaudio2のソース
	IXAudio2SourceVoice* source_;

	// xaudio2のバッファ
	std::unique_ptr<XAUDIO2_BUFFER> buffer_;

	// waveファイルのデータ
	std::shared_ptr<Wave> wave_;
};

