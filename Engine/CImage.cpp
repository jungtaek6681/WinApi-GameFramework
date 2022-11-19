#include "pch.h"
#include "CImage.h"

CImage::CImage()
{
	hDC = 0;
	hBmp = 0;
	bmpInfo = {};
}

CImage::~CImage()
{
	DeleteDC(hDC);
	DeleteObject(hBmp);
}

void CImage::Load(const wstring path)
{
	hBmp = (HBITMAP)LoadImage(
		nullptr,								// hInstance. nullptr로 해도 됨.
		path.c_str(),							// 파일 경로를 C style 문자열로 변환
		IMAGE_BITMAP,							// 이미지 타입, 비트맵 이미지로 지정
		0, 0,									// 이미지의 X, Y 크기, 0을 주면 이미지 크기로 설정
		LR_CREATEDIBSECTION | LR_LOADFROMFILE	// 이미지 로딩 타입.
	);

	assert(hBmp && "Image Load Failed");		// 이미지가 없다면 assert를 통한 종료

	hDC = CreateCompatibleDC(MAINDC);			// 비트맵이미지와 연결할 DC 생성
	SelectObject(hDC, hBmp);					// 비트맵이미지와 DC 연결
	GetObject(hBmp, sizeof(BITMAP), &bmpInfo);	// 비트맵이미지 정보 추출
}

void CImage::Create(UINT sizeX, UINT sizeY)
{
	hBmp = CreateCompatibleBitmap(MAINDC, sizeX, sizeY);
	hDC = CreateCompatibleDC(MAINDC);

	HBITMAP hOldBmp = (HBITMAP)SelectObject(hDC, hBmp);
	DeleteObject(hOldBmp);

	GetObject(hBmp, sizeof(BITMAP), &bmpInfo);
}
