#pragma once

class CCollisionManager;

class CCollider : public Component<CGameObject>, public IRender
{
	friend CCollisionManager;
public:
	CCollider();
	virtual ~CCollider();

public:
	UINT			GetID()							{ return id; }
	UINT			GetLayer()						{ return layer; }
	const Vec2&		GetPos()						{ return pos; }
	const Vec2&		GetOffset()						{ return offset; }
	const Vec2&		GetScale()						{ return scale; }

	void			SetLayer(UINT layer)			{ this->layer = layer; }
	void			SetPos(const Vec2& pos)			{ this->pos = pos; }
	void			SetOffset(const Vec2& offset)	{ this->offset = offset; }
	void			SetScale(const Vec2 scale)		{ this->scale = scale; }

private:
	virtual	bool	IsCollision(CCollider* other);

	void			Render()						override;

	void			ComponentInit()					override;
	void			ComponentOnEnable()				override;
	void			ComponentUpdate()				override;
	void			ComponentRender()				override;
	void			ComponentOnDisable()			override;
	void			ComponentRelease()				override;

	static UINT		colliderCount;					// 충돌체가 생성될때마다 증가하는 값
	UINT			id;								// 충돌체의 ID (게임에서 중복되지 않는 유일한 ID)
	UINT			count;							// 충돌중인 충돌체 갯수

	UINT			layer;							// 충돌체의 레이어
	Vec2			pos;
	Vec2			offset;							// 충돌체의 변위차
	Vec2			scale;

private:
	// 충돌시점 함수
	void			OnCollisionEnter(CCollider* other);		// 충돌 진입
	void			OnCollisionStay(CCollider* other);		// 충돌 중
	void			OnCollisionExit(CCollider* other);		// 충돌 해제
};

