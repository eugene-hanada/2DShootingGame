#pragma once
#include <cassert>
#ifdef _DEBUG
#include <Windows.h>	// OutPutDebugStringnがある所
#include <iostream>		// コンソールに標準出力
#include <sstream>		// stringの上位版文字列ストリーム
#include <array>
#include <memory>		// ユニークポインタとかの

// クリエイト関数を呼ぶマクロ関数
#define DebugStart() (DebugClass::Create())

// デバッグのセットアップをする
#define DebugSetUp() (DebugClass::GetInstance().SetUp())

// デバッグコンソールに出力する
#define DebugLog(...) (DebugClass::GetInstance().Log(__VA_ARGS__))

// visualstudioの出力の欄に出力する
#define DebugOutput(...) (DebugClass::GetInstance().Out(__VA_ARGS__))

// デバッグ情報の描画
#define DebugInfoDraw(delta) (DebugClass::GetInstance().DebugDraw(delta))

// 自作のassertみたいなの
#define Assert(val,mess) ( (val) || (_wassert(_CRT_WIDE(mess), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)),0))


class DebugClass
{
public:

	// クリエイト関数
	static void Create();

	// 実体を取得する
	static DebugClass& GetInstance(void);

	// コンソールに出力する
	template<class T>
	void Log(const T& t);

	template<class T, class... A>
	void Log(const T& t,const A&... a);


	// VisualStudioの出力の欄に出力する
	template<class T>
	void Out(const T& t);

	template<class T, class... A>
	void Out(const T& t, const A&... a);
	

	
private:
	// コンストラクタ
	DebugClass();

	// デストラクタ
	~DebugClass();

	// デリーター
	struct Deleter
	{
		void operator()(DebugClass* p)
		{
			delete p;
		}
	};

	// 実体をユニークポインタで持つ
	static std::unique_ptr<DebugClass, Deleter> instance_;


	// ファイルポインタ
	FILE* conFp_;


	// 停止フラグ
	bool stopFlag_;

	
};

template<class T>
inline void DebugClass::Log(const T& t)
{
	std::cout << t << std::endl;
}

template<class T, class ...A>
inline void DebugClass::Log(const T& t, const A & ...a)
{
	// デバッグモードの時だけ
	std::cout << t;
	Log(a...);
}

template<class T>
inline void DebugClass::Out(const T& t)
{
	// デバッグモードの時だけ
#ifdef UNICODE
	// ユニコードの時こっち
	std::wstringstream ss;
	ss << t << std::endl;
	OutputDebugString(ss.str().c_str());
#else
	std::stringstream ss(t);
	OutputDebugString(ss.str().c_str());
#endif
}

template<class T, class ...A>
inline void DebugClass::Out(const T& t, const A & ...a)
{
#ifdef UNICODE
	// ユニコードの時こっち
	std::wstringstream ss;
	ss << t;
	OutputDebugString(ss.str().c_str());
	Out(a...);
#else
	std::stringstream ss(t);
	OutputDebugString(ss.str().c_str());
	Out(a...);
#endif
}





#else

#define DebugStart() 

#define DebugSetUp() 

#define DebugLog(...)

#define DebugOutput(...) 

#define DebugInfoDraw(delta) 

#define Assert(val,mess) (val)

#endif







