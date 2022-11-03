#pragma once
#include <string>

class Utility
{
public:

	/// <summary>
	/// stringをwstringに変換する
	/// </summary>
	/// <param name="str"> 変換するstring </param>
	/// <returns> 変換したwstring </returns>
	static std::wstring StringToWidthString(const std::string& str);

	/// <summary>
	/// wstringをstringに変換する
	/// </summary>
	/// <param name="wstr"> 変換するwstring </param>
	/// <returns> 変換したstring </returns>
	static std::string WidthStringToString(const std::wstring& wstr);

	/// <summary>
	/// アライメントされたサイズを計算する(テンプレートでサイズとアライメントサイズを指定)
	/// </summary>
	/// <param name=""></param>
	/// <returns> アライメントされたサイズ </returns>
	template<size_t size, size_t alignment>
	static constexpr size_t AlignmentedSize(void) noexcept
	{
		return size + alignment - size % alignment;
	}
};

