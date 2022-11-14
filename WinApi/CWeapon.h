#pragma once
class CWeapon : public CGameObject
{
public:
	CWeapon();
	virtual ~CWeapon();

private:
	void	Init()			override;
	void	OnEnable()		override;
	void	Update()		override;
	void	Render()		override;
	void	OnDisable()		override;
	void	Release()		override;

private:
	void	CreateMissile();
};

