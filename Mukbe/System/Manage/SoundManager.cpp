#include "Mukbe.h"
#include "SoundManager.h"


SingletonCpp(SoundManager)

SoundManager::SoundManager()
{
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);

}


SoundManager::~SoundManager()
{
}

void SoundManager::Release()
{
	//사운드 삭제
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != NULL)
			{
				if (_sound != NULL) _sound[i]->release();
			}
		}
	}

	//메모리 지우기
	SafeDeleteArray(_channel);
	SafeDeleteArray(_sound);

	//시스템 닫기 
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

void SoundManager::Update()
{
	_system->update();
	if (Keyboard::Get()->Down('G'))
	{
		int count = 0;
		bool temp = _system->getChannelsPlaying(&count);
		int a = 10;
	}
}

void SoundManager::AddSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
	}
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));

}
//사운드를 플레이한 채널의 카운트를 저장하고 나중에 이 페어를 가지고 옵션들은 처리해야됨
//채널에 isPlaying 함수를 통해 카운트를 증감하여 플레이할때 넣어줘야됨
void SoundManager::Play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			break;
		}
	}

	bool isPlay;
	for (int i = 0;i < TOTALSOUNDBUFFER; i++)
	{
		_channel[i]->isPlaying(&isPlay);
		if (isPlay == false)
		{
			_channel[i]->setVolume(volume);
			_system->playSound(FMOD_CHANNEL_REUSE, *iter->second, false, &_channel[i]);

			playCount.insert(make_pair(keyName, i));
			break;
		}
	}



}

void SoundManager::Stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}


}

void SoundManager::Pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}

}

void SoundManager::Resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{

			_channel[count]->setPaused(false);
			break;
		}
	}

}

bool SoundManager::IsPlaySound(string keyName)
{
	bool isPlay = false;

	arrPlayCount::iterator Iter = playCount.find(keyName);
	if (Iter != playCount.end())
	{
		_channel[Iter->second]->isPlaying(&isPlay);
	}
	return isPlay;

}

bool SoundManager::IsPauseSound(string keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}
	
	return isPause;
}

unsigned int SoundManager::Getposition(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	unsigned int ps;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPosition(&ps, FMOD_TIMEUNIT_MS);
			return ps;
		}
	}
	return 0;
}
unsigned int SoundManager::Getlength(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	unsigned int ps;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_sound[count]->getLength(&ps, FMOD_TIMEUNIT_MS);
			return ps;
		}
	}
	return 0;
}
void SoundManager::Setposition(string keyName, unsigned int time)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	unsigned int ps = time;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPosition(ps, FMOD_TIMEUNIT_MS);
			break;
		}
	}

}
void SoundManager::SetVolume(string keyName, float volume)
{
	arrPlayCount::iterator Iter = playCount.find(keyName);
	if (Iter != playCount.end())
	{
		_channel[Iter->second]->setVolume(volume);
	}
	


}

