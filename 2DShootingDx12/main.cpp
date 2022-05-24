#include <Windows.h>
#include "GameSystem/GameSystem.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int mCmdShow)
{
	GameSys.Init(1280, 720, TEXT("ƒeƒXƒg"));
	while (GameSys.LoopProcess())
	{
		GameSys.DrawBeginRenderTarget();
		GameSys.DrawEndRenderTarget();
		GameSys.DrawRenderTarget();
	}
	return 0;
}
