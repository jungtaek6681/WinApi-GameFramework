#include "pch.h"
#include "CSoundManager.h"

CSoundManager::CSoundManager()
{
	system = nullptr;
}

CSoundManager::~CSoundManager()
{
}

void CSoundManager::Init()
{
	// 사운드 시스템 생성
	FMOD_RESULT result;
	result = System_Create(&system);
	assert(FMOD_OK == result && "Create sound system falied");

	result = system->init(MAXCHANNEL, FMOD_INIT_NORMAL, nullptr);
	assert(FMOD_OK == result && "Init sound system falied");
}

void CSoundManager::Update()
{
	/* IMPORTANT! CALL THIS ONCE PER FRAME! */
	// FMOD 시스템이 사운드를 관리하기 위해 프레임마다 호출 필요
	FMOD_RESULT result = system->update();
	assert(FMOD_OK == result && "Update sound system falied");
}

void CSoundManager::Release()
{
	if (nullptr != system)
	{
		system->release();
		system->close();
	}
}

void CSoundManager::PlayOnce(CSound* sound, float volume)
{
	FMOD_RESULT result;

	result = sound->GetSound()->setMode(FMOD_LOOP_OFF);
	assert(FMOD_OK == result && "Set Loop failed");

	FMOD::Channel* channel;		// FMOD의 업데이트에서 모두 재생시 반환됨
	result = system->playSound(sound->GetSound(), nullptr, false, &(channel));
	assert(FMOD_OK == result && "Play sound failed");

	result = channel->setVolume(volume);
	assert(FMOD_OK == result && "Set volume failed");
}

void CSoundManager::PlayLoop(const wstring& soundName, CSound* sound, float volume)
{
	FMOD::Channel* channel = ChannelFind(soundName);
	if (nullptr != channel)
		Stop(soundName);

	FMOD_RESULT result;

	result = sound->GetSound()->setMode(FMOD_LOOP_NORMAL);
	assert(FMOD_OK == result && "Set Loop failed");

	result = system->playSound(sound->GetSound(), nullptr, false, &(channel));
	assert(FMOD_OK == result && "Play sound failed");

	result = channel->setVolume(volume);
	assert(FMOD_OK == result && "Set volume failed");

	loopChannels.insert(make_pair(soundName, channel));
}

void CSoundManager::Stop(const wstring& soundName)
{
	FMOD::Channel* channel = ChannelFind(soundName);
	if (nullptr == channel)
		return;

	FMOD_RESULT result = channel->stop();
	assert(FMOD_OK == result && "Stop sound failed");
	loopChannels.erase(soundName);
}

void CSoundManager::StopAll()
{
	for (pair<wstring, FMOD::Channel*> channel : loopChannels)
	{
		FMOD_RESULT result = channel.second->stop();
		assert(FMOD_OK == result && "Stop sound failed");
	}
	loopChannels.clear();
}

void CSoundManager::Pause(const wstring& soundName)
{
	FMOD::Channel* channel = ChannelFind(soundName);
	if (nullptr == channel)
		return;

	FMOD_RESULT result = channel->setPaused(true);
	assert(FMOD_OK == result && "SetPaused failed");
}

void CSoundManager::Resume(const wstring& soundName)
{
	FMOD::Channel* channel = ChannelFind(soundName);
	if (nullptr == channel)
		return;

	FMOD_RESULT result = channel->setPaused(false);
	assert(FMOD_OK == result && "SetResume failed");
}

FMOD::Channel* CSoundManager::ChannelFind(const wstring& soundName)
{
	auto iter = loopChannels.find(soundName);
	if (iter == loopChannels.end())
		return nullptr;
	else
		return iter->second;
}
