#pragma once
class CGame
{
public:
	CGame();
	virtual ~CGame();

public:
	static const Vec2		WINSTART;
	static const Vec2		WINSIZE;
	static const DWORD		WINSTYLE = WS_SYSMENU | WS_MINIMIZEBOX;

public:
	void			Init(HINSTANCE hInstance);
	void			Run();
	void			Release();

private:
	void			Input();
	void			Update();
	void			Render();

private:
	HINSTANCE		hInst;
	HWND			hWnd;

	Vec2			moveDir;
	Vec2			pos;
	Vec2			scale;
};
