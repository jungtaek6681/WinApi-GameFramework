#pragma once
class CEngine : public SingleTon<CEngine>
{
	friend SingleTon<CEngine>;
private:
	CEngine();
	virtual ~CEngine();

public:
	void		Init(HINSTANCE hInst, HWND hWnd, Vec2 winSize);
	void		Release();

	HINSTANCE	GetHInst()		{ return hInst; }
	HWND		GetHWnd()		{ return hWnd; }
	Vec2		GetWinSize()	{ return winSize; }

private:
	HINSTANCE	hInst;
	HWND		hWnd;
	Vec2		winSize;
};

