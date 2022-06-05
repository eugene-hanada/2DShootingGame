#include "Time.h"

void TimeClass::DeltaTimeStart(void) noexcept
{
	deltaStart_ = std::chrono::system_clock::now();
	gameTimeStart_ = std::chrono::system_clock::now();
}

void TimeClass::DeltaTimeEnd(void)noexcept
{
	

	deltaEnd_ = std::chrono::system_clock::now();
	delta_ =  std::chrono::duration_cast<std::chrono::nanoseconds>(deltaEnd_ - deltaStart_).count() / 1000000000.0;
}

void TimeClass::GameTimeEnd(void) noexcept
{
	
	gameTimeEnd_ = std::chrono::system_clock::now();
	gameTime_ = std::chrono::duration_cast<std::chrono::nanoseconds>(gameTimeEnd_ - gameTimeStart_).count() / 1000000000.0;
}

