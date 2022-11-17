#pragma once
class CCameraController : public CGameObject
{
public:
	CCameraController();
	virtual ~CCameraController();

private:
	void Init()			override;
	void OnEnable()		override;
	void Update()		override;
	void Render()		override;
	void OnDisable()	override;
	void Release()		override;
};

