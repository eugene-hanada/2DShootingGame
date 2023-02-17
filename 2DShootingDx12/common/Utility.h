#pragma once
#include <string>

class Utility
{
public:

	/// <summary>
	/// string��wstring�ɕϊ�����
	/// </summary>
	/// <param name="str"> �ϊ�����string </param>
	/// <returns> �ϊ�����wstring </returns>
	std::wstring StringToWidthString(const std::string& str);

	/// <summary>
	/// wstring��string�ɕϊ�����
	/// </summary>
	/// <param name="wstr"> �ϊ�����wstring </param>
	/// <returns> �ϊ�����string </returns>
	std::string WidthStringToString(const std::wstring& wstr);

	/// <summary>
	/// �A���C�����g���ꂽ�T�C�Y���v�Z����(�e���v���[�g�ŃT�C�Y�ƃA���C�����g�T�C�Y���w��)
	/// </summary>
	/// <param name=""></param>
	/// <returns> �A���C�����g���ꂽ�T�C�Y </returns>
	template<size_t size, size_t alignment>
	constexpr size_t AlignmentedSize(void) noexcept
	{
		return size + alignment - size % alignment;
	}
};

