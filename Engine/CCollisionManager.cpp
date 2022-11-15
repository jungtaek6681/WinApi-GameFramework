#include "pch.h"
#include "CCollisionManager.h"

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Init()
{
}

void CCollisionManager::Update()
{
	// 충돌 판정 진행
}

void CCollisionManager::Release()
{
}

void CCollisionManager::AddCollider(CCollider* collider)
{
	colliderList.push_back(collider);
}

void CCollisionManager::RemoveCollider(CCollider* collider)
{
	colliderList.remove(collider);
}
