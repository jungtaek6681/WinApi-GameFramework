#include "pch.h"
#include "CRenderManager.h"

CRenderManager::CRenderManager()
{
	hWnd	= 0;
	hDC		= 0;
	hMemDC	= 0;
	hBMP	= 0;
	winSize	= Vec2(0.f, 0.f);
}

CRenderManager::~CRenderManager()
{
}

void CRenderManager::Init()
{
	hWnd	= SINGLE(CEngine)->GetHWnd();
	winSize = SINGLE(CEngine)->GetWinSize();
	hDC		= GetDC(SINGLE(CEngine)->GetHWnd());

	// <더블 버퍼링>
	// 현재 게임화면에 직접 그릴경우 그리는 과정이 포착되어
	// 반짝거리는 블링크 현상 발생
	// 백버퍼에 그리는 작업을 진행하고 모두 그렸을 경우
	// 브론트버퍼에 결과물을 복사해주는 방식으로 블링크 현상을 해결

	// 더블 버퍼링의 메모리 DC와 비트맵 생성
	hMemDC = CreateCompatibleDC(hDC);
	hBMP = CreateCompatibleBitmap(hDC, (int)winSize.x, (int)winSize.y);

	HBITMAP hOldBitmap = static_cast<HBITMAP>(SelectObject(hMemDC, hBMP));
	DeleteObject(hOldBitmap);
}

void CRenderManager::BeginDraw()
{
	// 백버퍼를 모두 흰색으로 초기화
	PatBlt(hMemDC, 0, 0, (int)winSize.x, (int)winSize.y, WHITENESS);
}

void CRenderManager::EndDraw()
{
	// 백버퍼를 프론트버퍼로 복사
	BitBlt(hDC, 0, 0, (int)winSize.x, (int)winSize.y, hMemDC, 0, 0, SRCCOPY);
}

void CRenderManager::Release()
{
	// 사용했던 프론트버퍼와 백버퍼 삭제
	DeleteObject(hMemDC);
	DeleteObject(hBMP);
	ReleaseDC(hWnd, hDC);

	hDC = 0;
	hMemDC = 0;
	hBMP = 0;
}

void CRenderManager::Pixel(float x, float y, COLORREF color)
{
	SetPixel(hMemDC, (int)x, (int)y, color);
}

void CRenderManager::Line(float startX, float startY, float endX, float endY)
{
	MoveToEx(hMemDC, (int)startX, (int)startY, NULL);
	LineTo(hMemDC, (int)endX, (int)endY);
}

void CRenderManager::Rect(float startX, float startY, float endX, float endY)
{
	Rectangle(hMemDC, (int)startX, (int)startY, (int)endX, (int)endY);
}

void CRenderManager::Circle(float x, float y, float radius)
{
	::Ellipse(hMemDC, (int)(x - radius), (int)(y - radius), (int)(x + radius), (int)(y + radius));
}

void CRenderManager::Ellipse(float startX, float startY, float endX, float endY)
{
	::Ellipse(hMemDC, (int)startX, (int)startY, (int)endX, (int)endY);
}

void CRenderManager::Text(float x, float y, wstring str)
{
	TextOut(hMemDC, (int)x, (int)y, str.c_str(), (int)str.size());
}