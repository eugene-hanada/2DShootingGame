#pragma once
#include <unordered_map>
#include <string_view>
#include <array>
#include <memory>
#include <windows.h>
#include <Xinput.h>

enum class InputID
{
	Up,			// 上
	Down,		// 下
	Right,		// 右
	Left,		// 左
	Shot,		// 射撃
	Speed,		// スピード切替
	Esc			// エスケープキー
};



// キーボードやコントローラーの情報取得
class InputSystem
{
public:
	InputSystem();
	~InputSystem();
	void Update();
	
	/// <summary> キーが押されたかどうか </summary> 
	/// <param name="id"> 入力ID </param>
	/// <returns> 押されて入ればtrue </returns>
	bool IsPressed(InputID id) const { return inputResult_.at(id).first && !inputResult_.at(id).second; }

	/// <summary> キーが長押しされているか </summary>
	/// <param name="id"> キーの種類 </param>
	/// <returns> 長押しされていればtrue </returns>
	bool IsPressedStay(InputID id) const { return inputResult_.at(id).first && inputResult_.at(id).second; }

	/// <summary>
	/// キーを話しな瞬間か
	/// </summary>
	/// <param name="id"> キーの種類 </param>
	/// <returns> 話した瞬間ならtrue </returns>
	bool IsRelesed(InputID id) const { return !inputResult_.at(id).first && inputResult_.at(id).second; }

private:

	struct InputCode
	{
		int key = 0;
		int pad = 0;
	};

	// 入力の結果
	std::unordered_map<InputID, std::pair<bool,bool>> inputResult_;

	// キーボードの入力情報
	std::array<unsigned char, 256> key_;

	// ゲームパッドの入力情報
	std::unique_ptr<XINPUT_STATE> padState_;

	// idとコードのテーブル
	std::unordered_map<InputID, InputCode> inputTable_;
};

