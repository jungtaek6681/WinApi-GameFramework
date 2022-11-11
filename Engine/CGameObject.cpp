#include "pch.h"
#include "CGameObject.h"

CGameObject::CGameObject()
{
	name	= TEXT("");
	pos		= Vec2(0, 0);
	scale	= Vec2(0, 0);
}

CGameObject::~CGameObject()
{
}
