#include "pch.h"
#include "CInputManager.h"

CInputManager::CInputManager()
{
	hWnd = 0;

	curKeys.fill(false);
	prevKeys.fill(false);
	mousePos = { 0, 0 };
}

CInputManager::~CInputManager()
{
}

void CInputManager::Init()
{
	hWnd = SINGLE(CEngine)->GetHWnd();
}

void CInputManager::Update()
{
	// 현재 선택(Focus)된 윈도우가 게임 윈도우인가를 확인
	if (hWnd != GetFocus())
	{
		// 윈도우가 선택(Focus)된 상태가 아닐 경우 키입력을 해제시킴
		for (int key = 0; key < VKEY_SIZE; key++)
		{
			prevKeys[key] = curKeys[key];
			curKeys[key] = false;
		}
		return;
	}

	// 모든 키 사이즈만큼 반복하며 입력상태를 확인
	for (int key = 0; key < VKEY_SIZE; key++)
	{
		prevKeys[key] = curKeys[key];
		if (GetAsyncKeyState(key) & 0x8000)
		{
			curKeys[key] = true;
		}
		else
		{
			curKeys[key] = false;
		}
	}

	// GetCursorPos() 윈도우에서 모니터 좌상단 기준 마우스의 좌표를 반환
	GetCursorPos(&mousePos);
	// 모니터 좌상단 기준 마우스 좌표를 게임 윈도우 기준 마우스 위치로 계산
	ScreenToClient(hWnd, &mousePos);
}

void CInputManager::Release()
{
}

bool CInputManager::ButtonStay(const int key)
{
	// 키가 눌리고 있는 중
	return prevKeys[key] == true && curKeys[key] == true;
}

bool CInputManager::ButtonUp(const int key)
{
	// 키가 올라간 순간
	return prevKeys[key] == true && curKeys[key] == false;
}

bool CInputManager::ButtonDown(const int key)
{
	// 키가 내려간 순간
	return prevKeys[key] == false && curKeys[key] == true;
}

Vec2 CInputManager::MousePos()
{
	return Vec2((float)mousePos.x, (float)mousePos.y);
}
