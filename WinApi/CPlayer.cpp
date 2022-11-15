#include "pch.h"
#include "CPlayer.h"

#include "CWeapon.h"

CPlayer::CPlayer()
{
	name	= TEXT("플레이어");
	scale	= Vec2(100, 100);
	speed	= 200.f;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	CWeapon* leftWeapon = new CWeapon();
	leftWeapon->SetPos(Vec2(-50, -20));
	leftWeapon->SetZOrder(-1);
	AddChild(leftWeapon);

	CWeapon* rightWeapon = new CWeapon();
	rightWeapon->SetPos(Vec2(+50, -20));
	rightWeapon->SetZOrder(+1);
	AddChild(rightWeapon);

	CCollider* collider = new CCollider();
	collider->SetScale(Vec2(90, 90));
	collider->SetLayer(Layer::Player);
	AddChild(collider);
}

void CPlayer::OnEnable()
{
}

void CPlayer::Update()
{
	if (INPUT->ButtonStay(VK_LEFT))
	{
		pos.x -= speed * DT;
	}

	if (INPUT->ButtonStay(VK_RIGHT))
	{
		pos.x += speed * DT;
	}

	if (INPUT->ButtonStay(VK_UP))
	{
		pos.y -= speed * DT;
	}

	if (INPUT->ButtonStay(VK_DOWN))
	{
		pos.y += speed * DT;
	}
}

void CPlayer::Render()
{
	RENDER->Rect(
		worldPos.x - scale.x * 0.5f,
		worldPos.y - scale.y * 0.5f,
		worldPos.x + scale.x * 0.5f,
		worldPos.y + scale.y * 0.5f);
}

void CPlayer::OnDisable()
{
}

void CPlayer::Release()
{
}
