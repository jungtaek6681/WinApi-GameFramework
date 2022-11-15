#pragma once
class CMonster : public CGameObject
{
public:
	CMonster();
	virtual ~CMonster();

private:
	void Init()			override;
	void OnEnable()		override;
	void Update()		override;
	void Render()		override;
	void OnDisable()	override;
	void Release()		override;
};

