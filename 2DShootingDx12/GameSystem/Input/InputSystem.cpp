#include <Windows.h>
#include "InputSystem.h"



InputSystem::InputSystem()
{
	inputResult_.reserve(static_cast<int>(InputID::Esc) + 1);
	inputTable_.reserve(static_cast<int>(InputID::Esc) + 1);
	inputTable_.emplace(InputID::Up, InputCode{ VK_UP,XINPUT_GAMEPAD_DPAD_UP });
	inputTable_.emplace(InputID::Down, InputCode{ VK_DOWN,XINPUT_GAMEPAD_DPAD_DOWN });
	inputTable_.emplace(InputID::Right, InputCode{ VK_RIGHT,XINPUT_GAMEPAD_DPAD_RIGHT });
	inputTable_.emplace(InputID::Left, InputCode{ VK_LEFT,XINPUT_GAMEPAD_DPAD_LEFT });
	inputTable_.emplace(InputID::Esc, InputCode{ VK_ESCAPE,XINPUT_GAMEPAD_START});
	inputTable_.emplace(InputID::Shot, InputCode{ 'Z',XINPUT_GAMEPAD_A });
	inputTable_.emplace(InputID::Speed, InputCode{ VK_LSHIFT,XINPUT_GAMEPAD_LEFT_THUMB });

	key_.fill(0);
	padState_ = std::make_unique<XINPUT_STATE>();
	if (XInputGetState(0, padState_.get()) != ERROR_SUCCESS)
	{
		return;
	}

}

InputSystem::~InputSystem()
{
}

void InputSystem::Update()
{
	if (!GetKeyboardState(key_.data()) && (XInputGetState(0,padState_.get()) != ERROR_SUCCESS))
	{
		return;
	}
	
	for (auto& code : inputTable_)
	{
		inputResult_[code.first].second = inputResult_[code.first].first;
		inputResult_[code.first].first = (key_[code.second.key] & 0x80) | (padState_->Gamepad.wButtons & code.second.pad);
	}

}
