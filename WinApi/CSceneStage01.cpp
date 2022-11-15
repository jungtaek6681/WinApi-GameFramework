#include "pch.h"
#include "CSceneStage01.h"

#include "CGame.h"
#include "CPlayer.h"

CSceneStage01::CSceneStage01()
{
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	CPlayer* player = new CPlayer();
	player->SetPos(Vec2(CGame::WINSIZE.x * 0.5f, CGame::WINSIZE.y * 0.5f));
	AddGameObject(player);
}

void CSceneStage01::Enter()
{
}

void CSceneStage01::Update()
{
	if (INPUT->ButtonDown(VK_ESCAPE))
	{
		EVENT->ChangeScene(SceneType::Title);
	}
}

void CSceneStage01::Render()
{
}

void CSceneStage01::Exit()
{
}

void CSceneStage01::Release()
{
}
