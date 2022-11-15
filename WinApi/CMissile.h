#pragma once
class CMissile : public CGameObject
{
public:
	CMissile();
	virtual ~CMissile();

public:
	void	SetDir(const Vec2 dir)	{ this->dir = dir.Normalized(); }

private:
	void	Init()					override;
	void	OnEnable()				override;
	void	Update()				override;
	void	Render()				override;
	void	OnDisable()				override;
	void	Release()				override;

	void	OnCollisionEnter(CCollider* other)	override;

private:
	Vec2	dir;
	float	speed;
};
