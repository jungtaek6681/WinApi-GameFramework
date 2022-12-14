#include "pch.h"
#include "CCameraManager.h"

CCameraManager::CCameraManager()
{
	lookAt			= Vec2(0, 0);
	targetPos		= Vec2(0, 0);
	targetObj		= nullptr;
	timeToTarget	= 0;

	fadeImage		= nullptr;
	targetBright	= 1;
	curBright		= 1;
	timeToBright	= 0;
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::Init()
{
	fadeImage = new CImage();
	fadeImage->Create((UINT)SINGLE(CEngine)->GetWinSize().x, (UINT)SINGLE(CEngine)->GetWinSize().y);
	PatBlt(fadeImage->GetImageDC(), 0, 0, fadeImage->GetBmpWidth(), fadeImage->GetBmpHeight(), BLACKNESS);
}

void CCameraManager::Update()
{
	// 추적할 게임오브젝트가 있을 경우
	if (nullptr != targetObj)
	{
		if (targetObj->IsReservedDelete())
		{
			// 추적할 게임오브젝트가 삭제예정인 경우 추적 해제
			targetObj = nullptr;
		}
		else
		{
			// 추적할 게임오브젝트가 있을 경우 게임오브젝트의 위치를 목표위치로 지정
			targetPos = targetObj->GetPos();
		}
	}

	MoveToTarget();
	BrightToTarget();
}

void CCameraManager::Render()
{
	if (curBright >= 1)
		return;

	RENDER->BlendImage(
		fadeImage,
		0, 0,
		SINGLE(CEngine)->GetWinSize().x,
		SINGLE(CEngine)->GetWinSize().y,
		0, 0,
		(float)(fadeImage->GetBmpWidth()),
		(float)(fadeImage->GetBmpHeight()),
		(1 - curBright)
	);
}

void CCameraManager::Release()
{
	delete fadeImage;
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

void CCameraManager::Scroll(Vec2 dir, float velocity)
{
	// 스크롤의 방향 크기가 없는 경우 진행하지 않음
	if (dir.Magnitude() == 0)
		return;

	// 스크롤의 목표 위치는 현재위치에서 스크롤 방향으로 떨어진 위치
	targetPos = lookAt;
	targetPos += dir.Normalized() * velocity * DT;
	timeToTarget = 0;	// 스크롤은 시간차를 두지 않은 즉각 이동
}

void CCameraManager::FadeIn(float duration)
{
	targetBright = 1;
	timeToBright = duration;
}

void CCameraManager::FadeOut(float duration)
{
	targetBright = 0;
	timeToBright = duration;
}

void CCameraManager::SetTargetPos(const Vec2& targetPos, float timeToTarget)
{
	this->targetPos = targetPos;
	this->timeToTarget = timeToTarget;
}

void CCameraManager::SetTargetObj(CGameObject* targetObj)
{
	this->targetObj = targetObj;
}

void CCameraManager::MoveToTarget()
{
	timeToTarget -= DT;

	if (timeToTarget <= 0)
	{
		// 목표위치까지 남은 시간이 없을 경우 목적지로 현재위치 고정
		lookAt = targetPos;
	}
	else
	{
		// 목표위치까지 남은 시간이 있을 경우
		// 목적지까지 남은시간만큼의 속도로 이동
		// 이동거리 = 속력 * 시간
		// 속력 = (도착지 - 출발지) / 소요시간
		// 시간 = 프레임단위시간
		lookAt += (targetPos - lookAt) / timeToTarget * DT;
	}
}

void CCameraManager::BrightToTarget()
{
	timeToBright -= DT;

	if (timeToBright <= 0)
	{
		// 목표위치까지 남은 시간이 없을 경우 목적지로 현재위치 고정
		curBright = targetBright;
	}
	else
	{
		// 목표위치까지 남은 시간이 있을 경우
		// 목적지까지 남은시간만큼의 속도로 이동
		// 이동거리 = 속력 * 시간
		// 속력 = (도착지 - 출발지) / 소요시간
		// 시간 = 프레임단위시간
		curBright += (targetBright - curBright) / timeToBright * DT;
		if		(curBright > 1) curBright = 1;
		else if (curBright < 0) curBright = 0;
	}
}
