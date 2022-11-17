#include "pch.h"
#include "CSceneStage01.h"

#include "CGame.h"
#include "CPlayer.h"
#include "CMonster.h"

CSceneStage01::CSceneStage01()
{
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	player = new CPlayer();
	player->SetPos(Vec2(CGame::WINSIZE.x * 0.5f, CGame::WINSIZE.y * 0.5f));
	AddGameObject(player);

	CMonster* monster = new CMonster();
	monster->SetPos(Vec2(CGame::WINSIZE.x * 0.5f, 100));
	AddGameObject(monster);
}

void CSceneStage01::Enter()
{
	CAMERA->SetTarget(player);
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
	Vec2 startPos = CAMERA->WorldToScreenPoint(Vec2(0, 0));
	Vec2 endPos = CAMERA->WorldToScreenPoint(Vec2(CGame::WINSIZE.x, CGame::WINSIZE.y));

	RENDER->SetBrush(BrushType::Null);
	RENDER->Rect(startPos.x, startPos.y, endPos.x, endPos.y);
	RENDER->SetBrush();
}

void CSceneStage01::Exit()
{
}

void CSceneStage01::Release()
{
}
