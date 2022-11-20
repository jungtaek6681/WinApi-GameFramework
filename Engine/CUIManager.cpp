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
	CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();
	const list<CUI*>& uiList = pCurScene->uiList;
	for (CUI* ui : uiList)
	{
		MouseEvent(ui);
	}
}

void CUIManager::Release()
{
}

void CUIManager::MouseEvent(CUI* ui)
{
	if (ui->IsMouseOn() && ui->IsShow())
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
}
