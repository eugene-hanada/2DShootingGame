#pragma once
#include "../common/Math.h"
#include <Windows.h>
#include <string>

class Window
{
public:
	 Window(int sizeX, int sizeY, const std::basic_string<TCHAR>& titleText);
	~Window();
	
	template<class T>
	const Math::Vector2Tmp<T> GetSize(void) const { return static_cast<Math::Vector2Tmp<T>>(size_); }

	HWND& GetWwnd(void) { return hwnd_; }

	// メッセージ処理をする
	bool LoopMessageProcess(void);
private:
	const Math::Vector2I size_;
	HWND hwnd_;
	WNDCLASSEX winClass_;
	MSG msg_;
};

