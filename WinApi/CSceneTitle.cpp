#include "pch.h"
#include "CSceneTitle.h"

#include "CGame.h"

CSceneTitle::CSceneTitle()
{
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
}

void CSceneTitle::Enter()
{
	CAMERA->FadeIn(0.5f);
}

void CSceneTitle::Update()
{
	if (INPUT->ButtonDown(VK_SPACE))
	{
		EVENT->ChangeScene(SceneType::Stage01);
	}
}

void CSceneTitle::Render()
{
	RENDER->SetText(20);
	RENDER->Text(CGame::WINSIZE.x * 0.5f, CGame::WINSIZE.y * 0.5f, TEXT("press space to start"));
	RENDER->SetText();
}

void CSceneTitle::Exit()
{
	CAMERA->FadeOut(0.5f);
}

void CSceneTitle::Release()
{
}
