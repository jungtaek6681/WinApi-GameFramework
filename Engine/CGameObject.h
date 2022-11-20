#pragma once
class CEventManager;
class CScene;

class CGameObject : public Composite<CGameObject>, public IRender
{
	friend CEventManager;
	friend CScene;
	friend CCollider;
public:
	CGameObject();
	virtual ~CGameObject();

public:
	const wstring&	GetName()						{ return name; }
	const Vec2&		GetPos()						{ return pos; }
	const Vec2&		GetWorldPos()					{ return worldPos; }
	const Vec2&		GetScale()						{ return scale; }

	void			SetName(const wstring& name)	{ this->name = name; }
	void			SetPos(const Vec2& pos)			{ this->pos = pos; }
	void			SetScale(const Vec2& scale)		{ this->scale = scale; }

protected:
	wstring			name;
	Vec2			pos;
	Vec2			worldPos;
	Vec2			scale;
	// float		zOrder;

private:
	virtual void	Init()		= 0;
	virtual void	OnEnable()	= 0;
	virtual void	Update()	= 0;
	//virtual void	Render()	= 0;
	virtual void	OnDisable()	= 0;
	virtual void	Release()	= 0;

	void			ComponentInit()			override;
	void			ComponentOnEnable()		override;
	void			ComponentUpdate()		override;
	void			ComponentRender()		override;
	void			ComponentOnDisable()	override;
	void			ComponentRelease()		override;

	virtual void	OnCollisionStay(CCollider* other) {};	
};

