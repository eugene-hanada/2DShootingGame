#pragma once
#include <memory>
#include <string>
#include <Windows.h>

#define GameSys (GameSystem::GetInstance())

class Window;
class Dx12Wrapper;

class GameSystem
{
public:
	static GameSystem& GetInstance(void)
	{
		return *instance_;
	}

	static bool Init(int x, int y, const std::basic_string<TCHAR>& titleText);
	
	bool LoopProcess(void);
	void DrawBeginRenderTarget(void);
	void DrawEndRenderTarget(void);
	void DrawRenderTarget(void);
	
	Window& GetWindow(void) { return *window_; };
	Dx12Wrapper& GetDx12(void) { return *dx12_; }

private:
	GameSystem(int x, int y, const std::basic_string<TCHAR>& titleText);
	~GameSystem();

	// コピーコンストラクタと演算子を消去
	GameSystem operator=(const GameSystem&) = delete;
	GameSystem(const GameSystem&) = delete;

	struct Deleter {
		void operator()(GameSystem* p) {
			if (p != nullptr)
			{
				delete p;
			}
		}
	};

	static std::unique_ptr<GameSystem, GameSystem::Deleter> instance_;

	std::unique_ptr<Window> window_;
	std::unique_ptr<Dx12Wrapper> dx12_;
	
};

