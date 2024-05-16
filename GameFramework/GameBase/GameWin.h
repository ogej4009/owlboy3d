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

class GameMovie; // �߰� 
class GameWin : public GameFirstObjMgr<GameWin>
{

#pragma region �̳�Ŭ���� == Starter ���α׷��ӵ��� Ʈ��
	/*
		�޸𸮿����� Ư¡�� �̿��ؼ�, ���α׷��� ������ Main���ٵ� ���� ����Ǵ� �Լ��� ����� ������ ����Ҽ� �ִ� ����̴�.
		������ ������ �ִ� ������ü�� �Ҹ��� �̰� ȣ��Ǵ� ������ �����ϱ�?
		��, ���α׷��� �������� ���������, ������ ������ ������ ȣ��Ǵ� ���̴�.
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