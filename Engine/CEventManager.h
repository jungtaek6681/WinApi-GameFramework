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

	void AddGameObject(CScene* scene, CGameObject* obj);							// 게임오브젝트 추가 이벤트 추가
	void AddChild(CGameObject* parent, Component<CGameObject>* child);				// 컴포넌트 추가 이벤트 추가
	void DeleteObject(CScene* scene, Component<CGameObject>* obj);					// 오브젝트 삭제 이벤트 추가
	void ChangeScene(int sceneType);												// 씬 전환 이벤트 추가

private:
	void ProgressAddGameObject();													// 게임오브젝트 추가 이벤트 진행
	void ProgressAddComponent();													// 컴포넌트 추가 이벤트 진행
	void ProgressDeleteObject();													// 오브젝트 삭제 이벤트 진행
	void ProgressChangeScene();														// 씬 전환 이벤트 진행

private:
	queue<pair<CScene*, CGameObject*>>					addGameObjectQueue;			// 게임오브젝트 추가 이벤트 보관
	queue<pair<CGameObject*, Component<CGameObject>*>>	addChildQueue;				// 컴포넌트 추가 이벤트 보관
	queue<pair<CScene*, Component<CGameObject>*>>		deleteObjectQueue;			// 오브젝트 삭제 이벤트 보관
	int													changeSceneValue = -1;		// 씬 전환 이벤트 보관 변수
};

#define EVENT		CEventManager::GetInstance()

