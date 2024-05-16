#include "GameCol.h"
#include "GameScene.h"
#include "GameActor.h"
#include <GameInput.h>
#include "GameCamera.h"
#include "GameDebugPlus.h"


GameCol::GameCol()
{
}

GameCol::~GameCol()
{
}

void GameCol::ColCheck(CPtr<GameCol> _Other)
{

	if (true == Col(m_Type, _Other.PTR, _Other.PTR->m_Type)) // _Other.PTR 이거 업캐스팅이다. 
	{

		if (m_ColSet.end() == m_ColSet.find(_Other.PTR))
		{
			m_ColSet.insert(_Other.PTR);
			_Other.PTR->m_ColSet.insert(this);

			CallEnter(_Other);
			_Other->CallEnter(this);
		}
		else
		{
			CallStay(_Other);
			_Other->CallStay(this);
		}
	}
	else
	{

		if (m_ColSet.end() != m_ColSet.find(_Other.PTR))
		{
			CallExit(_Other);
			_Other->CallExit(this);

			// 충돌을 하지 않았는데 other가 this에 속해있는 경우 
			m_ColSet.erase(_Other.PTR);
			_Other.PTR->m_ColSet.erase(this);
		}
	}

}


void GameCol::Init(int _Order)
{
	SetParent(GetActor()->GetTrans());
	Order(_Order);
	GetActor()->GetScene()->PushCol(this);
	IsMouse = false;
}


#pragma region this문법
/*
	this == GameCol* const
	CPtr<GameCol>
*/
#pragma endregion

void GameCol::CallEnter(GameCol* _Other)
{
	for (auto& _Value : m_EnterFunc)
	{
		_Value(this, _Other);
	}
}


void GameCol::CallStay(GameCol* _Other)
{
	for (auto& _Value : m_StayFunc)
	{
		_Value(this, _Other);
	}
}


void GameCol::CallExit(GameCol* _Other)
{
	for (auto& _Value : m_ExitFunc)
	{
		_Value(this, _Other);
	}
}


void GameCol::Release()
{
	for (auto& _OtherCol : m_ColSet)
	{
		_OtherCol->m_ColSet.erase(this);
	}
}


void GameCol::Off()
{
	GameVirtualProgress::Off();

	for (auto& _OtherCol : m_ColSet)
	{
		_OtherCol->m_ColSet.erase(this);
	}

}



DirectX::SimpleMath::Ray GameCol::RAY3D()
{
	if (true == IsMouse)
	{
		CPtr<GameCamera> Cam = GetActor()->FindComType<GameCamera>();

		if (nullptr != Cam)
		{
			CVector MousePos = GameInput::MousePos();
			CVector ScreenSize = GameWin::MainObj()->Size();
			CVector StartPos = GetWPos();
			// -1~1
			// 0~화면 너비
			// -1~1사이의 어떤 값이 되었죠?
			CVector Dir;
			Dir.X = ((2.0f * MousePos.X) / ScreenSize.X) - 1.0f;
			Dir.Y = ((2.0f * MousePos.Y) / ScreenSize.Y) - 1.0f;
			Dir.Z = 1.0f;

			Dir.X *= (Cam->GetMrxProj().Arr2D[0][0] * 0.5f);
			Dir.Y *= (Cam->GetMrxProj().Arr2D[1][1] * 0.5f);
			Dir.Normalize3d();

			return DirectX::SimpleMath::Ray(StartPos.DXVEC, Dir.DXVEC);
		}

		return GameTransform::RAY3D();
	}

	return GameTransform::RAY3D();
}

