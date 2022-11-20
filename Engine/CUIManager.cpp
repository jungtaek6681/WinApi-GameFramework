#include "pch.h"
#include "CUIManager.h"

CUIManager::CUIManager()
{
	focusedUI = nullptr;
}

CUIManager::~CUIManager()
{
}

void CUIManager::Init()
{
}

void CUIManager::Update()
{
	CUI* topUI = GetTopUI();
	CUI* topChildUI = GetTopChildUI(topUI);

	if (INPUT->ButtonDown(VK_LBUTTON))
		SetFocusedUI(topUI);

	CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();
	const list<CUI*>& uiList = pCurScene->uiList;
	for (CUI* ui : uiList)
	{
		MouseEvent(ui, topChildUI);
	}
}

void CUIManager::Release()
{
}

CUI* CUIManager::GetFocusedUI()
{
	return focusedUI;
}

void CUIManager::SetFocusedUI(CUI* ui)
{
	// 이미 포커싱된 UI일 경우 진행하지 않음
	if (focusedUI == ui)
		return;

	// 포커싱을 nullptr로 지정할 경우 포커싱 UI 를 nullptr로 설정
	if (nullptr == ui)
	{
		focusedUI = nullptr;
		return;
	}

	focusedUI = ui;

	// 포커싱된 UI를 최상단에 배치하도록 자료구조의 가장 뒤에 배치
	CScene* curScene = SINGLE(CSceneManager)->GetCurScene();
	list<CUI*>& listUI = curScene->uiList;

	listUI.remove(focusedUI);
	listUI.push_back(focusedUI);
}

void CUIManager::MouseEvent(CUI* ui, CUI* topChildUI)
{
	if (ui->IsMouseOn() && ui->IsShow() && ui == topChildUI)
	{
		if (!ui->prevMouseOn)
		{
			ui->OnMouseEnter();
		}
		ui->prevMouseOn = true;
		ui->OnMouseOver();
		if (INPUT->ButtonDown(VK_LBUTTON))
		{
			ui->OnMouseDown();
			ui->prevDown = true;
		}
		else if (INPUT->ButtonUp(VK_LBUTTON))
		{
			ui->OnMouseUp();

			if (ui->prevDown)
			{
				ui->OnMouseClicked();
			}
			ui->prevDown = false;
		}
	}
	else
	{
		if (ui->prevMouseOn)
		{
			ui->OnMouseExit();		
		}
		ui->prevMouseOn = false;
		if (INPUT->ButtonUp(VK_LBUTTON))
		{
			ui->prevDown = false;
		}
	}

	for (Component<CUI>* childUI : ui->childList)
	{
		MouseEvent((CUI*)childUI, topChildUI);
	}
}

CUI* CUIManager::GetTopUI()
{
	CScene* curScene = SINGLE(CSceneManager)->GetCurScene();
	const list<CUI*>& uiList = curScene->uiList;

	// 가장 위에 있는 UI는 씬의 게임오브젝트 자료구조에서 차례대로 순회하며 Render 한다는 것을 이용하여
	// 가장 마지막에 있는 게임오브젝트가 제일 위에 있는 게임오브젝트
	// 역방향 반복자 : 가장 뒤의 요소부터 역순으로 순회
	for (auto iter = uiList.rbegin(); iter != uiList.rend(); iter++)
	{
		// 역순으로 순회 중 가장먼저 마우스가 올려져 있는 UI가 마우스 클릭의 대상
		CUI* pUI = static_cast<CUI*>(*iter);
		if (pUI->IsMouseOn())
		{
			return pUI;
		}
	}

	return nullptr;
}

CUI* CUIManager::GetTopChildUI(CUI* parentUI)
{
	if (nullptr == parentUI)
		return nullptr;

	queue<CUI*> queueUI;
	CUI* topChildUI = nullptr;

	// BFS 을 통해서 UI중 마우스가 올라간 가장 자식 UI 확인
	queueUI.push(parentUI);
	while (!queueUI.empty())
	{
		CUI* ui = queueUI.front();
		queueUI.pop();

		if (ui->IsMouseOn())
		{
			topChildUI = ui;
		}

		for (Component<CUI>* childUI : ui->childList)
		{
			queueUI.push((CUI*)childUI);
		}
	}

	return topChildUI;
}
