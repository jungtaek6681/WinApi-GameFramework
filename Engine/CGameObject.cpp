#include "pch.h"
#include "CGameObject.h"

CGameObject::CGameObject()
{
	name	= TEXT("");
	pos		= Vec2(0, 0);
	scale	= Vec2(0, 0);

	reservedDelete = false;
}

CGameObject::~CGameObject()
{
}

void CGameObject::ComponentInit()
{
	Init();
	Composite::ComponentInit();
}

void CGameObject::ComponentOnEnable()
{
	OnEnable();
	Composite::ComponentOnEnable();
}

void CGameObject::ComponentUpdate()
{
	if (IsReservedDelete())
		return;

	Update();
	Composite::ComponentUpdate();
}

void CGameObject::ComponentRender()
{
	if (IsReservedDelete())
		return;

	Composite::ComponentRender();
	Render();
}

void CGameObject::ComponentOnDisable()
{
	Composite::ComponentOnDisable();
	OnDisable();
}

void CGameObject::ComponentRelease()
{
	Composite::ComponentRelease();
	Release();
}
