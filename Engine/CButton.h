#pragma once

// �Լ������� : �Լ��� ����Ű�� ������ ������ �Լ��� �����ּҸ� �����ϴ� ����
// ��ȯ�� (*�Լ������� �̸�)(�Ű�������...)
// ex) void (*FuncPointer)(int);
// ����Ű�� �ִ� �Լ��� ȣ���ϱ� ���ؼ��� �Լ������� �̸��� ���ؼ� ����
// ex) FuncPointer(10);
typedef void(*CallbackFunc)(DWORD_PTR, DWORD_PTR);

class CButton : public CUI
{
public:
	CButton();
	virtual ~CButton();

public:
	void	SetClickCallback(CallbackFunc callback, DWORD_PTR param1, DWORD_PTR param2);

private:
	void	Init()						override;
	void	OnEnable()					override;
	void	Update()					override;
	void	Render()					override;
	void	OnDisable()					override;
	void	Release()					override;

	// final : ��ӹ��� �ڽ�Ŭ�������� ���������� ���ϵ��� ����
	void	OnMouseEnter()				final;
	void	OnMouseOver()				final;
	void	OnMouseExit()				final;
	void	OnMouseUp()					final;
	void	OnMouseDown()				final;
	void	OnMouseClicked()			final;

	// delete : ���̻� �ش��Լ��� ��� �Ҽ� ������ ����
	void	AddChildUI(CUI* child)		= delete;
	void	DeleteChildUI(CUI* child)	= delete;

private:
	CallbackFunc	callback;
	DWORD_PTR		param1;
	DWORD_PTR		param2;
};

