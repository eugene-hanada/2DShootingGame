#include "Window.h"
#include "Dx12Wrapper.h"
#include "Application.h"
#include "Dx12/Render/BasicRender.h"
#include "Dx12/Resource/MaterialBase.h"
#include "Dx12/Resource/Texture.h"
#include "Dx12/Resource/CbMatrix.h"
#include "Dx12/../../Component/Transform.h"
#include "../common/Debug.h"

Application Application::instance_;

bool Application::Init(int x, int y, const std::basic_string<TCHAR>& titleText)
{
	window_ = std::make_unique<Window>(x, y, titleText);
	dx12_ = std::make_unique<Dx12Wrapper>(*window_);
	return true;
}


int Application::Run(void)
{
	if (!Init(1280, 720, TEXT("Dx12")))
	{
		return -1;
	}

	//BasicRender rd(*dx12_);

	/*MaterialBase mat(*dx12_, Math::Vector2{ 100.0f,100.0f });
	auto t = std::make_shared<Transform>(*dx12_);
	t->SetPos({ 1000,50 });
	t->Update();
	mat.SetTransform(t);
	mat.PushResource(std::make_shared<Texture>(*dx12_,TEXT("Resource/image/Logo.jpg")));*/

	while (window_->LoopMessageProcess())
	{
		dx12_->BeginFinalRenderTarget();
		
		//mat.Draw(rd, dx12_->GetCbMat());

		dx12_->EndFinalRenderTarget();

		dx12_->DrawFinalRenderTarget();
	}
	return 0;
}

Application::Application()
{
	
}

Application::~Application()
{
	DebugLog("AppƒNƒ‰ƒX‚ð”jŠü");
}
