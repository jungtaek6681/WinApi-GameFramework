#pragma once
class CTimeManager : public SingleTon<CTimeManager>
{
	friend SingleTon<CTimeManager>;
private:
	CTimeManager();
	virtual ~CTimeManager();

public:
	void			Init();
	void			Update();
	void			Release();

	UINT			GetFPS();
	float			GetDT();

private:
	UINT			fps;	// FPS : 주사율(프레임), 1초당 그려진 화면 수
	float			dt;		// Delta Time : 단위시간, 1프레임당 소요된 시간

	int				updateCount;
	float			updateOneSecond;
	chrono::high_resolution_clock::time_point prevTime;	// 이전프레임의 시간
	chrono::high_resolution_clock::time_point curTime;	// 현재프레임의 시간
};

#define DT			CTimeManager::GetInstance()->GetDT()
#define FPS			CTimeManager::GetInstance()->GetFPS()