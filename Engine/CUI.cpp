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

bool CUI::IsMouseOn()
{
	if (renderPos.x <= INPUT->MouseScreenPos().x && INPUT->MouseScreenPos().x <= renderPos.x + scale.x &&
		renderPos.y <= INPUT->MouseScreenPos().y && INPUT->MouseScreenPos().y <= renderPos.y + scale.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CUI::ComponentInit()
{
	Init();
	Composite::ComponentInit();
}

void CUI::ComponentOnEnable()
{
	OnEnable();
	Composite::ComponentOnEnable();
}

void CUI::ComponentUpdate()
{
	if (IsReservedDelete())
		return;

	// �θ� ���ӿ�����Ʈ�� �ִ� ���, ��ġ�� �θ� ���������� �����ġ
	if (GetOwner() != nullptr)
		worldPos = GetOwner()->GetWorldPos() + pos;
	// �θ� ���ӿ�����Ʈ�� ���� ���, ��ġ�� ���带 ���������� ������ġ
	else
		worldPos = pos;

	if (IsScreenFixed())
		renderPos = worldPos;
	else
		renderPos = SINGLE(CCameraManager)->WorldToScreenPoint(worldPos);

	Update();
	Composite::ComponentUpdate();
}

void CUI::ComponentRender()
{
	if (IsReservedDelete() || !IsShow())
		return;

	Render();
	Composite::ComponentRender();
}

void CUI::ComponentOnDisable()
{
	Composite::ComponentOnDisable();
	OnDisable();
}

void CUI::ComponentRelease()
{
	Composite::ComponentRelease();
	Release();
}
