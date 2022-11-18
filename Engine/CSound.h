#pragma once
#include "CResource.h"
class CSound : public CResource
{
public:
	CSound();
	virtual ~CSound();

public:
	void Load(const wstring& path);

	FMOD::Sound* GetSound() { return sound; }

private:
	FMOD::Sound* sound;
};

