#include "../common/Debug.h"
#include "Window.h"

// ウインドウプロシージャ
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

Window::Window(int sizeX, int sizeY, const std::basic_string<TCHAR>& titleText) :
	size_{sizeX, sizeY},msg_{0}
{
	DebugStart();
#ifdef _DEBUG
	DebugLog("デバッグモードで開始");
#endif

	// Comを初期化
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
	{
		DebugLog("Comの初期化に失敗");
		
	}
	DebugLog("Comの初期化に成功");

	// ウィンドウクラスの設定と登録
	winClass_.cbSize = sizeof(WNDCLASSEX);
	winClass_.lpfnWndProc = (WNDPROC)WindowProcedure;
	winClass_.lpszClassName = TEXT("Window");
	winClass_.hInstance = GetModuleHandle(nullptr);
	if (!RegisterClassEx(&winClass_))
	{
		DebugLog("ウィンドウクラスの登録に失敗");
		Assert(false,"ウィンドウクラスの登録に失敗");
	}
	DebugLog("ウィンドウクラスの登録に成功");

	// ウィンドウのサイズ設定
	RECT wSize{ 0,0,size_.x, size_.y };
	if (!AdjustWindowRect(&wSize, WS_OVERLAPPEDWINDOW, false))
	{
		DebugLog("ウィンドウのサイズ設定に失敗");
		Assert(false, "ウィンドウのサイズ設定に失敗");
	}
	DebugLog("ウィンドウのサイズ設定に成功");
	
	// ウィンドウの生成
	hwnd_ = CreateWindow(
		winClass_.lpszClassName,
		titleText.c_str(),
		WS_OVERLAPPEDWINDOW,			// タイトルバーと境界線のあるウィンドウ
		CW_USEDEFAULT,					// OSに任せる
		CW_USEDEFAULT,
		wSize.right - wSize.left,		// ウィンドウ幅と高さ
		wSize.bottom - wSize.top,
		nullptr,
		nullptr,
		winClass_.hInstance,
		nullptr
	);
	DebugLog("ウィンドウを生成");

	ShowWindow(hwnd_, SW_SHOW);

}

Window::~Window()
{
	CoUninitialize();
	UnregisterClass(winClass_.lpszClassName, winClass_.hInstance);
	DebugLog("ウィンドウを破棄");
}

bool Window::LoopMessageProcess(void)
{
	if (PeekMessage(&msg_, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg_);
		DispatchMessage(&msg_);
	}
	if (msg_.message == WM_QUIT)
	{
		return false;
	}
	return true;
}
