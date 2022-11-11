#include "pch.h"
#include "CSceneStage01.h"

#include "CGame.h"
#include "CPlayer.h"

CSceneStage01::CSceneStage01()
{
	player = nullptr;
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	player = new CPlayer();
	player->SetPos(Vec2(CGame::WINSIZE.x * 0.5f, CGame::WINSIZE.y * 0.5f));
	player->Init();
}

void CSceneStage01::Enter()
{
	player->OnEnable();
}

void CSceneStage01::Update()
{
	player->Update();

	if (BUTTONDOWN(VK_ESCAPE))
	{
		SINGLE(CSceneManager)->ChangeScene(SceneType::Title);
	}
}

void CSceneStage01::Render()
{
	player->Render();
}

void CSceneStage01::Exit()
{
	player->OnDisable();
}

void CSceneStage01::Release()
{
	player->Release();
}
