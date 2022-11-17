#pragma once
class CCameraManager : public SingleTon<CCameraManager>
{
	friend SingleTon<CCameraManager>;
private:
	CCameraManager();
	virtual ~CCameraManager();

public:
	void				Init();
	void				Update();
	void				Release();

	const Vec2&			GetLookAt()						{ return lookAt; }
	const CGameObject*	GetTarget()						{ return target; }

	void				SetLookAt(const Vec2& lookAt)	{ this->lookAt = lookAt; }
	void				SetTarget(CGameObject* target)	{ this->target = target; }

private:
	// 목표 오브젝트를 지정할 경우 목표 위치는 목표 오브젝트의 위치로 지정됨
	Vec2				lookAt;		// 카메라가 보고있는 위치
	CGameObject*		target;		// 카메라의 목표 오브젝트
};

#define CAMERA	CCameraManager::GetInstance()