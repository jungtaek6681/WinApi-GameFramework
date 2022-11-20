#pragma once
class CSoundController : public CGameObject
{
public:
	CSoundController();
	virtual ~CSoundController();

private:
	void Init()			override;
	void OnEnable()		override;
	void Update()		override;
	void Render()		override;
	void OnDisable()	override;
	void Release()		override;

private:
	CSound* soundOnce;
	CSound* soundLoop;
};

