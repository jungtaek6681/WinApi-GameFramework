#include "pch.h"
#include "CSceneStage01.h"

#include "CGame.h"

CSceneStage01::CSceneStage01()
{
	moveDir	= Vec2(0.f, 0.f);
	pos		= Vec2(CGame::WINSIZE.x * 0.5f, CGame::WINSIZE.y * 0.5f);
	scale	= Vec2(100.f, 100.f);
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
}

void CSceneStage01::Enter()
{
}

void CSceneStage01::Update()
{
	if (BUTTONSTAY(VK_LEFT))
	{
		moveDir.x = -1;
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		moveDir.x = +1;
	}
	else
	{
		moveDir.x = 0;
	}

	if (BUTTONSTAY(VK_UP))
	{
		moveDir.y = -1;
	}
	else if (BUTTONSTAY(VK_DOWN))
	{
		moveDir.y = +1;
	}
	else
	{
		moveDir.y = 0;
	}

	pos += moveDir * 100 * DT;

	if (BUTTONDOWN(VK_ESCAPE))
	{
		SINGLE(CSceneManager)->ChangeScene(SceneType::Title);
	}
}

void CSceneStage01::Render()
{
	RENDER->SetPen(PenType::Solid, RGB(255, 0, 0), 1);
	RENDER->SetBrush(BrushType::Solid, RGB(0, 255, 0));
	RENDER->Rect(
		pos.x - scale.x * 0.5f,
		pos.y - scale.y * 0.5f,
		pos.x + scale.x * 0.5f,
		pos.y + scale.y * 0.5f
	);
	RENDER->SetPen();
	RENDER->SetBrush();
}

void CSceneStage01::Exit()
{
}

void CSceneStage01::Release()
{
}
