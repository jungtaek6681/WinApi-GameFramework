#include "pch.h"
#include "CResourceManager.h"

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
}

CImage* CResourceManager::ImageFind(const wstring& key)
{
	auto iter = images.find(key);
	if (iter == images.end())
		return nullptr;
	else
		return iter->second;
}

CImage* CResourceManager::ImageLoad(const wstring& key, const wstring& file)
{
	CImage* pImage = ImageFind(key);
	if (nullptr != pImage)
		return pImage;

	wstring filePath = resourceFolder + file;
	pImage = new CImage;
	pImage->Load(filePath);
	pImage->SetKey(key);
	pImage->SetPath(filePath);
	images.insert(make_pair(key, pImage));

	return pImage;
}

CSound* CResourceManager::SoundFind(const wstring& key)
{
	auto iter = sounds.find(key);
	if (iter == sounds.end())
		return nullptr;
	else
		return iter->second;
}

CSound* CResourceManager::SoundLoad(const wstring& key, const wstring& file)
{
	CSound* pSound = SoundFind(key);
	if (nullptr != pSound)
		return pSound;

	wstring filePath = resourceFolder + file;
	pSound = new CSound;
	pSound->Load(filePath);
	pSound->SetKey(key);
	pSound->SetPath(filePath);
	sounds.insert(make_pair(key, pSound));

	return pSound;
}

void CResourceManager::Init()
{
}

void CResourceManager::Release()
{
	for (pair<wstring, CImage*> image : images)
	{
		delete image.second;
	}
	images.clear();
	for (pair<wstring, CSound*> sound : sounds)
	{
		delete sound.second;
	}
	sounds.clear();
}
