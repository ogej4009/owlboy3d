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
	m_pSoundSys�� ���ڷ� �ϸ� ���� ä���ְ� �����Ѵ�.
	���� ī�尡 ���ٸ�, nullptr�� ���� �� �ִ�.
	*/
#pragma endregion	
	FMOD::System_Create(&m_pSoundSys);

	if (nullptr == m_pSoundSys)
	{
		assert(true);
	}

#pragma region FMOD CHANNEL
	/*
	ä�� ������ 32�� �Ѵ�. 32 ä���̸� 8126������ ������� �����ϴ�.
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

	Find->second->stop(); // setPaused() == �Ͻ����� , setVolume() 

	FMOD::Channel* Ptr = nullptr;
	m_pSoundSys->playSound(Sound->m_pSound, nullptr, false, &Ptr); // ��� ������ �ο� 

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