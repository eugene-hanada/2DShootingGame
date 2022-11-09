#include "Xaudio2.h"
#include <xaudio2.h>

Xaudio2::Xaudio2()
{
	XAudio2Create(&xAudio2_, 0);

#ifdef _DEBUG
	// デバッグ用の設定
	XAUDIO2_DEBUG_CONFIGURATION debug{ 0 };
	debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
	debug.BreakMask = XAUDIO2_LOG_ERRORS;
	xAudio2_->SetDebugConfiguration(&debug, 0);
#endif

	// マスターボイスの作成
	xAudio2_->CreateMasteringVoice(&masterVoice_);
}

Xaudio2::~Xaudio2()
{
	masterVoice_->DestroyVoice();
}
