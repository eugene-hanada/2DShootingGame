#pragma once
#include <memory>
#include <string>
#include <windef.h>
#include "Scene/SceneID.h"
#include "common/Time.h"
#include "common/Math.h"
#include "common/Random.h"

#define App (Application::GetInstance())
#define Time (Application::GetInstance().GetTime())
#define Rand (Application::GetInstance().GetRandom())
class Window;
class Dx12Wrapper;
class Mesh;
class BaseScene;
class RenderManager;
class InputSystem;
class Random;

class Application
{
public:
	static Application& GetInstance(void)
	{
		return instance_;
	}

	bool Init(int x, int y, const std::basic_string<TCHAR>& titleText);
	
	Window& GetWindow(void) { return *window_; };
	Dx12Wrapper& GetDx12(void) { return *dx12_; }
	int Run(void);
	const TimeClass& GetTime(void)const noexcept { return time_; }
	Random& GetRandom(void)&;
private:
	Application();
	~Application();

	// コピーコンストラクタと演算子を消去
	Application operator=(const Application&) = delete;
	Application(const Application&) = delete;

	static Application instance_;
	TimeClass time_;
	std::unique_ptr<Window> window_;
	std::unique_ptr<Dx12Wrapper> dx12_;
	std::unique_ptr<BaseScene> scene_;
	std::unique_ptr<Random> random_;
	std::shared_ptr<RenderManager> renderMng_;
	std::shared_ptr<InputSystem> input_;
	
};

