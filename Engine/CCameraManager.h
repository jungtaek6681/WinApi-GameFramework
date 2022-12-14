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
	void				Render();
	void				Release();

	Vec2				WorldToScreenPoint(Vec2 worldPoint);	// 게임위치->화면위치
	Vec2				ScreenToWorldPoint(Vec2 screenPoint);	// 화면위치->게임위치

	void				Scroll(Vec2 dir, float velocity);

	void				FadeIn(float duration);	// 씬 진입 효과
	void				FadeOut(float duration);	// 씬 탈출 효과

	void				SetTargetPos(const Vec2& targetPos, float timeToTarget = 0);
	void				SetTargetObj(CGameObject* targetObj);

	const Vec2&			GetLookAt()							{ return lookAt; }
	const Vec2&			GetTargetPos()						{ return targetPos; }
	const CGameObject*	GetTargetObj()						{ return targetObj; }

private:
	void				MoveToTarget();
	void				BrightToTarget();

	// 목표 오브젝트를 지정할 경우 목표 위치는 목표 오브젝트의 위치로 지정됨
	Vec2				lookAt;				// 카메라가 보고있는 위치
	Vec2				targetPos;			// 카메라의 목표 위치
	CGameObject*		targetObj;			// 카메라의 목표 오브젝트
	float				timeToTarget;		// 목표까지 남은 시간

	CImage*				fadeImage;			// 전환 효과용 이미지
	float				targetBright;		// 카메라의 목표 밝기
	float				curBright;			// 카메라의 현재 밝기
	float				timeToBright;		// 카메라의 밝기 변화 남은시간
};

#define CAMERA	CCameraManager::GetInstance()