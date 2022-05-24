#include "Window.h"
#include "Dx12Wrapper.h"
#include "GameSystem.h"

std::unique_ptr<GameSystem, GameSystem::Deleter> GameSystem::instance_ = nullptr;

bool GameSystem::Init(int x, int y, const std::basic_string<TCHAR>& titleText)
{
	if (instance_ == nullptr)
	{
		instance_.reset(new GameSystem(x, y, titleText));
		return true;
	}
	return false;
}

bool GameSystem::LoopProcess(void)
{
	return window_->LoopMessageProcess();
}

void GameSystem::DrawBeginRenderTarget(void)
{
	dx12_->BeginFinalRenderTarget();
}

void GameSystem::DrawEndRenderTarget(void)
{
	dx12_->EndFinalRenderTarget();
}

void GameSystem::DrawRenderTarget(void)
{
	dx12_->DrawFinalRenderTarget();
}

GameSystem::GameSystem(int x, int y, const std::basic_string<TCHAR>& titleText)
{
	window_ = std::make_unique<Window>(x, y, titleText);
	dx12_ = std::make_unique<Dx12Wrapper>(*window_);
}

GameSystem::~GameSystem()
{
}
