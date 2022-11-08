#include "pch.h"
#include "CEngine.h"

CEngine::CEngine()
{
	hInst		= 0;
	hWnd		= 0;
	winSize		= Vec2(0, 0);
}

CEngine::~CEngine()
{
}

void CEngine::Init(HINSTANCE hInst, HWND hWnd, Vec2 winSize)
{
	this->hInst		= hInst;
	this->hWnd		= hWnd;
	this->winSize	= winSize;
}

void CEngine::Release()
{
}
