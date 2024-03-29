#pragma once
#include <concepts>
#include <chrono>

template<class T>
// 時間用コンセプト整数値もしくは浮動小数点数を受け付けるようにする
concept TimeC = std::integral<T> || std::floating_point<T>;

class TimeClass
{
public:

	template<TimeC T>
	T GetDeltaTime(void) const noexcept;

	template<TimeC T>
	T GetGameTime(void) const noexcept;
	
	void DeltaTimeStart(void) noexcept;

	void DeltaTimeEnd(void) noexcept;

	void GameTimeEnd(void) noexcept;

private:

	double delta_;

	double gameTime_;


	// デルタタイム計測の終点
	std::chrono::system_clock::time_point deltaEnd_;

	// デルタタイム計測の始点
	std::chrono::system_clock::time_point deltaStart_;

	// 
	std::chrono::system_clock::time_point gameTimeEnd_;

	std::chrono::system_clock::time_point gameTimeStart_;
};

template<TimeC T>
constexpr T  convertNano = static_cast<T>(1) / static_cast<T>(1000000000.0);


template<TimeC T >
inline T TimeClass::GetDeltaTime(void) const noexcept
{
	return static_cast<T>(delta_);
}

template<TimeC T>
inline T TimeClass::GetGameTime(void) const noexcept
{
	return static_cast<T>(gameTime_);
}
