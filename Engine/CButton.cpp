#include "pch.h"
#include "CButton.h"

CButton::CButton()
{
	callback	= nullptr;
	param1		= 0;
	param2		= 0;
}

CButton::~CButton()
{
}

void CButton::SetClickCallback(CallbackFunc callback, DWORD_PTR param1, DWORD_PTR param2)
{
	this->callback	= callback;
	this->param1	= param1;
	this->param2	= param2;
}

void CButton::Init()
{
}

void CButton::OnEnable()
{
}

void CButton::Update()
{
}

void CButton::Render()
{
	RENDER->Rect(
		renderPos.x,
		renderPos.y,
		renderPos.x + scale.x,
		renderPos.y + scale.y
	);
}

void CButton::OnDisable()
{
}

void CButton::Release()
{
}

void CButton::OnMouseEnter()
{
}

void CButton::OnMouseOver()
{
}

void CButton::OnMouseExit()
{
}

void CButton::OnMouseUp()
{
}

void CButton::OnMouseDown()
{
}

void CButton::OnMouseClicked()
{
	if (nullptr != callback)
		callback(param1, param2);
}
