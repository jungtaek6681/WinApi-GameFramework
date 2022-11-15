#include "pch.h"
#include "CMissile.h"

#include "CGame.h"

CMissile::CMissile()
{
	name = TEXT("¹Ì»çÀÏ");
	scale = Vec2(20, 20);
	dir = Vec2(0, -1);
	speed = 200.f;
}

CMissile::~CMissile()
{
}

void CMissile::Init()
{
	CCollider* collider = new CCollider();
	collider->SetScale(Vec2(20, 20));
	collider->SetLayer(Layer::Missile);
	AddChild(collider);
}

void CMissile::OnEnable()
{
}

void CMissile::Update()
{
	pos += dir * speed * DT;

	if (worldPos.x < 0 || worldPos.x > CGame::WINSIZE.x ||
		worldPos.y < 0 || worldPos.y > CGame::WINSIZE.y)
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

void CMissile::OnCollisionEnter(CCollider* other)
{
	EVENT->DeleteObject(GetScene(), this);
}
