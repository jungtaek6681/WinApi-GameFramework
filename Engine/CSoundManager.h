#pragma once
class CSoundManager : public SingleTon<CSoundManager>
{
	friend SingleTon<CSoundManager>;
private:
	CSoundManager();
	virtual ~CSoundManager();

public:
	const static UINT MAXCHANNEL = 32;

	void			Init();
	void			Update();
	void			Release();

	void			PlayOnce(CSound* sound, float volume = 1.f);
	void			PlayLoop(const wstring& soundName, CSound* sound, float volume = 1.f);

	void			Stop(const wstring& soundName);
	void			StopAll();

	void			Pause(const wstring& soundName);
	void			Resume(const wstring& soundName);

	FMOD::Channel*	ChannelFind(const wstring& soundName);

	System*			GetSystem() { return system; }

private:
	FMOD::System* system;
	map<wstring, FMOD::Channel*> loopChannels;
};

#define SOUND	CSoundManager::GetInstance()