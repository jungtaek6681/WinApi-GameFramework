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

bool CInputManager::GetButtonStay(const int key)
{
	// Ű�� ������ �ִ� ��
	return prevKeys[key] == true && curKeys[key] == true;
}

bool CInputManager::GetButtonUp(const int key)
{
	// Ű�� �ö� ����
	return prevKeys[key] == true && curKeys[key] == false;
}

bool CInputManager::GetButtonDown(const int key)
{
	// Ű�� ������ ����
	return prevKeys[key] == false && curKeys[key] == true;
}

Vec2 CInputManager::GetMousePos()
{
	return Vec2((float)mousePos.x, (float)mousePos.y);
}