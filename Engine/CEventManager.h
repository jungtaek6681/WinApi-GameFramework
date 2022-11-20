#pragma once

class CScene;
class CGameObject;

class CEventManager : public SingleTon<CEventManager>
{
	friend SingleTon<CEventManager>;
private:
	CEventManager();
	virtual ~CEventManager();

public:
	void Init();
	void Update();
	void Release();

	void AddGameObject(CScene* scene, CGameObject* obj);		// 게임오브젝트 추가 이벤트

private:
	void ProgressAddGameObject();								// 게임오브젝트 추가 진행

private:
	queue<pair<CScene*, CGameObject*>> addGameObjectQueue;		// 게임오브젝트 추가 이벤트 보관
};

#define EVENT		CEventManager::GetInstance()

