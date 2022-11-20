#pragma once

class CUIManager;
class CEventManager;
class CScene;

class CUI : public Composite<CUI>
{
	friend CUIManager;
	friend CEventManager;
	friend CScene;
public:
	CUI();
	virtual ~CUI();

public:
	const wstring&	GetName()						{ return name; }
	const Vec2&		GetPos()						{ return pos; }
	const Vec2&		GetWorldPos()					{ return worldPos; }
	const Vec2&		GetRenderPos()					{ return renderPos; }
	const Vec2&		GetScale()						{ return scale; }
	bool			IsScreenFixed()					{ return (owner == nullptr) ? screenFixed : owner->IsScreenFixed(); }
	bool			IsShow()						{ return show; }

	void			SetName(const wstring& name)	{ this->name = name; }
	void			SetPos(const Vec2& pos)			{ this->pos = pos; }
	void			SetScale(const Vec2& scale)		{ this->scale = scale; }
	void			SetScreenFixed(bool fixed)		{ this->screenFixed = fixed; }
	void			SetShow(bool show)				{ this->show = show; }

protected:
	bool			IsMouseOn();

	wstring			name;
	Vec2			pos;
	Vec2			worldPos;
	Vec2			renderPos;
	Vec2			scale;
	bool			screenFixed;
	bool			show;

protected:
	void			ComponentInit()			override;
	void			ComponentOnEnable()		override;
	void			ComponentUpdate()		override;
	void			ComponentRender()		override;
	void			ComponentOnDisable()	override;
	void			ComponentRelease()		override;

private:
	virtual void	Init()					= 0;
	virtual void	OnEnable()				= 0;
	virtual void	Update()				= 0;
	virtual void	Render()				= 0;
	virtual void	OnDisable()				= 0;
	virtual void	Release()				= 0;

	virtual void	OnMouseEnter()			{}
	virtual void	OnMouseOver()			{}
	virtual void	OnMouseExit()			{}
	virtual void	OnMouseUp()				{}
	virtual void	OnMouseDown()			{}
	virtual void	OnMouseClicked()		{}

	bool			prevMouseOn;			// UI가 이전 프레임에 마우스가 올려진 여부
	bool			prevDown;				// UI가 이전 프레임에 눌렸는지 여부
};

