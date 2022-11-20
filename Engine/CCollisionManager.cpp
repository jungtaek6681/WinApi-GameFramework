#include "pch.h"
#include "CCollisionManager.h"

CCollisionManager::CCollisionManager()
{
	ResetCheck();
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Init()
{
}

void CCollisionManager::Update()
{
	for (UINT left = 0; left < MAXLAYER; left++)
	{
		for (UINT right = left; right < MAXLAYER; right++)
		{
			if (layerMask[left][right])
			{
				CollisionUpdate(left, right);
			}
		}
	}
}

void CCollisionManager::Release()
{
}

void CCollisionManager::AddCollider(CCollider* collider)
{
	colliderList[collider->GetLayer()].push_back(collider);
}

void CCollisionManager::RemoveCollider(CCollider* collider)
{
	colliderList[collider->GetLayer()].remove(collider);
}

void CCollisionManager::CheckLayer(UINT left, UINT right)
{
	layerMask[left][right] = true;
	layerMask[right][left] = true;
}

void CCollisionManager::UnCheckLayer(UINT left, UINT right)
{
	layerMask[left][right] = false;
	layerMask[right][left] = false;
}

void CCollisionManager::ResetCheck()
{
	for (UINT i = 0; i < layerMask.size(); i++)
		layerMask[i].fill(false);
}

void CCollisionManager::CollisionUpdate(UINT left, UINT right)
{
	for (CCollider* leftCollider : colliderList[left])
	{
		for (CCollider* rightCollider : colliderList[right])
		{
			// 자기 자신과의 충돌을 무시
			if (leftCollider == rightCollider)
				continue;

			// 충돌처리 확인
			if (leftCollider->IsCollision(rightCollider))
			{
				leftCollider->OnCollisionStay(rightCollider);
				rightCollider->OnCollisionStay(leftCollider);
			}
		}
	}
}

