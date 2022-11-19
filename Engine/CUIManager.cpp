#include "pch.h"
#include "CUIManager.h"

CUIManager::CUIManager()
{
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
