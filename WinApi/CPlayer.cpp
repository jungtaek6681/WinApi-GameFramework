#include "pch.h"
#include "CPlayer.h"

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
	if (BUTTONSTAY(VK_LEFT))
	{
		pos.x -= speed * DT;
	}

	if (BUTTONSTAY(VK_RIGHT))
	{
		pos.x += speed * DT;
	}

	if (BUTTONSTAY(VK_UP))
	{
		pos.y -= speed * DT;
	}

	if (BUTTONSTAY(VK_DOWN))
	{
		pos.y += speed * DT;
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
