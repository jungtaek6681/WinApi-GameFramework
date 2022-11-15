#pragma once
#include "CResource.h"
class CImage : public CResource
{
public:
	CImage();
	virtual ~CImage();

public:
	void	Load(const wstring path);

	HDC		GetImageDC()	{ return hDC; }
	BITMAP	GetBmpInfo()	{ return bmpInfo; }
	UINT	GetBmpWidth()	{ return bmpInfo.bmWidth; }
	UINT	GetBmpHeight()	{ return bmpInfo.bmHeight; }

private:
	HDC		hDC;
	HBITMAP	hBmp;
	BITMAP	bmpInfo;
};

