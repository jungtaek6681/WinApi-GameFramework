#include "pch.h"
#include "CSceneStage01.h"

#include "CGame.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCameraController.h"
#include "CSoundController.h"

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

	CMonster* monster = new CMonster();
	monster->SetPos(Vec2(CGame::WINSIZE.x * 0.5f, 100));
	AddGameObject(monster);

	CCameraController* controller = new CCameraController();
	AddGameObject(controller);

	CSoundController* sound = new CSoundController();
	AddGameObject(sound);
}

void CSceneStage01::Enter()
{
	CAMERA->FadeIn(0.5f);
}

void CSceneStage01::Update()
{
	if (INPUT->ButtonDown(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.5f);
		EVENT->ChangeScene(SceneType::Title, 0.5f);
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
