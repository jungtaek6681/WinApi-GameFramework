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

	void	ComponentUpdate()	override;

	// final : ��ӹ��� �ڽ�Ŭ�������� ���������� ���ϵ��� ����
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

