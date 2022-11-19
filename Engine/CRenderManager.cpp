#include "pch.h"
#include "CRenderManager.h"

CRenderManager::CRenderManager()
{
	hWnd	= 0;
	hDC		= 0;
	hMemDC	= 0;
	hBMP	= 0;
	winSize	= Vec2(0.f, 0.f);

	hCurPen = 0;
	penType = PenType::Solid;
	penWidth = 1;
	penColor = RGB(0, 0, 0);

	hCurBrush = 0;
	brushType = BrushType::Solid;
	brushColor = RGB(255, 255, 255);

	hFont = 0;
	textSize = 10;
	textColor = RGB(0, 0, 0);
	textAlign = TextAlign::Center;
	textBackMode = TextBackMode::Null;
	textBackColor = RGB(255, 255, 255);
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

	// 기본 펜 & 브러시 설정
	SetPen();
	SetBrush();
	SetText();
	SetTextBackMode();
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

	// 사용했던 펜 & 브러시 삭제
	DeleteObject(hCurPen);
	DeleteObject(hCurBrush);

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
	// WinGDI 사용법
	// 1. 현재펜과 현재브러시를 선택
	// 2. 그리기 작업 진행
	// 3. 이전펜과 이전브러시로 복구
	// Why? 다른 영역에서 사용하다 잠시 빌려쓴 경우를 대비

	HPEN prevPen = static_cast<HPEN>(SelectObject(hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(hMemDC, hCurBrush));

	MoveToEx(hMemDC, (int)startX, (int)startY, NULL);
	LineTo(hMemDC, (int)endX, (int)endY);

	SelectObject(hMemDC, prevPen);
	SelectObject(hMemDC, prevBrush);
}

void CRenderManager::Rect(float startX, float startY, float endX, float endY)
{
	HPEN prevPen = static_cast<HPEN>(SelectObject(hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(hMemDC, hCurBrush));

	Rectangle(hMemDC, (int)startX, (int)startY, (int)endX, (int)endY);

	SelectObject(hMemDC, prevPen);
	SelectObject(hMemDC, prevBrush);
}

void CRenderManager::Circle(float x, float y, float radius)
{
	HPEN prevPen = static_cast<HPEN>(SelectObject(hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(hMemDC, hCurBrush));

	::Ellipse(hMemDC, (int)(x - radius), (int)(y - radius), (int)(x + radius), (int)(y + radius));

	SelectObject(hMemDC, prevPen);
	SelectObject(hMemDC, prevBrush);
}

void CRenderManager::Ellipse(float startX, float startY, float endX, float endY)
{
	HPEN prevPen = static_cast<HPEN>(SelectObject(hMemDC, hCurPen));
	HBRUSH prevBrush = static_cast<HBRUSH>(SelectObject(hMemDC, hCurBrush));

	::Ellipse(hMemDC, (int)startX, (int)startY, (int)endX, (int)endY);

	SelectObject(hMemDC, prevPen);
	SelectObject(hMemDC, prevBrush);
}

void CRenderManager::Text(float x, float y, wstring str)
{
	TextOut(hMemDC, (int)x, (int)y, str.c_str(), (int)str.size());
}

void CRenderManager::BitImage(CImage* pImg, float startX, float startY, float endX, float endY)
{
	BitBlt(hMemDC, (int)startX, (int)startY, (int)endX, (int)endY, pImg->GetImageDC(), 0, 0, SRCCOPY);
}

void CRenderManager::StrectchImage(CImage* pImg, float startX, float startY, float endX, float endY)
{
	StretchBlt(hMemDC, (int)startX, (int)startY, (int)(endX - startX), (int)(endY - startY),
		pImg->GetImageDC(), 0, 0, pImg->GetBmpWidth(), pImg->GetBmpHeight(), SRCCOPY);
}

void CRenderManager::TransparentImage(CImage* pImg, float startX, float startY, float endX, float endY, COLORREF transparent)
{
	TransparentBlt(hMemDC, (int)startX, (int)startY, (int)(endX - startX), (int)(endY - startY),
		pImg->GetImageDC(), 0, 0, pImg->GetBmpWidth(), pImg->GetBmpHeight(), transparent);
}

void CRenderManager::FrameImage(CImage* pImg, float dstStartX, float dstStartY, float dstEndX, float dstEndY, float srcStartX, float srcStartY, float srcEndX, float srcEndY, COLORREF transparent)
{
	TransparentBlt(hMemDC, (int)dstStartX, (int)dstStartY, (int)(dstEndX - dstStartX), (int)(dstEndY - dstStartY),
		pImg->GetImageDC(), (int)srcStartX, (int)srcStartY, (int)(srcEndX - srcStartX), (int)(srcEndY - srcStartY), transparent);
}

void CRenderManager::BlendImage(CImage* pImg, float dstStartX, float dstStartY, float dstEndX, float dstEndY, float srcStartX, float srcStartY, float srcEndX, float srcEndY, float ratio)
{
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = (BYTE)(ratio * 255);

	AlphaBlend(hMemDC, (int)dstStartX, (int)dstStartY, (int)(dstEndX - dstStartX), (int)(dstEndY - dstStartY),
		pImg->GetImageDC(), (int)srcStartX, (int)srcStartY, (int)(srcEndX - srcStartX), (int)(srcEndY - srcStartY), bf);
}

void CRenderManager::SetPen(PenType type, COLORREF color, int width)
{
	// 선택하는 펜이 현재 펜과 동일할 경우 새로 만들지 않음
	if (penType == type && penWidth == width && penColor == color)
		return;

	penType = type;
	penWidth = width;
	penColor = color;

	// 이전 펜을 제거
	DeleteObject(hCurPen);

	// 펜 타입에 따라 펜 스타일을 다르게 설정
	switch (type)
	{
	case PenType::Solid:
		hCurPen = CreatePen(PS_SOLID, width, color);
		break;
	case PenType::Dot:
		hCurPen = CreatePen(PS_DOT, width, color);
		break;
	case PenType::Dash:
		hCurPen = CreatePen(PS_DASH, width, color);
		break;
	case PenType::Null:
		hCurPen = CreatePen(PS_NULL, width, color);
		break;
	default:
		hCurPen = CreatePen(PS_SOLID, width, color);
		break;
	}
}

void CRenderManager::SetBrush(BrushType type, COLORREF color)
{
	// 선택하는 브러시가 현재 브러시와 동일할 경우 새로 만들지 않음
	if (brushType == type && brushColor == color)
		return;

	brushType = type;
	brushColor = color;

	// 이전 브러시를 제거
	DeleteObject(hCurBrush);

	// 브러시 타입에 따라 브러시 스타일을 다르게 설정
	switch (type)
	{
	case BrushType::Solid:
		hCurBrush = CreateSolidBrush(color);
		break;
	case BrushType::Null:
		// Null 브러시만 유독 희안한 구현
		// 컴퓨터는 투명표현이 불가능 -> 특별처리 필요
		hCurBrush = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
		break;
	default:
		hCurBrush = CreateSolidBrush(color);
		break;
	}
}

void CRenderManager::SetText(int size, COLORREF color, TextAlign align)
{
	// 선택하는 텍스트가 현재 텍스트와 동일할 경우 새로 만들지 않음
	if (textSize == size && textColor == color && textAlign == align)
		return;

	textSize = size;
	textColor = color;
	textAlign = align;

	DeleteObject(hFont);
	hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
	SelectObject(hMemDC, hFont);

	SetTextColor(hMemDC, color);

	switch (align)
	{
	case TextAlign::Top:
		SetTextAlign(hMemDC, TA_TOP);
		break;
	case TextAlign::Bottom:
		SetTextAlign(hMemDC, TA_BOTTOM);
		break;
	case TextAlign::Left:
		SetTextAlign(hMemDC, TA_LEFT);
		break;
	case TextAlign::Right:
		SetTextAlign(hMemDC, TA_RIGHT);
		break;
	case TextAlign::Center:
		SetTextAlign(hMemDC, TA_CENTER);
		break;
	default:
		SetTextAlign(hMemDC, TA_TOP);
		break;
	}

}

void CRenderManager::SetTextBackMode(TextBackMode mode, COLORREF backColor)
{
	// 선택하는 텍스트 배경이 현재 텍스트와 동일할 경우 새로 만들지 않음
	if (textBackMode == mode && textBackColor == backColor)
		return;

	switch (mode)
	{
	case TextBackMode::Null:
		SetBkMode(hMemDC, TRANSPARENT);
		break;
	case TextBackMode::Solid:
		SetBkMode(hMemDC, OPAQUE);
		break;
	default:
		SetBkMode(hMemDC, TRANSPARENT);
		break;
	}
}
