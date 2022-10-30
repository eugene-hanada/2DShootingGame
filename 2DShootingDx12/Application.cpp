#include "GameSystem/Window.h"
#include "GameSystem/Dx12Wrapper.h"
#include "Scene/TitleScene.h"
#include "Application.h"
#include "GameSystem/Dx12/Render/BasicRender.h"
#include "GameSystem/Dx12/Resource/MaterialBase.h"
#include "GameSystem/Dx12/Resource/Texture.h"
#include "GameSystem/Dx12/Resource/CbMatrix.h"
#include "GameSystem/Dx12/../../Component/Transform.h"
#include "GameSystem/Dx12/Render/RenderManager.h"
#include "GameSystem/Input/InputSystem.h"
#include "common/Random.h"
#include "common/Debug.h"

#include "GameSystem/Dx12/Resource/RenderTarget.h"

Application Application::instance_;

bool Application::Init(int x, int y, const std::basic_string<TCHAR>& titleText)
{
	window_ = std::make_unique<Window>(x, y, titleText);
	dx12_ = std::make_unique<Dx12Wrapper>(*window_);
	random_ = std::make_unique<Random>();
	return true;
}


int Application::Run(void)
{
	if (!Init(800, 600, TEXT("Dx12")))
	{
		return -1;
	}

	renderMng_ = std::make_shared<RenderManager>(*dx12_);
	input_ = std::make_shared<InputSystem>();
	scene_ = std::make_unique<TitleScene>(renderMng_, *dx12_,input_);
	
	time_.DeltaTimeStart();
	time_.DeltaTimeEnd();
	while (window_->LoopMessageProcess())
	{
		// �f���^�^�C���v���J�n
		time_.DeltaTimeStart();
		input_->Update();
		// �V�[�����A�b�v�f�[�g
		scene_ = scene_->Update(std::move(scene_));

		// �Q�[���̏���������
		time_.GameTimeEnd();

		// �V�[�����̕`��
		scene_->Draw();

		// �V�[����`��
		dx12_->BeginFinalRenderTarget();

		// �`�悵�����̂��t�@�C�i�������_�[�^�[�Q�b�g�ɕ`��
		scene_->Draw(dx12_->GetCbMat());

		dx12_->EndFinalRenderTarget();

		dx12_->DrawFinalRenderTarget();
		
		// �f���^�^�C���v���I��
		time_.DeltaTimeEnd();
	}
	return 0;
}

Random& Application::GetRandom(void)&
{
	return *random_;
}

Application::Application()
{
	
}

Application::~Application()
{
	DebugLog("App�N���X��j��");
}
