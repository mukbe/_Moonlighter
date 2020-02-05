#pragma once

using namespace FMOD;

#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER


class SoundManager
{
	SingletonHeader(SoundManager)
private:
	typedef unordered_map<string, Sound**>			arrSounds;
	typedef unordered_map<string, Sound**>::iterator	arrSoundsIter;

	typedef unordered_map<string, Channel**>				arrChannels;
	typedef unordered_map<string, Channel**>::iterator	arrChannelsIter;
	
	using arrPlayCount = unordered_map<string, int>;
private:
	System* _system;
	Sound** _sound;
	Channel** _channel;
	
	arrSounds _mTotalSounds;
	arrPlayCount playCount;
public:

	void Init();
	void Release();
	void Update();

	void AddSound(string keyName, string soundName, bool bgm, bool loop);

	void Play(string keyName, float volume = 1.0f);
	void Stop(string keyName);
	void Pause(string keyName);
	void Resume(string keyName);

	//사운드 이벤트 처리용 (호옥시 몰라)
	bool IsPlaySound(string keyName);
	bool IsPauseSound(string keyName);

	unsigned int Getposition(string keyName);
	unsigned int Getlength(string keyName);
	void Setposition(string keyName, unsigned int time);
	void SetVolume(string keyName, float volume);



};


#define SOUNDMANAGER SoundManager::Get()