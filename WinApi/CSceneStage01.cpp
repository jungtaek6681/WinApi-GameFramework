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

	CPanel* panel1 = new CPanel();
	panel1->SetScale(Vec2(200, 200));
	panel1->SetPos(Vec2(100, 100));
	AddUI(panel1);

	auto click1 = [](DWORD_PTR button1, DWORD_PTR param2) {
		CButton* button = (CButton*)button1;
		wstring text = button->GetName() + TEXT("이 클릭됨");
		Logger::Debug(text);
	};

	CButton* button1 = new CButton();
	button1->SetScale(Vec2(100, 50));
	button1->SetPos(Vec2(50, 50));
	button1->SetName(TEXT("버튼1"));
	button1->SetClickCallback(click1, (DWORD_PTR)button1, 0);
	panel1->AddChild(button1);

	CPanel* panel2 = new CPanel();
	panel2->SetScale(Vec2(200, 200));
	panel2->SetPos(Vec2(300, 100));
	AddUI(panel2);

	auto click2 = [](DWORD_PTR panel1, DWORD_PTR param2) {
		CPanel* panel = (CPanel*)panel1;
		EVENT->ShowUI(panel, !panel->IsShow());
	};

	CButton* button2 = new CButton();
	button2->SetScale(Vec2(100, 50));
	button2->SetPos(Vec2(50, 50));
	button2->SetClickCallback(click2, (DWORD_PTR)panel1, 0);
	panel2->AddChild(button2);
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
