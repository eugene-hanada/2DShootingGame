#include "Xaudio2.h"
#include <xaudio2.h>

#pragma comment(lib,"xaudio2.lib")

Xaudio2::Xaudio2()
{
	XAudio2Create(&xAudio2_, 0);
	// �f�o�b�O�p�̐ݒ�
	XAUDIO2_DEBUG_CONFIGURATION debug{ 0 };
	debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
	debug.BreakMask = XAUDIO2_LOG_ERRORS;
	xAudio2_->SetDebugConfiguration(&debug, 0);

	// �}�X�^�[�{�C�X�̍쐬
	xAudio2_->CreateMasteringVoice(&masterVoice_);
}

Xaudio2::~Xaudio2()
{
	masterVoice_->DestroyVoice();
}
