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
	// �̹� ��Ŀ�̵� UI�� ��� �������� ����
	if (focusedUI == ui)
		return;

	// ��Ŀ���� nullptr�� ������ ��� ��Ŀ�� UI �� nullptr�� ����
	if (nullptr == ui)
	{
		focusedUI = nullptr;
		return;
	}

	focusedUI = ui;

	// ��Ŀ�̵� UI�� �ֻ�ܿ� ��ġ�ϵ��� �ڷᱸ���� ���� �ڿ� ��ġ
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

	// ���� ���� �ִ� UI�� ���� ���ӿ�����Ʈ �ڷᱸ������ ���ʴ�� ��ȸ�ϸ� Render �Ѵٴ� ���� �̿��Ͽ�
	// ���� �������� �ִ� ���ӿ�����Ʈ�� ���� ���� �ִ� ���ӿ�����Ʈ
	// ������ �ݺ��� : ���� ���� ��Һ��� �������� ��ȸ
	for (auto iter = uiList.rbegin(); iter != uiList.rend(); iter++)
	{
		// �������� ��ȸ �� ������� ���콺�� �÷��� �ִ� UI�� ���콺 Ŭ���� ���
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

	// BFS �� ���ؼ� UI�� ���콺�� �ö� ���� �ڽ� UI Ȯ��
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
