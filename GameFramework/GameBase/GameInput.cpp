#include "GameInput.h"
#include <Windows.h>
#include "GameWin.h"


std::map<GameString, GameInput::GameKey*> GameInput::AllKey;

CVector GameInput::PrevPos = CVector::ZERO;
CVector GameInput::MouseDir = CVector::ZERO;

GameInput::GameStatic GameInput::StaticInst;

GameInput::GameStatic::GameStatic()
{
}

GameInput::GameStatic::~GameStatic()
{
	for (auto& Item : AllKey)
	{
		delete Item.second;
	}
}

bool GameInput::GameKey::KeyCheck()
{
	for (size_t i = 0; i < m_KeyVec.size(); i++)
	{
		if (0 == GetAsyncKeyState(m_KeyVec[i]))
		{
			return false;
		}
	}

	return true; // 어쨌든 키가 눌렸다. 
}


void GameInput::GameKey::Update()
{
	if (KeyCheck()) // 어쨌든 키가 눌렸다. 
	{
		// 키를 처음 누른 상황
		if (false == Press)
		{
			Down = true;
			Press = true;
			Up = false;
			Free = false;
		}
		else
			// 이전 상황에 키를 눌렀고 계속 누르고 있다. 
		{
			Down = false;
			Press = true;
			Up = false;
			Free = false;
		}
	}
	else
	{
		if (true == Press)
		{
			// 이전 상황에 키를 눌렀었다. 키를 떼다.
			Down = false;
			Press = false;
			Up = true;
			Free = true;
		}
		else
		{
			Down = false;
			Press = false;
			Up = false;
			Free = true;
		}
	}

}


void GameInput::Update()
{
	CVector Pos = MousePos3D();
	MouseDir = Pos - PrevPos;	// 현재위치 - 이전위치
	PrevPos = Pos;

	if (MouseDir != CVector::ZERO)
	{
		int a = 0;
	}

	for (auto& Item : AllKey)
	{
		Item.second->Update();
	}
}

CVector GameInput::MousePos() // 추가했습니다. 
{
	return GameWin::MainObj()->MousePos();
}


CVector GameInput::MousePos3D()
{
	return GameWin::MainObj()->MousePosVec3D();
}

CVector GameInput::MouseDir3D() // 크기, 방향을 동시에 안다. 
{
	return MouseDir;
}

CVector GameInput::MouseDir3DNormal()
{
	return MouseDir.Normal3dVecReturn();
}

