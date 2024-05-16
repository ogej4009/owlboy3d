#include "FreeCam.h"
#include <GameActor.h>
#include <GameCamera.h>
#include <GameDebug.h> 
#include <GameInput.h>
#include <GameTransform.h>
#include <GameTime.h>
#include <GameRenderer.h>

void FreeCam::CamInitialization()
{
	GetTrans()->SetWPos(m_FixedPos);
	GetTrans()->SetWRot(m_FixedRot);
	m_Cam->SetCamFov(m_FixedFov);
}

void FreeCam::CamAcceleration()
{
	m_Speed += 0.1f;
}

void FreeCam::CamSpeedInit()
{
	m_Speed -= 0.1f;

	if (m_Speed <= 0.0f)
	{
		m_Speed = 0.0f;
	}
}

void FreeCam::CamZoomIn()
{
	if (m_Cam->GetCamFov() <= 1.0f)
	{
		return;
	}
	m_Cam->SetCamFov(m_Cam->GetCamFov() - 0.1f);
}

void FreeCam::CamZoomOut()
{
	m_Cam->SetCamFov(m_Cam->GetCamFov() + 0.1f);
}

void FreeCam::Init()
{
}

void FreeCam::Init(float _Speed)
{
	if (nullptr == GetActor()->FindComType<GameCamera>())
	{
		MSG_ASSERT_CODE(L"캠이 존재하지 않는 곳에 프리캠을 넣어줄수 없습니다.");
	}

	m_Cam = GetActor()->FindComType<GameCamera>();
	m_Speed = _Speed;
	m_RotSpeed = 200.0f;

	m_StartPos = GetTrans()->GetWPos();
	m_StartRot = GetTrans()->GetWRot();
	m_StartFov = m_Cam->GetCamFov();
	m_FixedPos = { 0.0f, 9.0f, -9.0f };
	m_FixedRot = { 45.0f, 0.0f, 0.0f };
	m_FixedFov = 45.0f;

	//if (false == GameInput::FindKey(L"CAM_LEFT"))
	//{
		GameInput::CreateKey(L"CAM_LEFT", VK_NUMPAD4);
		GameInput::CreateKey(L"CAM_RIGHT", VK_NUMPAD6);
		GameInput::CreateKey(L"CAM_UP", VK_NUMPAD8);
		GameInput::CreateKey(L"CAM_DOWN", VK_NUMPAD2);
		GameInput::CreateKey(L"CAM_FORWARD", VK_NUMPAD7);
		GameInput::CreateKey(L"CAM_BACK", VK_NUMPAD9);
		GameInput::CreateKey(L"CAM_ROT", VK_NUMPAD5);
		GameInput::CreateKey(L"CAM_INIT", VK_NUMPAD0);
		GameInput::CreateKey(L"CAM_SPEED_ACCEL", '+');
		GameInput::CreateKey(L"CAM_SPEED_DOWN", '-');
		GameInput::CreateKey(L"CAM_ZOOM_IN", VK_NUMPAD1);
		GameInput::CreateKey(L"CAM_ZOOM_OUT", VK_NUMPAD3);
	//}
}

void FreeCam::Update()
{
	if (true == GameInput::Press(L"CAM_LEFT"))
	{
		GetTrans()->LMove(GetTrans()->WLeft() * GameTime::DeltaTime(m_Speed));
	}

	if (true == GameInput::Press(L"CAM_RIGHT"))
	{
		GetTrans()->LMove(GetTrans()->WRight() * GameTime::DeltaTime(m_Speed));
	}

	if (true == GameInput::Press(L"CAM_UP"))
	{
		GetTrans()->LMove(GetTrans()->WUp() * GameTime::DeltaTime(m_Speed));
	}

	if (true == GameInput::Press(L"CAM_DOWN"))
	{
		GetTrans()->LMove(GetTrans()->WDown() * GameTime::DeltaTime(m_Speed));
	}

	if (true == GameInput::Press(L"CAM_FORWARD"))
	{
		GetTrans()->LMove(GetTrans()->WForward() * GameTime::DeltaTime(m_Speed));
	}

	if (true == GameInput::Press(L"CAM_BACK"))
	{
		GetTrans()->LMove(GetTrans()->WBack() * GameTime::DeltaTime(m_Speed));
	}

	if (true == GameInput::Press(L"CAM_ROT"))
	{
		GetTrans()->WRotAddY(GameInput::MouseDir3D().X * GameTime::DeltaTime(m_RotSpeed));
		GetTrans()->WRotAddX(-GameInput::MouseDir3D().Y * GameTime::DeltaTime(m_RotSpeed));
	}

	if (true == GameInput::Down(L"CAM_INIT"))
	{
		CamInitialization();
	}

	if (true == GameInput::Press(L"CAM_SPEED_ACCEL"))
	{
		CamAcceleration();
	}

	if (true == GameInput::Press(L"CAM_SPEED_DOWN"))
	{
		CamSpeedInit();
	}

	if (true == GameInput::Press(L"CAM_ZOOM_IN"))
	{
		CamZoomIn();
	}

	if (true == GameInput::Press(L"CAM_ZOOM_OUT"))
	{
		CamZoomOut();
	}
}

FreeCam::FreeCam()
{
}

FreeCam::FreeCam(float _Speed)
{
	m_Speed = _Speed;
}

FreeCam::~FreeCam()
{
}
