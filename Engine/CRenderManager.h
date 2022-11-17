#pragma once

class CImage;

enum class PenType { Solid, Dot, Dash, Null };
enum class BrushType { Solid, Null };
enum class TextAlign { Top, Bottom, Left, Right, Center };
enum class TextBackMode { Solid, Null };

class CRenderManager : public SingleTon<CRenderManager>
{
	friend SingleTon<CRenderManager>;
private:
	CRenderManager();
	virtual ~CRenderManager();

public:
	void		Init();
	void		BeginDraw();
	void		EndDraw();
	void		Release();

	void		Pixel(float x, float y, COLORREF color);						// 픽셀 그리기
	void		Line(float startX, float startY, float endX, float endY);		// 선 그리기
	void		Rect(float startX, float startY, float endX, float endY);		// 사각형 그리기
	void		Circle(float x, float y, float radius);							// 원 그리기
	void		Ellipse(float startX, float startY, float endX, float endY);	// 타원 그리기
	void		Text(float x, float y, wstring str);							// 텍스트 그리기

	void		BitImage(CImage* pImg, float startX, float startY, float endX, float endY);			// 이미지 그리기
	void		StrectchImage(CImage* pImg, float startX, float startY, float endX, float endY);	// 크기변경이미지 그리기
	void		TransparentImage(CImage* pImg, float startX, float startY, float endX, float endY,	// 투명이미지 그리기
								COLORREF transparent = RGB(255, 0, 255));
	void		FrameImage(CImage* pImg,
					float dstStartX, float dstStartY, float dstEndX, float dstEndY,
					float srcStartX, float srcStartY, float srcEndX, float srcEndY,
					COLORREF transparent = RGB(255, 0, 255));		// 이미지 일부분 그리기

	void		SetPen(PenType type = PenType::Solid, COLORREF color = RGB(0, 0, 0), int width = 1);
	void		SetBrush(BrushType type = BrushType::Solid, COLORREF color = RGB(255, 255, 255));
	void		SetText(int size = 10, COLORREF color = RGB(0, 0, 0), TextAlign align = TextAlign::Center);
	void		SetTextBackMode(TextBackMode mode = TextBackMode::Null, COLORREF color = RGB(255, 255, 255));

	HDC			GetMemDC() { return hMemDC; }

private:
	HWND			hWnd;			// 윈도우 핸들
	HDC				hDC;			// 프론트버퍼(결과 게임화면)에 그릴 dc
	HDC				hMemDC;			// 백버퍼(그리는중 게임화면)에 그릴 dc
	HBITMAP			hBMP;			// 백버퍼용 비트맵(이미지)
	Vec2			winSize;		// 윈도우 사이즈

	// 펜
	HPEN			hCurPen;
	PenType			penType;
	int				penWidth;
	COLORREF		penColor;

	// 브러시
	HBRUSH			hCurBrush;
	BrushType		brushType;
	COLORREF		brushColor;

	// 텍스트
	HFONT			hFont;
	int				textSize;
	COLORREF		textColor;
	TextAlign		textAlign;
	TextBackMode	textBackMode;
	COLORREF		textBackColor;
};

#define RENDER		CRenderManager::GetInstance()
#define MAINDC		CRenderManager::GetInstance()->GetMemDC()