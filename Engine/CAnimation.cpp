#include "pch.h"
#include "CAnimation.h"

CAnimation::CAnimation()
{
	image	= nullptr;
	repeat	= false;
}

CAnimation::~CAnimation()
{
}

void CAnimation::Create(CImage* image, float stepTime, UINT count, bool repeat, Vec2 pos, Vec2 scale, Vec2 step)
{
	this->image = image;
	this->repeat = repeat;

	AniFrame frame;
	for (UINT i = 0; i < count; i++)
	{
		frame.pos = pos + step * i;
		frame.scale = scale;
		frame.time = stepTime;

		frames.push_back(frame);
	}
}
