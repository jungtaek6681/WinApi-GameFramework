#pragma once
class CSceneTitle : public CScene
{
public:
	CSceneTitle();
	virtual ~CSceneTitle();

public:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};

