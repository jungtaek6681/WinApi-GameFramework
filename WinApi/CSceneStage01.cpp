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

	CPanel* panel = new CPanel();
	panel->SetScale(Vec2(200, 200));
	panel->SetPos(Vec2(100, 100));
	AddUI(panel);

	auto click1 = [](DWORD_PTR button1, DWORD_PTR param2) {
		CButton* button = (CButton*)button1;
		wstring text = button->GetName() + TEXT("이 클릭됨");
		Logger::Debug(text);
	};

	CButton* button1 = new CButton();
	button1->SetScale(Vec2(100, 50));
	button1->SetPos(Vec2(100, 100));
	button1->SetName(TEXT("버튼1"));
	button1->SetClickCallback(click1, (DWORD_PTR)button1, 0);
	AddUI(button1);

	auto click2 = [](DWORD_PTR sceneType, DWORD_PTR param2) {
		SceneType type = (SceneType)sceneType;
		CAMERA->FadeOut(0.5f);
		EVENT->ChangeScene(type, 0.5f);
	};

	CButton* button2 = new CButton();
	button2->SetScale(Vec2(100, 50));
	button2->SetPos(Vec2(50, 50));
	button2->SetClickCallback(click2, (DWORD_PTR)SceneType::Title, 0);
	panel->AddChild(button2);
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
}

void CSceneStage01::Exit()
{
}

void CSceneStage01::Release()
{
}
