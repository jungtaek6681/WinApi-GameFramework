#include "pch.h"
#include "CSound.h"

CSound::CSound()
{
	sound = nullptr;
}

CSound::~CSound()
{
	if (nullptr != sound)
		sound->release();
}

void CSound::Load(const wstring& path)
{
}
