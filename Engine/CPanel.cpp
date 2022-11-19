#include "pch.h"
#include "CPanel.h"

CPanel::CPanel()
{
	dragStartPos	= Vec2(0, 0);
	isDragging		= false;
	draggable		= true;
}

CPanel::~CPanel()
{
}

void CPanel::Init()
{
}

void CPanel::OnEnable()
{
}

void CPanel::Update()
{
}

void CPanel::Render()
{
	RENDER->Rect(
		renderPos.x,
		renderPos.y,
		renderPos.x + scale.x,
		renderPos.y + scale.y
	);
}

void CPanel::OnDisable()
{
}

void CPanel::Release()
{
}

void CPanel::ComponentUpdate()
{
	if (IsReservedDelete())
		return;

	if (isDragging)
	{
		Vec2 diff = INPUT->MouseScreenPos() - dragStartPos;
		pos += diff;
		dragStartPos = INPUT->MouseScreenPos();
	}

	CUI::ComponentUpdate();
}

void CPanel::OnMouseEnter()
{
}

void CPanel::OnMouseOver()
{
}

void CPanel::OnMouseExit()
{ 
}

void CPanel::OnMouseUp()
{
	isDragging = false;
}

void CPanel::OnMouseDown()
{
	dragStartPos = INPUT->MouseScreenPos();
	isDragging = draggable;
}

void CPanel::OnMouseClicked()
{
}
