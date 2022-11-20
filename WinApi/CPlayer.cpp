#include "pch.h"
#include "CPlayer.h"

#include "CMissile.h"

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

	if (INPUT->ButtonDown(VK_SPACE))
	{
		CreateMissile();
	}
}

void CPlayer::Render()
{
	RENDER->Rect(
		pos.x - scale.x * 0.5f,
		pos.y - scale.y * 0.5f,
		pos.x + scale.x * 0.5f,
		pos.y + scale.y * 0.5f);
}

void CPlayer::OnDisable()
{
}

void CPlayer::Release()
{
}

void CPlayer::CreateMissile()
{
	CMissile* missile = new CMissile();
	missile->SetPos(pos);
	EVENT->AddGameObject(GetScene(), missile);
}
