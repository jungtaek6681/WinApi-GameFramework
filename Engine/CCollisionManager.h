#pragma once

class CCollider;

class CCollisionManager : public SingleTon<CCollisionManager>
{
	friend SingleTon<CCollisionManager>;
private:
	CCollisionManager();
	virtual ~CCollisionManager();

public:
	void Init();
	void Update();
	void Release();

	void AddCollider(CCollider* collider);
	void RemoveCollider(CCollider* collider);

private:
	list<CCollider*> colliderList;
};

