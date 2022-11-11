#pragma once
class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void	Init()			override;
	void	OnEnable()		override;
	void	Update()		override;
	void	Render()		override;
	void	OnDisable()		override;
	void	Release()		override;

private:
	float	speed;
};

