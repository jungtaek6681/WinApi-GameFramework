#include "pch.h"
#include "CMissile.h"

#include "CGame.h"

CMissile::CMissile()
{
	name = TEXT("πÃªÁ¿œ");
	scale = Vec2(20, 20);
	dir = Vec2(0, -1);
	speed = 400.f;
}

CMissile::~CMissile()
{
}

void CMissile::Init()
{
}

void CMissile::OnEnable()
{
}

void CMissile::Update()
{
	pos += dir * speed * DT;

	if (worldPos.x < 100 || worldPos.x > CGame::WINSIZE.x ||
		worldPos.y < 100 || worldPos.y > CGame::WINSIZE.y)
		EVENT->DeleteObject(GetScene(), this);
}

void CMissile::Render()
{
	RENDER->Ellipse(
		worldPos.x - scale.x * 0.5f,
		worldPos.y - scale.y * 0.5f,
		worldPos.x + scale.x * 0.5f,
		worldPos.y + scale.y * 0.5f);
}

void CMissile::OnDisable()
{
}

void CMissile::Release()
{
}
