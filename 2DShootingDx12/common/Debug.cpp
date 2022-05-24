#ifdef _DEBUG
#include <cassert>
#include <iomanip>
#include "Debug.h"

std::unique_ptr<DebugClass, DebugClass::Deleter> DebugClass::instance_ = nullptr;

void DebugClass::Create()
{
	if (instance_ == nullptr)
	{
		// ヌルポインターの時実体を作る
		instance_.reset(new DebugClass());
	}
}

DebugClass& DebugClass::GetInstance(void)
{
	return (*instance_);
}




DebugClass::DebugClass()
{
	// デバッグ出力用のコンソールを生成
	AllocConsole();

	// 標準出力で出力できるようにする
	conFp_ = nullptr;
	freopen_s(&conFp_, "CONOUT$", "w", stdout);
	freopen_s(&conFp_, "CONIN$", "r", stdin);

}

DebugClass::~DebugClass()
{

	fclose(conFp_);

}

#endif

