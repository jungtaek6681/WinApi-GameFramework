#pragma once
class CPanel : public CUI
{
public:
	CPanel();
	virtual ~CPanel();

public:
	bool	IsDraggable()					{ return draggable; }
	void	SetDraggable(bool draggable)	{ this->draggable = draggable; }

private:
	void	Init()				override;
	void	OnEnable()			override;
	void	Update()			override;
	void	Render()			override;
	void	OnDisable()			override;
	void	Release()			override;

	// final : 상속받은 자식클래스에서 재정의하지 못하도록 제한
	void	OnMouseEnter()		final;
	void	OnMouseOver()		final;
	void	OnMouseExit()		final;
	void	OnMouseUp()			final;
	void	OnMouseDown()		final;
	void	OnMouseClicked()	final;

	Vec2	dragStartPos;
	bool	isDragging;
	bool	draggable;
};

