#include <wrl.h>
#include <xaudio2.h>

#include <memory>
#include <vector>
#include <Windows.h>
#include "Sound.h"
#include "Xaudio2.h"
#include "Wave.h"
#include "SoundResource.h"

#include "Wave.h"







template<class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

int main(void)
{
	// Comの初期化
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
	{
		return -1;
	}

	Xaudio2 xaoudio;
	std::shared_ptr<Wave> wave = std::make_shared<Wave>();
	wave->Load("Pickup_Coin.wav");

	Sound sound{ xaoudio,wave };
	sound.Start();

	//// XAudio2の初期化
	//ComPtr<IXAudio2> xAudio2{ nullptr };
	//if (FAILED(XAudio2Create(&xAudio2, 0)))
	//{
	//	return -1;
	//}

	//// デバッグ用の設定
	//XAUDIO2_DEBUG_CONFIGURATION debug{ 0 };
	//	debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
	//	debug.BreakMask = XAUDIO2_LOG_ERRORS;
	//	xAudio2->SetDebugConfiguration(&debug, 0);

	//// マスターボイスの作成
	//IXAudio2MasteringVoice* maserVoice{ nullptr };
	//if (FAILED(xAudio2->CreateMasteringVoice(&maserVoice)))
	//{
	//	return -1;
	//}

	//SoundResource::GetInstance().Load(L"Pickup_Coin.wav");
	//auto& rData = SoundResource::GetInstance().GetData(L"Pickup_Coin.wav");

	//for (int i = 0; i < rData.data.size(); i++)
	//{
	//	if (rData.data[i] != wave->GetData()[i])
	//	{
	//		return -1;
	//	}
	//}

	//// ソースボイスの作成
	//IXAudio2SourceVoice* sourceVoice{ nullptr };
	//
	//
	//if (FAILED(xAudio2->CreateSourceVoice(&sourceVoice, rData.waveEx)))
	//{
	//	return -1;
	//}

	//XAUDIO2_BUFFER buf{};
	//
	//// 再生する波形データを設定
	//buf.pAudioData = rData.data.data();
	//buf.Flags = XAUDIO2_END_OF_STREAM;
	//buf.AudioBytes = sizeof(rData.data[0]) * rData.data.size();

	//XAUDIO2_BUFFER buf2{};
	//buf2.pAudioData = rData.data.data();
	//buf2.Flags = XAUDIO2_END_OF_STREAM;
	//buf2.AudioBytes = sizeof(rData.data[0]) * rData.data.size();

	//// 再生
	//auto r = sourceVoice->SubmitSourceBuffer(&buf);
	//r = sourceVoice->Start();
	//

	//
	//XAUDIO2_VOICE_STATE state{};
	//while (true) 
	//{
	//	sourceVoice->GetState(&state);
	//	if (state.BuffersQueued == 0)
	//	{
	//		break;
	//	}
	//}


	//// MFShutdown();
	//sourceVoice->DestroyVoice();
	//maserVoice->DestroyVoice();

	while (true)
	{
		if (sound.IsEnd())
		{
			break;
		}
	}
	
	CoUninitialize();
	return 0;
}