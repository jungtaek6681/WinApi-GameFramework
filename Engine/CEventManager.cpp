#include "pch.h"
#include "CEventManager.h"

CEventManager::CEventManager()
{
}

CEventManager::~CEventManager()
{
}

void CEventManager::Init()
{
}

void CEventManager::Update()
{
	ProgressAddGameObject();
	ProgressDeleteGameObject();
	ProgressAddComponent();
	ProgressChangeScene();
}

void CEventManager::Release()
{
}

void CEventManager::AddGameObject(CScene* scene, CGameObject* obj)
{
	addGameObjectQueue.push(make_pair(scene, obj));
}

void CEventManager::AddChild(CGameObject* parent, Component<CGameObject>* child)
{
	addChildQueue.push(make_pair(parent, child));
}

void CEventManager::DeleteGameObject(CScene* scene, CGameObject* obj)
{
	deleteGameObjectQueue.push(make_pair(scene, obj));
}

void CEventManager::ChangeScene(int sceneType)
{
	changeSceneValue = sceneType;
}

void CEventManager::ProgressAddGameObject()
{
	while (!addGameObjectQueue.empty())
	{
		CScene* scene = addGameObjectQueue.front().first;
		CGameObject* obj = addGameObjectQueue.front().second;
		addGameObjectQueue.pop();
		scene->AddGameObject(obj);
	}
}

void CEventManager::ProgressAddComponent()
{
	while (!addChildQueue.empty())
	{
		CGameObject* parent = addChildQueue.front().first;
		Component<CGameObject>* child = addChildQueue.front().second;
		addChildQueue.pop();
		parent->AddChild(child);
	}
}

void CEventManager::ProgressDeleteGameObject()
{
	// 삭제 예정 표시된 게임오브젝트를 삭제 진행
	CScene* curScene = SINGLE(CSceneManager)->GetCurScene();
	list<CGameObject*>& objList = curScene->objList;

	objList.remove_if([&](CGameObject* obj) {
		if (obj->IsReservedDelete())
		{
			if (curScene->active) obj->OnDisable();
			obj->Release();
			obj->SetScene(nullptr);
			delete obj;
			return true;
		}
		else
		{
			return false;
		}
		});

	// 삭제 예정인 게임오브젝트에 삭제예정 표시를 진행
	while (!deleteGameObjectQueue.empty())
	{
		CScene* scene = deleteGameObjectQueue.front().first;
		CGameObject* obj = deleteGameObjectQueue.front().second;
		deleteGameObjectQueue.pop();
		obj->SetReservedDelete();
	}
}

void CEventManager::ProgressChangeScene()
{
	// 씬 전환 이벤트가 있는 경우 씬 전환 진행
	if (changeSceneValue != -1)
	{
		SINGLE(CSceneManager)->ChangeScene(changeSceneValue);
		changeSceneValue = -1;
	}
}
