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

			// 충돌체와 충돌체의 ID 확인
			UINT64 collisionID = CollisionID(leftCollider->GetID(), rightCollider->GetID());
			// 충돌 정보가 없었던 경우, 충돌하지 않은 상태를 추가
			if (prevCollision.find(collisionID) == prevCollision.end())
				prevCollision.insert(make_pair(collisionID, false));

			// 충돌처리 확인
			if (leftCollider->IsCollision(rightCollider))
			{
				// 이전 프레임 O, 현재 프레임 O
				if (prevCollision[collisionID])
				{
					leftCollider->OnCollisionStay(rightCollider);
					rightCollider->OnCollisionStay(leftCollider);
				}
				// 이전 프레임 X, 현재 프레임 O
				else
				{
					leftCollider->OnCollisionEnter(rightCollider);
					rightCollider->OnCollisionEnter(leftCollider);
				}
				prevCollision[collisionID] = true;
			}
			else
			{
				// 이전 프레임 O, 현재 프레임 X
				if (prevCollision[collisionID])
				{
					leftCollider->OnCollisionExit(rightCollider);
					rightCollider->OnCollisionExit(leftCollider);
				}
				// 이전 프레임 X, 현재 프레임 X
				else
				{
					// 아무것도 하지 않음
				}
				prevCollision[collisionID] = false;
			}
		}
	}
}

UINT64 CCollisionManager::CollisionID(UINT leftID, UINT rightID)
{
	UINT64 result = 0;
	if (leftID < rightID)
	{
		result |= (UINT64)leftID << 32;
		result |= rightID;
		return result;
	}
	else
	{
		result |= (UINT64)rightID << 32;
		result |= leftID;
		return result;
	}
}
