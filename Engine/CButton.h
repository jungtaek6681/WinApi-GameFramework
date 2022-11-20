#pragma once

// 함수포인터 : 함수를 가리키는 포인터 변수로 함수의 시작주소를 저장하는 변수
// 반환형 (*함수포인터 이름)(매개변수들...)
// ex) void (*FuncPointer)(int);
// 가리키고 있는 함수를 호출하기 위해서는 함수포인터 이름을 통해서 진행
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

	// final : 상속받은 자식클래스에서 재정의하지 못하도록 제한
	void	OnMouseEnter()				final;
	void	OnMouseOver()				final;
	void	OnMouseExit()				final;
	void	OnMouseUp()					final;
	void	OnMouseDown()				final;
	void	OnMouseClicked()			final;

	// delete : 더이상 해당함수를 사용 할수 없도록 제한
	void	AddChildUI(CUI* child)		= delete;
	void	DeleteChildUI(CUI* child)	= delete;

private:
	CallbackFunc	callback;
	DWORD_PTR		param1;
	DWORD_PTR		param2;
};

