#pragma once

class CScene;
class CGameObject;
class CUI;

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
	void Delete(CScene* scene, Component<CGameObject>* obj);						// 오브젝트 삭제 이벤트 추가

	void AddUI(CScene* scene, CUI* ui);												// UI 추가 이벤트 추가
	void AddChild(CUI* parent, CUI* child);											// 자식UI 추가 이벤트 추가
	void Delete(CScene* scene, CUI* ui);											// UI 삭제 이벤트 추가
	void ShowUI(CUI* ui, bool show);												// UI 표시 변경 이벤트 추가

	void ChangeScene(int sceneType, float delay = 0);								// 씬 전환 이벤트 추가

private:
	void ProgressAddGameObject();													// 게임오브젝트 추가 이벤트 진행
	void ProgressAddComponent();													// 컴포넌트 추가 이벤트 진행
	void ProgressDeleteObject();													// 오브젝트 삭제 이벤트 진행

	void ProgressAddUI();															// UI 추가 이벤트 진행
	void ProgressAddChildUI();														// 자식UI 추가 이벤트 진행
	void ProgressDeleteUI();														// UI 삭제 이벤트 진행
	void ProgressShowUI();															// UI 표시 변경 이벤트 진행

	void ProgressChangeScene();														// 씬 전환 이벤트 진행

private:
	queue<pair<CScene*, CGameObject*>>					addGameObjectQueue;			// 게임오브젝트 추가 이벤트 보관
	queue<pair<CGameObject*, Component<CGameObject>*>>	addChildQueue;				// 컴포넌트 추가 이벤트 보관
	queue<pair<CScene*, Component<CGameObject>*>>		deleteObjectQueue;			// 오브젝트 삭제 이벤트 보관

	queue<pair<CScene*, CUI*>>							addUIQueue;					// UI 추가 이벤트 보관
	queue<pair<CUI*, CUI*>>								addChildUIQueue;			// 자식UI 추가 이벤트 보관
	queue<pair<CScene*, CUI*>>							deleteUIQueue;				// UI 삭제 이벤트 보관
	queue<pair<CUI*, bool>>								showUIQueue;				// UI 표시 변경 이벤트 보관

	pair<int, float>*									changeSceneEvent;			// 씬 전환 이벤트 보관 변수
};

#define EVENT		CEventManager::GetInstance()

