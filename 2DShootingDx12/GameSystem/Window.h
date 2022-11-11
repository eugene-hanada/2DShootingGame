#pragma once
#include "../common/Math.h"
#include <Windows.h>
#include <string>

// �E�B���h�E�Ɋւ���N���X
class Window
{
public:
	 Window(int sizeX, int sizeY, const std::basic_string<TCHAR>& titleText);
	~Window();
	
	/// <summary>
	/// �E�B���h�E�T�C�Y���擾
	/// </summary>
	/// <typeparam name="T"> �T�C�Y�̌^ </typeparam>
	/// <param name=""></param>
	/// <returns> �E�B���h�E�T�C�Y </returns>
	template<class T>
	const Math::Vector2Tmp<T> GetSize(void) const { return static_cast<Math::Vector2Tmp<T>>(size_); }

	/// <summary>
	/// �E�B���h�E�n���h���̎擾
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	HWND& GetWndHandle(void) { return hwnd_; }

	/// <summary>
	/// ���b�Z�[�W����������
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool LoopMessageProcess(void);
private:

	// �E�B���h�E�T�C�Y
	const Math::Vector2I size_;

	// �E�B���h�E�n���h��
	HWND hwnd_;

	// �E�B���h�E�N���X
	WNDCLASSEX winClass_;

	// ���b�Z�[�W
	MSG msg_;
};

