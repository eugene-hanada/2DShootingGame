#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include "SoundResource.h"
#include <wrl.h>


#pragma comment(lib, "Mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "Mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")

template<class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

bool SoundResource::Load(const std::wstring& fileName)
{

	Data retData;
	// ソースリーダーの作成
	ComPtr<IMFSourceReader> mfSourceReader{ nullptr };
	MFCreateSourceReaderFromURL(fileName.c_str(), nullptr, &mfSourceReader);

	ComPtr<IMFMediaType> mfMediaType{ nullptr };
	if (FAILED(MFCreateMediaType(&mfMediaType)))
	{
		return false;
	}
	mfMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	mfMediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
	mfSourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mfMediaType.Get());

	mfMediaType->Release();
	mfMediaType.Detach();
	mfSourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &mfMediaType);


	

	// メディアタイプからデータを読み込む
	MFCreateWaveFormatExFromMFMediaType(mfMediaType.Get(), &retData.waveEx, nullptr);


	// データを読み込む
	
	while (true)
	{
		IMFSample* mfSample{ nullptr };
		DWORD dwStreamFlag{ 0 };
		mfSourceReader->ReadSample(
			MF_SOURCE_READER_FIRST_AUDIO_STREAM,
			0,
			nullptr,
			&dwStreamFlag,
			nullptr,
			&mfSample
		);

		if (dwStreamFlag & MF_SOURCE_READERF_ENDOFSTREAM)
		{
			break;
		}

		IMFMediaBuffer* mfMediaBuffer{ nullptr };
		mfSample->ConvertToContiguousBuffer(&mfMediaBuffer);

		BYTE* buffer{ nullptr };
		DWORD cbCurrentLength{ 0 };
		mfMediaBuffer->Lock(&buffer, nullptr, &cbCurrentLength);
		retData.data.resize(retData.data.size() + cbCurrentLength);
		std::memcpy(retData.data.data() + retData.data.size() - cbCurrentLength, buffer, cbCurrentLength);

		mfMediaBuffer->Unlock();
		mfMediaBuffer->Release();
		mfSample->Release();
	}

	dataMap_.emplace(
		fileName,
		retData
	);
	return true;
}

Data& SoundResource::GetData(const std::wstring& fileName)
{
	if (dataMap_.contains(fileName))
	{
		return dataMap_[fileName];
	}
	return dataMap_.begin()->second;
}

SoundResource::SoundResource()
{
	if (FAILED(MFStartup(MF_VERSION, MFSTARTUP_NOSOCKET)))
	{
		return;
	}
}

SoundResource::~SoundResource()
{
}
