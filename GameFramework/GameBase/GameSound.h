#pragma once
#include <FMOD/x64/fmod.hpp> 
#include "GameIO.h"
#include <map>
#include "GameObjTFuncMgr.h"

// fmod_vc.lib	������ ��嶧 ���
// fmodL_vc.lib ����� ��嶧 ���

#ifdef X32
#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif
#else 
#ifdef _DEBUG 
#pragma comment(lib, "fmodL_vc.lib")
#else 
#pragma comment(lib, "fmod_vc.lib")
#endif
#endif

class GameString;
class GameFile;
class GameSound : public GameFileMgr<GameSound>
{
private:
	static FMOD::System* m_pSoundSys;

#pragma region FMOD������
	/*
		FMOD�� ��������� FMOD::Channel* �� �������̴�.
		ä���� �ް�, ä���� ���� ����� �����ؾ� �Ѵ�.
	*/
#pragma endregion

	static std::map<GameString, FMOD::Channel*> m_pAllPlaySound;

	class GameSoundStarter
	{
	public:
		GameSoundStarter();
		~GameSoundStarter();
	};
	static GameSoundStarter Starter;

public:
	static void Init();
	static void Update();

	static void Load(const GameFile& _File);
	static void Play(const GameString& _FileName);
	static void Play(const GameString& _PlayName, const GameString& _FileName);
	static void Stop(const GameString& _Name);
	static bool IsPlay(const GameString& _Name);

private:
	FMOD::Sound* m_pSound;

private:
	void Load();

public:
	GameSound() : m_pSound(nullptr) {}
	~GameSound() {}
};