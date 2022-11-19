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
	obj->ComponentInit();
	if (active) obj->ComponentOnEnable();
}

void CScene::DeleteGameObject(CGameObject* obj)
{
	if (active) obj->ComponentOnDisable();
	obj->ComponentRelease();
	obj->SetScene(nullptr);
	objList.remove(obj);
	delete obj;
}

void CScene::DeleteAllObject()
{
	for (CGameObject* obj : objList)
	{
		if (active) obj->ComponentOnDisable();
		obj->ComponentRelease();
		objList.remove(obj);
		delete obj;
	}
}

void CScene::AddRenderer(IRender* renderer)
{
	renderPQueue.push(make_pair(renderer->zOrder, renderer));
}

void CScene::AddUI(CUI* ui)
{
	uiList.push_back(ui);
	ui->SetScene(this);
	ui->ComponentInit();
	if (active) ui->ComponentOnEnable();
}

void CScene::DeleteUI(CUI* ui)
{
	if (active) ui->ComponentOnDisable();
	ui->ComponentRelease();
	ui->SetScene(nullptr);
	uiList.remove(ui);
	delete ui;
}

void CScene::DeleteAllUI()
{
	for (CUI* ui : uiList)
	{
		if (active) ui->ComponentOnDisable();
		ui->ComponentRelease();
		ui->SetScene(nullptr);
		uiList.remove(ui);
		delete ui;
	}
}

void CScene::SceneInit()
{
	Init();
}

void CScene::SceneEnter()
{
	// 이전 씬의 카메라 상황을 초기화하고 카메라의 위치를 초기 위치로
	// 씬의 카메라 시작위치가 초기 위치가 아닌경우 씬의 Enter에서 위치를 설정하여 목표위치가 덮어씀
	CAMERA->SetTargetObj(nullptr);
	CAMERA->SetTargetPos(SINGLE(CEngine)->GetWinSize() * 0.5f);
	CAMERA->FadeIn(0.5f);
	Enter();

	active = true;
	for (CGameObject* obj : objList)
	{
		obj->ComponentOnEnable();
	}
	for (CUI* ui : uiList)
	{
		ui->ComponentOnEnable();
	}
}

void CScene::SceneUpdate()
{
	Update();

	for (CGameObject* obj : objList)
	{
		obj->ComponentUpdate();
	}
	for (CUI* ui : uiList)
	{
		ui->ComponentUpdate();
	}
}

void CScene::SceneRender()
{
	for (CGameObject* obj : objList)
	{
		obj->ComponentRender();
	}

	while (!renderPQueue.empty())
	{
		pair<float, IRender*> top = renderPQueue.top();
		renderPQueue.pop();
		top.second->Render();
	}

	for (CUI* ui : uiList)
	{
		ui->ComponentRender();
	}

	Render();
}

void CScene::SceneExit()
{
	for (CGameObject* obj : objList)
	{
		obj->ComponentOnDisable();
	}
	for (CUI* ui : uiList)
	{
		ui->ComponentOnDisable();
	}
	active = false;
	Exit();
}

void CScene::SceneRelease()
{
	for (CGameObject* obj : objList)
	{
		obj->ComponentRelease();
		delete obj;
	}
	objList.clear();
	for (CUI* ui : uiList)
	{
		ui->ComponentRelease();
		delete ui;
	}
	uiList.clear();

	Release();
}
