#include "pch.h"
#include "CGameObject.h"

CGameObject::CGameObject()
{
	name	= TEXT("");
	pos		= Vec2(0, 0);
	scale	= Vec2(0, 0);
	zOrder	= 0;
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

	// 부모 게임오브젝트가 있는 경우, 위치는 부모를 기준으로한 상대위치
	if (GetOwner() != nullptr)
		worldPos = GetOwner()->GetWorldPos() + pos;
	// 부모 게임오브젝트가 없는 경우, 위치는 월드를 기준으로한 절대위치
	else
		worldPos = pos;

	renderPos = SINGLE(CCameraManager)->WorldToScreenPoint(worldPos);

	Update();
	Composite::ComponentUpdate();
}

void CGameObject::ComponentRender()
{
	if (IsReservedDelete())
		return;

	GetScene()->AddRenderer(this);
	Composite::ComponentRender();
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
