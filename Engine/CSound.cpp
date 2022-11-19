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
	char str[255];
	wcstombs_s(nullptr, str, path.c_str(), 255);

	FMOD_RESULT result = SOUND->GetSystem()->createSound(str, FMOD_LOOP_OFF, 0, &sound);
	assert(FMOD_OK == result && "System createSound failed");
}
