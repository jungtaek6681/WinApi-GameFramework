#pragma once
class CEventManager;
class CScene;

class CGameObject : public Composite<CGameObject>
{
	friend CEventManager;
	friend CScene;
public:
	CGameObject();
	virtual ~CGameObject();

public:
	CScene*			GetScene()						{ return scene; }
	const wstring&	GetName()						{ return name; }
	const Vec2&		GetPos()						{ return pos; }
	const Vec2&		GetScale()						{ return scale; }

	void			SetScene(CScene* scene)			{ this->scene = scene; }
	void			SetName(const wstring& name)	{ this->name = name; }
	void			SetPos(const Vec2& pos)			{ this->pos = pos; }
	void			SetScale(const Vec2& scale)		{ this->scale = scale; }

	bool			IsReservedDelete()				{ return reservedDelete; }

protected:
	CScene*			scene;
	wstring			name;
	Vec2			pos;
	Vec2			scale;

private:
	virtual void	Init()		= 0;
	virtual void	OnEnable()	= 0;
	virtual void	Update()	= 0;
	virtual void	Render()	= 0;
	virtual void	OnDisable()	= 0;
	virtual void	Release()	= 0;

	void			ComponentInit()			override;
	void			ComponentOnEnable()		override;
	void			ComponentUpdate()		override;
	void			ComponentRender()		override;
	void			ComponentOnDisable()	override;
	void			ComponentRelease()		override;

	void			SetReservedDelete()		{ reservedDelete = true; }	// 게임오브젝트 삭제 예약

	bool			reservedDelete;										// 게임오브젝트가 삭제예정인지 여부
};

