#include "pch.h"
#include "CMissile.h"

CMissile::CMissile()
{
	name = TEXT("¹Ì»çÀÏ");
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
