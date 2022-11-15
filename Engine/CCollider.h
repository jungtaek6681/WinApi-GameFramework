#pragma once
class CCollider : public Component<CGameObject>, public IRender
{
public:
	CCollider();
	virtual ~CCollider();

public:
	const Vec2&		GetPos()						{ return pos; }
	const Vec2&		GetOffset()						{ return offset; }
	const Vec2&		GetScale()						{ return scale; }

	void			SetPos(const Vec2& pos)			{ this->pos = pos; }
	void			SetOffset(const Vec2& offset)	{ this->offset = offset; }
	void			SetScale(const Vec2 scale)		{ this->scale = scale; }

private:
	void			Render()						override;

	void			ComponentInit()					override;
	void			ComponentOnEnable()				override;
	void			ComponentUpdate()				override;
	void			ComponentRender()				override;
	void			ComponentOnDisable()			override;
	void			ComponentRelease()				override;

	Vec2			pos;
	Vec2			offset;							// 충돌체의 변위차
	Vec2			scale;

private:
	// 충돌시점 함수
	void			OnCollisionStay(CCollider* other);		// 충돌 중
};

