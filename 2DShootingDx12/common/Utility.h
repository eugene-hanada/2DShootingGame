#pragma once
#include <string>

class Utility
{
public:
	static std::wstring StringToWidthString(const std::string& str);
	static std::string WidthStringToString(const std::wstring& wstr);

	template<size_t size, size_t alignment>
	static constexpr size_t AlignmentedSize(void) noexcept
	{
		return size + alignment - size % alignment;
	}
};

