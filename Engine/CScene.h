#pragma once
class CSceneManager;
class CEventManager;
class CGameObject;
class CUI;

class CScene
{
	friend CEventManager;
	friend CSceneManager;
public:
	CScene();
	virtual ~CScene();

public:
	void				AddGameObject(CGameObject* obj);
	void				DeleteGameObject(CGameObject* obj);
	void				DeleteAllObject();

	void				AddRenderer(IRender* renderer);

	void				AddUI(CUI* ui);
	void				DeleteUI(CUI* ui);
	void				DeleteAllUI();

private:
	// 순수가상함수 :
	// 함수를 추상화하여 구체화하지 않을 경우 인스턴스 생성을 막음
	// 씬을 상속받아 순수가상함수들을 구체화시켜 씬을 완성시킴
	virtual void		Init()		= 0;	// 초기화
	virtual void		Enter()		= 0;	// 진입
	virtual void		Update()	= 0;	// 게임로직 갱신
	virtual void		Render()	= 0;	// 게임표현 갱신
	virtual void		Exit()		= 0;	// 탈출
	virtual void		Release()	= 0;	// 마무리

	// 씬 부모 전용 함수들 :
	// 씬에 있는 모든 게임오브젝트들을 갱신
	void				SceneInit();		
	void				SceneEnter();		
	void				SceneUpdate();		
	void				SceneRender();		
	void				SceneExit();		
	void				SceneRelease();		

private:
	list<CGameObject*>						objList;
	list<CUI*>								uiList;
	bool									active;
	priority_queue<pair<float, IRender*>>	renderPQueue;
};

