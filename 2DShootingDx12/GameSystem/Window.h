#pragma once
#include "../common/Math.h"
#include <Windows.h>
#include <string>

// ウィンドウに関するクラス
class Window
{
public:
	 Window(int sizeX, int sizeY, const std::basic_string<TCHAR>& titleText);
	~Window();
	
	/// <summary>
	/// ウィンドウサイズを取得
	/// </summary>
	/// <typeparam name="T"> サイズの型 </typeparam>
	/// <param name=""></param>
	/// <returns> ウィンドウサイズ </returns>
	template<class T>
	const Math::Vector2Tmp<T> GetSize(void) const { return static_cast<Math::Vector2Tmp<T>>(size_); }

	/// <summary>
	/// ウィンドウハンドルの取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	HWND& GetWndHandle(void) { return hwnd_; }

	/// <summary>
	/// メッセージ処理をする
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool LoopMessageProcess(void);
private:

	// ウィンドウサイズ
	const Math::Vector2I size_;

	// ウィンドウハンドル
	HWND hwnd_;

	// ウィンドウクラス
	WNDCLASSEX winClass_;

	// メッセージ
	MSG msg_;
};

