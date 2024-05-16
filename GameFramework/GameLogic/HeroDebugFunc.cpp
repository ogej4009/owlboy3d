#include "Hero.h"
#include "ValueData.h"
#include "EnumData.h"
#include <GameDebugPlus.h>

void Hero::DebugDisplay(bool _bDebugText)
{
	// 확인
	if (_bDebugText == false)
	{
		return;
	}

	// FPS
	wchar_t Arr[256] = { 0, };
	m_FpsTime -= GameTime::DeltaTime();
	if (0 >= m_FpsTime)
	{
		m_CalFpsResult = 1.0f / GameTime::DeltaTime();
		m_FpsTime = 1.0f;
	}

	swprintf_s(Arr, L" FPS : %f", m_CalFpsResult);
	GameDebugPlus::DrawDebugText(Arr, 30.0f, CVector(10.0f, 10.0f), CVector::WHITE);

	// 스펙
	swprintf_s(Arr, L"HERO POS : %f, %f", GetTrans()->GetWPos().X, GetTrans()->GetWPos().Y);
	GameDebugPlus::DrawDebugText(Arr, 15.0f, CVector(10.0f, 70.0f), CVector::WHITE);

	swprintf_s(Arr, L"HERO ACTOR SIZE : %f, %f", GetTrans()->GetWScale().X, GetTrans()->GetWScale().Y);
	GameDebugPlus::DrawDebugText(Arr, 15.0f, CVector(10.0f, 130.0f), CVector::WHITE);

	swprintf_s(Arr, L"HERO RENDERER SIZE : %f, %f", m_Render->GetWScale().X, m_Render->GetWScale().Y);
	GameDebugPlus::DrawDebugText(Arr, 15.0f, CVector(10.0f, 190.0f), CVector::WHITE);
	
	// 수정 
	swprintf_s(Arr, L"MAP FRAME SIZE : %f, %f", m_Render->GetWScale().X, m_Render->GetWScale().Y); // 이미지 텍스쳐 
	GameDebugPlus::DrawDebugText(Arr, 15.0f, CVector(10.0f, 250.0f), CVector::WHITE);

	swprintf_s(Arr, L"CAM SIZE : %f, %f", m_Render->GetWScale().X, m_Render->GetWScale().Y); // 캠 정보 
	GameDebugPlus::DrawDebugText(Arr, 15.0f, CVector(10.0f, 320.0f), CVector::WHITE);

	swprintf_s(Arr, L"MOUSE COORD : %f, %f", GameWin::MainObj()->MousePos().X, GameWin::MainObj()->MousePos().Y);
	GameDebugPlus::DrawDebugText(Arr, 15.0f, CVector(10.0f, 390.0f), CVector::WHITE);

	swprintf_s(Arr, L"MOUSE SCREEN COORD : %f, %f", 
		GetScene()->MainCam()->CamOrthMousePos2d().X, 
		GetScene()->MainCam()->CamOrthMousePos2d().Y);
	GameDebugPlus::DrawDebugText(Arr, 15.0f, CVector(10.0f, 460.0f), CVector::WHITE);

	swprintf_s(Arr, L"MOUSE WORLD COORD : %f, %f", 
		GetScene()->MainCam()->OrthWorldMousePos2d().X, 
		GetScene()->MainCam()->OrthWorldMousePos2d().Y);
	GameDebugPlus::DrawDebugText(Arr, 15.0f, CVector(10.0f, 530.0f), CVector::WHITE);

	/*
		GameDebugPlus::ConsolePrintText(L"%d Current Frame Hero Position : %f, %f",
										GameDebug::FrameCount(),
										GetTrans()->GetLPos().X,
										GetTrans()->GetLPos().Y
										);
	*/


	// 무엇을 들고 있나? 
	if (true == GetPickUp())
	{
		GameDebugPlus::DrawDebugText(L"PICKUP : TRUE", 15.0f, CVector(10.0f, 600.0f), CVector::WHITE);
	}
	else
	{
		GameDebugPlus::DrawDebugText(L"PICKUP : FALSE", 15.0f, CVector(10.0f, 670.0f), CVector::WHITE);
	}

	// 플레이어의 STATE는?
	//if ((UINT)GetState() != 0)
	//{
	//	return;
	//}


	//GameDebugPlus::DrawDebugText(L"STATE : ", m_StateName[(UINT)GetState()]);
	

}