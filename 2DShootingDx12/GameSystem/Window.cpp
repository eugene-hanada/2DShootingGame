#include "../common/Debug.h"
#include "Window.h"

// �E�C���h�E�v���V�[�W��
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
	DebugLog("�f�o�b�O���[�h�ŊJ�n");
#endif

	// Com��������
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
	{
		DebugLog("Com�̏������Ɏ��s");
		
	}
	DebugLog("Com�̏������ɐ���");

	// �E�B���h�E�N���X�̐ݒ�Ɠo�^
	winClass_.cbSize = sizeof(WNDCLASSEX);
	winClass_.lpfnWndProc = (WNDPROC)WindowProcedure;
	winClass_.lpszClassName = TEXT("Window");
	winClass_.hInstance = GetModuleHandle(nullptr);
	if (!RegisterClassEx(&winClass_))
	{
		DebugLog("�E�B���h�E�N���X�̓o�^�Ɏ��s");
		Assert(false,"�E�B���h�E�N���X�̓o�^�Ɏ��s");
	}
	DebugLog("�E�B���h�E�N���X�̓o�^�ɐ���");

	// �E�B���h�E�̃T�C�Y�ݒ�
	RECT wSize{ 0,0,size_.x, size_.y };
	if (!AdjustWindowRect(&wSize, WS_OVERLAPPEDWINDOW, false))
	{
		DebugLog("�E�B���h�E�̃T�C�Y�ݒ�Ɏ��s");
		Assert(false, "�E�B���h�E�̃T�C�Y�ݒ�Ɏ��s");
	}
	DebugLog("�E�B���h�E�̃T�C�Y�ݒ�ɐ���");
	
	// �E�B���h�E�̐���
	hwnd_ = CreateWindow(
		winClass_.lpszClassName,
		titleText.c_str(),
		WS_OVERLAPPEDWINDOW,			// �^�C�g���o�[�Ƌ��E���̂���E�B���h�E
		CW_USEDEFAULT,					// OS�ɔC����
		CW_USEDEFAULT,
		wSize.right - wSize.left,		// �E�B���h�E���ƍ���
		wSize.bottom - wSize.top,
		nullptr,
		nullptr,
		winClass_.hInstance,
		nullptr
	);
	DebugLog("�E�B���h�E�𐶐�");

	ShowWindow(hwnd_, SW_SHOW);

}

Window::~Window()
{
	CoUninitialize();
	UnregisterClass(winClass_.lpszClassName, winClass_.hInstance);
	DebugLog("�E�B���h�E��j��");
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
