#include "pch.h"
#include "CCameraManager.h"

CCameraManager::CCameraManager()
{
	lookAt	= Vec2(0, 0);
	target	= nullptr;
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::Init()
{
}

void CCameraManager::Update()
{
	// 추적할 게임오브젝트가 있을 경우
	if (nullptr != target)
	{
		if (target->IsReservedDelete())
		{
			// 추적할 게임오브젝트가 삭제예정인 경우 추적 해제
			target = nullptr;
		}
		else
		{
			// 추적할 게임오브젝트가 있을 경우 게임오브젝트의 위치를 목표위치로 지정
			lookAt = target->GetPos();
		}
	}
}

void CCameraManager::Release()
{
}

Vec2 CCameraManager::WorldToScreenPoint(Vec2 worldPoint)
{
	Vec2 center = SINGLE(CEngine)->GetWinSize() * 0.5f;
	return worldPoint - (lookAt - center);
}

Vec2 CCameraManager::ScreenToWorldPoint(Vec2 screenPoint)
{
	Vec2 center = SINGLE(CEngine)->GetWinSize() * 0.5f;
	return screenPoint + (lookAt - center);
}
