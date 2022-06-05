#pragma once
#include <unordered_map>
#include <string_view>
#include <array>
#include <memory>
#include <Xinput.h>

enum class InputID
{
	Up,			// ��
	Down,		// ��
	Right,		// �E
	Left,		// ��
	Shot1,		// �ˌ�1
	Shot2,		// �ˌ�2
	Speed,		// �X�s�[�h�ؑ�
	Esc			// �G�X�P�[�v�L�[
};



// �L�[�{�[�h��R���g���[���[�̏��擾
class InputSystem
{
public:
	InputSystem();
	~InputSystem();
	void Update();
	
	/// <summary> �L�[�������ꂽ���ǂ��� </summary> 
	/// <param name="id"> ����ID </param>
	/// <returns> ������ē����true </returns>
	bool IsPressed(InputID id) const { return inputResult_.at(id).first && !inputResult_.at(id).second; }

	/// <summary> �L�[������������Ă��邩 </summary>
	/// <param name="id"> �L�[�̎�� </param>
	/// <returns> ����������Ă����true </returns>
	bool IsPressedStay(InputID id) const { return inputResult_.at(id).first && inputResult_.at(id).second; }


	bool IsRelesed(InputID id) const { return !inputResult_.at(id).first && inputResult_.at(id).second; }

private:

	struct InputCode
	{
		int key = 0;
		int pad = 0;
	};

	std::unordered_map<InputID, std::pair<bool,bool>> inputResult_;
	std::array<unsigned char, 256> key_;
	std::unique_ptr<XINPUT_STATE> padState_;
	std::unordered_map<InputID, InputCode> inputTable_;
};

