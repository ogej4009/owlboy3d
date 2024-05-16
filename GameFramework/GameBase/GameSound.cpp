#include "GameSound.h"
#include "GameString.h"
#include <assert.h>


GameSound::GameSoundStarter::GameSoundStarter() { Init(); }
GameSound::GameSoundStarter::~GameSoundStarter() {}

std::map<GameString, FMOD::Channel*> GameSound::m_pAllPlaySound;
FMOD::System* GameSound::m_pSoundSys = nullptr;
GameSound::GameSoundStarter GameSound::Starter;

void GameSound::Init()
{
#pragma region FMOD CALLBACK
	/*
	m_pSoundSys를 인자로 하면 값을 채워주고 리턴한다.
	사운드 카드가 없다면, nullptr이 나올 수 있다.
	*/
#pragma endregion	
	FMOD::System_Create(&m_pSoundSys);

	if (nullptr == m_pSoundSys)
	{
		assert(true);
	}

#pragma region FMOD CHANNEL
	/*
	채널 갯수를 32로 한다. 32 채널이면 8126개까지 동시재생 가능하다.
	*/
#pragma endregion
	if (FMOD_OK != m_pSoundSys->init(32, FMOD_DEFAULT, nullptr))
	{
		assert(true);
	}
}

void GameSound::Update()
{
	m_pSoundSys->update();
}

void GameSound::Play(const GameString& _Name)
{
	CPtr<GameSound> Sound = Find(_Name);

	if (nullptr == Sound)
	{
		assert(false);
	}

	m_pSoundSys->playSound(Sound->m_pSound, nullptr, false, nullptr);
}

bool GameSound::IsPlay(const GameString& _Name)
{
	std::map<GameString, FMOD::Channel*>::iterator Find = m_pAllPlaySound.find(_Name);

	if (Find == m_pAllPlaySound.end())
	{
		return false;
	}

	bool Playing = false;

	Find->second->isPlaying(&Playing);

	return Playing;
}

void GameSound::Stop(const GameString& _Name)
{
	std::map<GameString, FMOD::Channel*>::iterator Find = m_pAllPlaySound.find(_Name);

	if (Find == m_pAllPlaySound.end())
	{
		return;
	}

	Find->second->stop();
}

void GameSound::Play(const GameString& _PlayName, const GameString& _FileName)
{
	CPtr<GameSound> Sound = Find(_FileName);

	if (nullptr == Sound)
	{
		assert(false);
	}

	std::map<GameString, FMOD::Channel*>::iterator Find = m_pAllPlaySound.find(_PlayName);

	if (Find == m_pAllPlaySound.end())
	{
		FMOD::Channel* Ptr = nullptr;
		m_pSoundSys->playSound(Sound->m_pSound, nullptr, false, &Ptr);

		if (nullptr == Ptr)
		{
			assert(false);
		}

		m_pAllPlaySound.insert(std::map<GameString, FMOD::Channel*>::value_type(_PlayName, Ptr));

		return;
	}

	Find->second->stop(); // setPaused() == 일시정지 , setVolume() 

	FMOD::Channel* Ptr = nullptr;
	m_pSoundSys->playSound(Sound->m_pSound, nullptr, false, &Ptr); // 재생 권한을 부여 

	if (nullptr == Ptr)
	{
		assert(false);
	}

	Find->second = Ptr;

}

void GameSound::Load(const GameFile& _File)
{
	if (nullptr != Find(_File.FileName()))
	{
		assert(false);
	}

	GameSound* NewSound = CreateAndInsertToFileObj(_File);
	NewSound->Load();
}

void GameSound::Load()
{
	std::string Path = CFile.FullPath();

	if (FMOD_OK != m_pSoundSys->createSound(Path.c_str(), FMOD_DEFAULT, nullptr, &m_pSound))
	{
		assert(true);
	}
}