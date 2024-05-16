#pragma once
#include <vector>
#include <assert.h>
#include <map>
#include "GameString.h"
#include "GameMath.h"

class GameInput
{
public:
	class GameKey
	{
	public:
		friend GameInput;

	public:
		GameString Name;
		std::vector<int> m_KeyVec;

		bool Down;
		bool Press;
		bool Up;
		bool Free;

	private:
		bool KeyCheck();
		void Update();

	private:
		GameKey() : Down(false), Press(false), Up(false), Free(true) {}
		~GameKey() {}
		// 0 != GetAsyncKeyState('A')
	};


public:
	class GameStatic
	{
	public:
		GameStatic();
		~GameStatic();
	};
	static GameStatic StaticInst;

private:
	static std::map<GameString, GameKey*> AllKey;

public:
	static GameKey* FindKey(const GameString& _KeyName)
	{
		if (AllKey.end() == AllKey.find(_KeyName))
		{
			return nullptr;
		}

		return AllKey[_KeyName];
	}

	///////////// 추가했습니다. 
	static bool IsKey(const GameString& _KeyName)
	{
		return nullptr != FindKey(_KeyName);
	}

	template<typename ... REST>
	static void CreateKey(const GameString& _KeyName, REST ... Arg)
	{
		GameKey* NewKey = FindKey(_KeyName);

		if (nullptr != NewKey)
		{
			assert(false);
		}

		NewKey = new GameKey();
		NewKey->Name = _KeyName;
		NewKey->m_KeyVec.reserve(sizeof...(Arg));
		PushKey(NewKey, Arg...);
	}

private:
	template<typename T, typename ... REST>
	static void PushKey(GameKey* _NewKey, T _Value, REST ... Arg)
	{
		_NewKey->m_KeyVec.push_back(_Value);
		PushKey(_NewKey, Arg...);
	}

	static void PushKey(GameKey* _NewKey)
	{
		AllKey.insert(std::map<GameString, GameKey*>::value_type(_NewKey->Name, _NewKey));
	}

public:
	static bool Down(const GameString& _Key)
	{
		GameKey* Ptr = FindKey(_Key);
		if (nullptr == Ptr) { assert(false); }
		return Ptr->Down;
	}

	static bool Press(const GameString& _Key)
	{
		GameKey* Ptr = FindKey(_Key);
		if (nullptr == Ptr) { assert(false); }
		return Ptr->Press;
	}

	static bool Up(const GameString& _Key)
	{
		GameKey* Ptr = FindKey(_Key);
		if (nullptr == Ptr) { assert(false); }
		return Ptr->Up;
	}

	static bool Free(const GameString& _Key)
	{
		GameKey* Ptr = FindKey(_Key);
		if (nullptr == Ptr) { assert(false); }
		return Ptr->Free;
	}

public:
	static CVector PrevPos;
	static CVector MouseDir;
	static CVector MousePos();
	static CVector MousePos3D();
	static CVector MouseDir3D();
	static CVector MouseDir3DNormal();

public:
	static void Update();

public:
	GameInput() {}
	~GameInput() {}
};

