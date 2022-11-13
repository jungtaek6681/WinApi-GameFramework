#include "pch.h"
#include "CScene.h"

CScene::CScene()
{
	active = false;
}

CScene::~CScene()
{
}

void CScene::AddGameObject(CGameObject* obj)
{
	objList.push_back(obj);
	obj->SetScene(this);
	obj->Init();
	if (active) obj->OnEnable();
}

void CScene::DeleteGameObject(CGameObject* obj)
{
	if (active) obj->OnDisable();
	obj->Release();
	obj->SetScene(nullptr);
	objList.remove(obj);
	delete obj;
}

void CScene::DeleteAllObject()
{
	for (CGameObject* obj : objList)
	{
		if (active) obj->OnDisable();
		obj->Release();
		objList.remove(obj);
		delete obj;
	}
}

void CScene::SceneInit()
{
	Init();
}

void CScene::SceneEnter()
{
	Enter();
	active = true;
	for (CGameObject* obj : objList)
	{
		obj->OnEnable();
	}
}

void CScene::SceneUpdate()
{
	Update();

	for (CGameObject* obj : objList)
	{
		obj->Update();
	}
}

void CScene::SceneRender()
{
	for (CGameObject* obj : objList)
	{
		obj->Render();
	}

	Render();
}

void CScene::SceneExit()
{
	for (CGameObject* obj : objList)
	{
		obj->OnDisable();
	}
	active = false;
	Exit();
}

void CScene::SceneRelease()
{
	for (CGameObject* obj : objList)
	{
		obj->Release();
		delete obj;
	}
	objList.clear();

	Release();
}
