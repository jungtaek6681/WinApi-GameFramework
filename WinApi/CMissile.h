#pragma once
class CMissile : public CGameObject
{
public:
	CMissile();
	virtual ~CMissile();

private:
	void	Init()				override;
	void	OnEnable()			override;
	void	Update()			override;
	void	Render()			override;
	void	OnDisable()			override;
	void	Release()			override;

	void	OnCollisionStay(CCollider* other)	override;

private:
	Vec2	dir;
	float	speed;
};
