#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include "GameDebug.h"
#include "GameMath.h"
#include "GameObjTFuncMgr.h"
#include "CPtr.h"

typedef int(__stdcall* DEADTIME)();
typedef DEADTIME INITFUNC;

class GameMovie; // 추가 
class GameWin : public GameFirstObjMgr<GameWin>
{

#pragma region 이너클래스 == Starter 프로그래머들의 트릭
	/*
		메모리영역의 특징을 이용해서, 프로그램이 구동시 Main보다도 먼저 실행되는 함수를 만들고 싶을때 사용할수 있는 방식이다.
		데이터 영역에 있는 전역객체의 소멸자 이게 호출되는 순간은 언제일까?
		즉, 프로그램이 마지막에 종료됐을때, 유저가 게임을 껐을때 호출되는 것이다.
	*/
#pragma endregion

private:
	static void RegDef();
	class GameWinStarter
	{
	public:
		GameWinStarter()
		{
			RegDef();
		}
	};
	static GameWinStarter Starter;

private:
	static bool IsProcess;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	static void Create(const GameString& _WindowName, const GameString& _ClassName = L"DEF");
	static void Create(const GameString& _WindowName, HWND _HWnd);

public:
	static void WINMESSAGE(INITFUNC _Init, DEADTIME _CallBack);

private: 
	HWND m_HWND;
	HDC m_HDC;
	int Style;
	CVector m_Size;

public:
	HWND WINHWND()
	{
		return m_HWND;
	}

	HDC WINHDC()
	{
		return m_HDC;
	}

	CVector Size()
	{
		return m_Size;
	}

	CVector HalfSize()
	{
		return m_Size.HalfVec();
	}

private:
	GameMovie* MoviePlayer;

public:
	GameMovie* GetMoviePlayer()
	{
		return MoviePlayer;
	}


public: 
	CVector MousePos();
	CVector MousePosVec3D();
	CMatrix ViewPort();
	void Size(const CVector& _Size);
	CVector WindowPosTo3DPos(CVector _WindowPos);

public:
	GameWin(const GameString& _Name);
	GameWin(HWND _HWnd);
	~GameWin();
};