#include "pch.h"
#include "CCollider.h"

CCollider::CCollider()
{
	pos		= Vec2(0, 0);
	offset	= Vec2(0, 0);
	scale	= Vec2(0, 0);
	zOrder	= -10;
}

CCollider::~CCollider()
{
}

void CCollider::Render()
{
	RENDER->SetPen(PenType::Solid, RGB(0, 255, 0));
	RENDER->SetBrush(BrushType::Null);

	RENDER->Rect(
		pos.x - scale.x * 0.5f,
		pos.y - scale.y * 0.5f,
		pos.x + scale.x * 0.5f,
		pos.y + scale.y * 0.5f);

	RENDER->SetPen();
	RENDER->SetBrush();
}

void CCollider::ComponentInit()
{
}

void CCollider::ComponentUpdate()
{
	pos = GetOwner()->GetWorldPos() + offset;
}

void CCollider::ComponentRender()
{
	GetScene()->AddRenderer(this);
}

void CCollider::ComponentRelease()
{
}

void CCollider::OnCollisionStay(CCollider* other)
{
	Logger::Debug(TEXT("Ãæµ¹ Áß"));
}
