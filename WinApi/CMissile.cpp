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

	if (pos.x < 100 || pos.x > CGame::WINSIZE.x ||
		pos.y < 100 || pos.y > CGame::WINSIZE.y)
		EVENT->DeleteGameObject(GetScene(), this);
}

void CMissile::Render()
{
	RENDER->Ellipse(
		pos.x - scale.x * 0.5f,
		pos.y - scale.y * 0.5f,
		pos.x + scale.x * 0.5f,
		pos.y + scale.y * 0.5f);
}

void CMissile::OnDisable()
{
}

void CMissile::Release()
{
}
