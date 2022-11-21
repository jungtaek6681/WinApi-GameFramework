#pragma once
class CInputManager : public SingleTon<CInputManager>
{
	friend SingleTon<CInputManager>;
private:
	CInputManager();
	virtual ~CInputManager();

	static const UINT VKEY_SIZE = 0xFF;	// VK�� �ִ� ����

public:
	void					Init();
	void					Update();
	void					Release();

	bool					ButtonStay(const int key, bool ignoreUI = false);	// Ű�� ������ �ִ� ��
	bool					ButtonUp(const int key, bool ignoreUI = false);		// Ű�� �ö� ����
	bool					ButtonDown(const int key, bool ignoreUI = false);	// Ű�� ������ ����
	Vec2					MouseScreenPos();									// ���콺 ȭ�� ��ġ
	Vec2					MouseWorldPos();									// ���콺 ���� ��ġ

private:
	HWND					hWnd;

	array<bool, VKEY_SIZE>	prevKeys;						// ���� Ű�� �Է»���
	array<bool, VKEY_SIZE>	curKeys;						// ���� Ű�� �Է»���
	POINT					mousePos;						// ���� ���콺 ��ġ
};

#define	INPUT				CInputManager::GetInstance()
