#pragma once
class CInputManager : public SingleTon<CInputManager>
{
	friend SingleTon<CInputManager>;
private:
	CInputManager();
	virtual ~CInputManager();

	static const UINT VKEY_SIZE = 0xFF;	// VK의 최대 갯수

public:
	void					Init();
	void					Update();
	void					Release();

	bool					ButtonStay(const int key);	// 키를 누르고 있는 중
	bool					ButtonUp(const int key);	// 키가 올라간 순간
	bool					ButtonDown(const int key);	// 키가 내려간 순간
	Vec2					MousePos();					// 현재 마우스 위치

private:
	HWND					hWnd;

	array<bool, VKEY_SIZE>	prevKeys;					// 이전 키의 입력상태
	array<bool, VKEY_SIZE>	curKeys;					// 현재 키의 입력상태
	POINT					mousePos;					// 현재 마우스 위치
};

#define	INPUT				CInputManager::GetInstance()
