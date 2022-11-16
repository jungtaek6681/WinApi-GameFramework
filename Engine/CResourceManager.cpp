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
}
