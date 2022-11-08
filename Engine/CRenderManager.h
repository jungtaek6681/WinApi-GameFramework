#pragma once
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

private:
	HWND		hWnd;			// 윈도우 핸들
	HDC			hDC;			// 프론트버퍼(결과 게임화면)에 그릴 dc
	HDC			hMemDC;			// 백버퍼(그리는중 게임화면)에 그릴 dc
	HBITMAP		hBMP;			// 백버퍼용 비트맵(이미지)
	Vec2		winSize;		// 윈도우 사이즈
};

#define RENDER		CRenderManager::GetInstance()