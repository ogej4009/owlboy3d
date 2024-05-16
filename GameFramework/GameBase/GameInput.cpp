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

	return true; // ��·�� Ű�� ���ȴ�. 
}


void GameInput::GameKey::Update()
{
	if (KeyCheck()) // ��·�� Ű�� ���ȴ�. 
	{
		// Ű�� ó�� ���� ��Ȳ
		if (false == Press)
		{
			Down = true;
			Press = true;
			Up = false;
			Free = false;
		}
		else
			// ���� ��Ȳ�� Ű�� ������ ��� ������ �ִ�. 
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
			// ���� ��Ȳ�� Ű�� ��������. Ű�� ����.
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
	MouseDir = Pos - PrevPos;	// ������ġ - ������ġ
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

CVector GameInput::MousePos() // �߰��߽��ϴ�. 
{
	return GameWin::MainObj()->MousePos();
}


CVector GameInput::MousePos3D()
{
	return GameWin::MainObj()->MousePosVec3D();
}

CVector GameInput::MouseDir3D() // ũ��, ������ ���ÿ� �ȴ�. 
{
	return MouseDir;
}

CVector GameInput::MouseDir3DNormal()
{
	return MouseDir.Normal3dVecReturn();
}

