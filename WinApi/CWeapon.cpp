#include "pch.h"
#include "CWeapon.h"

#include "CMissile.h"

CWeapon::CWeapon()
{
	name = TEXT("¹«±â");
	scale = Vec2(30, 100);
}

CWeapon::~CWeapon()
{
}

void CWeapon::Init()
{
}

void CWeapon::OnEnable()
{
}

void CWeapon::Update()
{
	if (INPUT->ButtonDown(VK_SPACE))
	{
		CreateMissile();
	}
}

void CWeapon::Render()
{
	RENDER->Rect(
		worldPos.x - scale.x * 0.5f,
		worldPos.y - scale.y * 0.5f,
		worldPos.x + scale.x * 0.5f,
		worldPos.y + scale.y * 0.5f);
}

void CWeapon::OnDisable()
{
}

void CWeapon::Release()
{
}

void CWeapon::CreateMissile()
{
	CMissile* missile = new CMissile();
	missile->SetPos(Vec2(0, -50));
	EVENT->AddChild(this, missile);
}
