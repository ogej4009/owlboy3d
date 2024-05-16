#pragma once
#include <iostream>
#include <crtdbg.h>
#include <assert.h>
#include "GameString.h"

#pragma region MESSAGE ASSERT ����
// Ư�� ���ǿ��� MSG_ASSERT_CODE�� �����޼����� ����� �ִ�. 
/*
	�ٸ� �������� ����� >>
	static void AssertMsg(const GameString& _Msg)
	{
		_wassert(_Msg, _crt_wide())
	}
*/
#pragma endregion


#ifdef _DEBUG
#define MSG_ASSERT_CODE(MESSAGE) _wassert(MESSAGE, _CRT_WIDE(__FILE__), (unsigned)(__LINE__))
#else
#define MSG_ASSERT_CODE(MESSAGE) assert(false)
#endif



class GameWin;
class GameDebug
{
	friend GameWin;
private:

	class GameDebugStarter
	{
	public:
		void StartTest() {}

	public:
		GameDebugStarter()
		{
			if (false == IsLeckCheck) 
			{
				_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
				IsLeckCheck = true;
			}
		}
		~GameDebugStarter()
		{
			if (true == bConsole)
			{
				FreeConsole();
			}

			if (nullptr != stream)
			{
				fclose(stream);
			}
		}
	};

	static GameDebugStarter Starter;  

	static bool IsLeckCheck;

	static void LeckCheck()
	{
		Starter.StartTest();
	}

	static int m_FrameCount;

public:
	static bool bConsole;
	static FILE* stream;

	static int FrameCount()
	{
		return m_FrameCount;
	}

	static void DebugFrameUpdate()
	{
		++m_FrameCount;
	}

public:

	static void OpenConsole()
	{
		if (0 == AllocConsole())
		{
			MSG_ASSERT_CODE(L"�ܼ�â�� ���µ� �����߽��ϴ�.");
		}
		else
		{
			freopen_s(&stream, "CONIN$", "rb", stdin);
			freopen_s(&stream, "CONOUT$", "wb", stdout);
			freopen_s(&stream, "CONOUT$", "wb", stderr);
			// GetLastError

			std::wcout.imbue(std::locale("korean"));
			std::wcout << L"�� ��µǴ��� ���ڽ��ϴ�." << std::endl;
			bConsole = true;
		}
	}

	template<typename ... REST>
	static void ConsolePrintText(const GameString& _Text, REST ... _Arg)
	{
		if (false == bConsole)
		{
			MSG_ASSERT_CODE(L"�ܼ�â�� ������ �ʾҽ��ϴ�.");
		}

		wchar_t ArrText[256];
		swprintf_s(ArrText, _Text, _Arg...);
		std::wcout << ArrText << std::endl;
	}

};