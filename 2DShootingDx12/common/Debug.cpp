#ifdef _DEBUG
#include <cassert>
#include <iomanip>
#include "Debug.h"

std::unique_ptr<DebugClass, DebugClass::Deleter> DebugClass::instance_ = nullptr;

void DebugClass::Create()
{
	if (instance_ == nullptr)
	{
		// �k���|�C���^�[�̎����̂����
		instance_.reset(new DebugClass());
	}
}

DebugClass& DebugClass::GetInstance(void)
{
	return (*instance_);
}




DebugClass::DebugClass()
{
	// �f�o�b�O�o�͗p�̃R���\�[���𐶐�
	AllocConsole();

	// �W���o�͂ŏo�͂ł���悤�ɂ���
	conFp_ = nullptr;
	freopen_s(&conFp_, "CONOUT$", "w", stdout);
	freopen_s(&conFp_, "CONIN$", "r", stdin);

}

DebugClass::~DebugClass()
{

	fclose(conFp_);

}

#endif

