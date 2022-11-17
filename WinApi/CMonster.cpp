#include "pch.h"
#include "CMonster.h"

CMonster::CMonster()
{
	name	= TEXT("¸ó½ºÅÍ");
	scale	= Vec2(100, 100);
}

CMonster::~CMonster()
{
}

void CMonster::Init()
{
	CCollider* collider = new CCollider();
	collider->SetScale(Vec2(90, 90));
	collider->SetLayer(Layer::Monster);
	AddChild(collider);
}

void CMonster::OnEnable()
{
}

void CMonster::Update()
{
}

void CMonster::Render()
{
	RENDER->Rect(
		renderPos.x - scale.x * 0.5f,
		renderPos.y - scale.y * 0.5f,
		renderPos.x + scale.x * 0.5f,
		renderPos.y + scale.y * 0.5f);
}

void CMonster::OnDisable()
{
}

void CMonster::Release()
{
}
