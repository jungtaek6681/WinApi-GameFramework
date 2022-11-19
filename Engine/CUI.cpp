#include "pch.h"
#include "CUI.h"

CUI::CUI()
{
	name		= TEXT("");
	pos			= Vec2(0, 0);
	worldPos	= Vec2(0, 0);
	renderPos	= Vec2(0, 0);
	scale		= Vec2(0, 0);
	screenFixed	= true;
	show		= true;
}

CUI::~CUI()
{
}

void CUI::ComponentInit()
{
	Composite::ComponentInit();
}

void CUI::ComponentOnEnable()
{
	Composite::ComponentOnEnable();
}

void CUI::ComponentUpdate()
{
	if (IsReservedDelete())
		return;

	// 부모 게임오브젝트가 있는 경우, 위치는 부모를 기준으로한 상대위치
	if (GetOwner() != nullptr)
		worldPos = GetOwner()->GetWorldPos() + pos;
	// 부모 게임오브젝트가 없는 경우, 위치는 월드를 기준으로한 절대위치
	else
		worldPos = pos;

	if (IsScreenFixed())
		renderPos = worldPos;
	else
		renderPos = SINGLE(CCameraManager)->WorldToScreenPoint(worldPos);

	Composite::ComponentUpdate();
}

void CUI::ComponentRender()
{
	if (IsReservedDelete() || !IsShow())
		return;

	Composite::ComponentRender();
}

void CUI::ComponentOnDisable()
{
	Composite::ComponentOnDisable();
}

void CUI::ComponentRelease()
{
	Composite::ComponentRelease();
}
