#pragma once

class CCollider;

class CCollisionManager : public SingleTon<CCollisionManager>
{
	friend SingleTon<CCollisionManager>;
private:
	CCollisionManager();
	virtual ~CCollisionManager();

public:
	static const UINT MAXLAYER = 64;

public:
	void	Init();
	void	Update();
	void	Release();

	void	AddCollider(CCollider* collider);
	void	RemoveCollider(CCollider* collider);

	void	CheckLayer(UINT left, UINT right);
	void	UnCheckLayer(UINT left, UINT right);
	void	ResetCheck();

private:
	void	CollisionUpdate(UINT left, UINT right);
	UINT64	CollisionID(UINT leftID, UINT rightID);

	array<list<CCollider*>, MAXLAYER>		colliderList;
	array<array<bool, MAXLAYER>, MAXLAYER>	layerMask;
	unordered_map<UINT64, bool>				prevCollision;
};

