#pragma once
class CSoundManager : public SingleTon<CSoundManager>
{
	friend SingleTon<CSoundManager>;
private:
	CSoundManager();
	virtual ~CSoundManager();

public:
	const static UINT MAXCHANNEL = 32;

	void	Init();
	void	Update();
	void	Release();

	System* GetSystem() { return system; }

private:
	FMOD::System* system;
};

#define SOUND	CSoundManager::GetInstance()