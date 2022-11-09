#pragma once
class CSceneStage01 : public CScene
{
public:
	CSceneStage01();
	virtual ~CSceneStage01();

public:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;

private:
	Vec2			moveDir;
	Vec2			pos;
	Vec2			scale;
};

