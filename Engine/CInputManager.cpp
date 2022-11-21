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
	// ���� ����(Focus)�� �����찡 ���� �������ΰ��� Ȯ��
	if (hWnd != GetFocus())
	{
		// �����찡 ����(Focus)�� ���°� �ƴ� ��� Ű�Է��� ������Ŵ
		for (int key = 0; key < VKEY_SIZE; key++)
		{
			prevKeys[key] = curKeys[key];
			curKeys[key] = false;
		}
		return;
	}

	// ��� Ű �����ŭ �ݺ��ϸ� �Է»��¸� Ȯ��
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

	// GetCursorPos() �����쿡�� ����� �»�� ���� ���콺�� ��ǥ�� ��ȯ
	GetCursorPos(&mousePos);
	// ����� �»�� ���� ���콺 ��ǥ�� ���� ������ ���� ���콺 ��ġ�� ���
	ScreenToClient(hWnd, &mousePos);
}

void CInputManager::Release()
{
}

bool CInputManager::ButtonStay(const int key, bool ignoreUI)
{
	if (SINGLE(CUIManager)->GetFocusedUI() != nullptr && !ignoreUI)
		return false;

	// Ű�� ������ �ִ� ��
	return prevKeys[key] == true && curKeys[key] == true;
}

bool CInputManager::ButtonUp(const int key, bool ignoreUI)
{
	if (SINGLE(CUIManager)->GetFocusedUI() != nullptr && !ignoreUI)
		return false;

	// Ű�� �ö� ����
	return prevKeys[key] == true && curKeys[key] == false;
}

bool CInputManager::ButtonDown(const int key, bool ignoreUI)
{
	if (SINGLE(CUIManager)->GetFocusedUI() != nullptr && !ignoreUI)
		return false;

	// Ű�� ������ ����
	return prevKeys[key] == false && curKeys[key] == true;
}

Vec2 CInputManager::MouseScreenPos()
{
	return Vec2((float)mousePos.x, (float)mousePos.y);
}

Vec2 CInputManager::MouseWorldPos()
{
	return CAMERA->ScreenToWorldPoint(Vec2((float)mousePos.x, (float)mousePos.y));
}

