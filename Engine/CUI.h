#pragma once

class CScene;

class CUI : Composite<CUI>
{
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
	wstring			name;
	Vec2			pos;
	Vec2			worldPos;
	Vec2			renderPos;
	Vec2			scale;
	bool			screenFixed;
	bool			show;

private:
	void			ComponentInit()			override;
	void			ComponentOnEnable()		override;
	void			ComponentUpdate()		override;
	void			ComponentRender()		override;
	void			ComponentOnDisable()	override;
	void			ComponentRelease()		override;
};

