#include "pch.h"
#include "CAnimator.h"

CAnimator::CAnimator()
{
	curAnimation	= nullptr;
	playing			= false;
	ratio			= 1;
	curFrame		= 0;
	curTime			= 0;
}

CAnimator::~CAnimator()
{
}

void CAnimator::AddAnimation(const wstring& aniName, CAnimation* animation)
{
	CAnimation* ani = FindAnimation(aniName);
	assert(nullptr == ani && "Animation already exist");

	animation->SetKey(aniName);
	animation->SetPath(TEXT(""));
	animationMap.insert(make_pair(aniName, animation));
}

void CAnimator::RemoveAnimation(const wstring& aniName)
{
	CAnimation* ani = FindAnimation(aniName);

	if (nullptr != ani)
	{
		animationMap.erase(aniName);
		delete ani;
	}
}

CAnimation* CAnimator::FindAnimation(const wstring& aniName)
{
	auto iter = animationMap.find(aniName);
	if (iter == animationMap.end())
		return nullptr;
	else
		return iter->second;
}

void CAnimator::CreateAnimation(const wstring& aniName, CImage* image, float stepTime, UINT count, bool repeat, Vec2 pos, Vec2 scale, Vec2 step)
{
	CAnimation* ani = new CAnimation();
	ani->Create(image, stepTime, count, repeat, pos, scale, step);
	AddAnimation(aniName, ani);
}

void CAnimator::Play(const wstring& aniName, bool reset)
{
	// 현재 애니메이션이 플레이하고자 하는 애니메이션이며
	// reset 아닐 경우 현재 애니메이션을 변경하지 않음
	// reset : 같은 애니메이션을 처음부터 재생
	// (ex. 공격 모션처럼 누를때마다 처음부터 재생해야하는 애니메이션)
	if (playing && aniName == curAnimation->GetKey() && !reset)
		return;

	CAnimation* animation = FindAnimation(aniName);
	assert(nullptr != animation && "Animation no exist");

	// reset 일 경우 처음부터 재생
	if (reset || curAnimation != animation)
	{
		curFrame = 0;
		curTime = 0;
	}
	curAnimation = animation;
}

void CAnimator::Stop()
{
	playing = false;
}

void CAnimator::ComponentInit()
{
}

void CAnimator::ComponentOnEnable()
{
	Component::ComponentOnEnable();
}

void CAnimator::ComponentUpdate()
{
	// 현재 플레이중인 프레임의 누적시간
	curTime += DT;

	// 누적시간이 현재 플레이중인 프레임의 지속시간보다 커졌을 경우
	// -> 다음 프레임을 보여줘야 하는 경우
	if (curAnimation->frames[curFrame].time < curTime)
	{
		curFrame++;	// 현재 플레이중인 프레임의 인덱스를 하나 증가
		curTime = 0;	// 현재 플레이중인 프레임의 누적시간 초기화

		// 만약 플레이중인 프레임이 마지막 프레임이었을 경우
		if (curFrame == curAnimation->frames.size())
		{
			// 반복 애니메이션이라면 처음부터, 아니라면 마지막을 다시 재생
			if (curAnimation->repeat)	curFrame = 0;
			else						curFrame--;
		}
	}
}

void CAnimator::ComponentRender()
{
	Vec2 pos = GetOwner()->GetWorldPos();				// 애니메이션이 그려질 위치 확인
	AniFrame frame = curAnimation->frames[curFrame];	// 애니메이션이 그려질 프레임 확인

	// 프레임 이미지 그리기
	RENDER->FrameImage(
		curAnimation->image,
		pos.x - frame.scale.x * 0.5f * ratio,
		pos.y - frame.scale.y * 0.5f * ratio,
		pos.x + frame.scale.x * 0.5f * ratio,
		pos.y + frame.scale.y * 0.5f * ratio,
		frame.pos.x,
		frame.pos.y,
		frame.pos.x + frame.scale.x,
		frame.pos.y + frame.scale.y
	);
}

void CAnimator::ComponentOnDisable()
{
	Component::ComponentOnDisable();
}

void CAnimator::ComponentRelease()
{
	for (pair<wstring, CAnimation*> animation : animationMap)
	{
		delete animation.second;
	}
	animationMap.clear();
}
