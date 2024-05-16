#include "GameRay.h"
#include "GameCol.h"
#include <GameInput.h>
#include "GameDebugPlus.h"
#include "GameTransform.h"
#include "GameCamera.h"
#include "GameRenderer.h"


void GameRay::TestRay(RayData _ray)
{
	GetTrans()->SetWPos({ _ray.Src.X ,_ray.Src.Y ,_ray.Src.Z });

	GetTrans()->SetWRot(_ray.Dir);

	CVector NewPos = GetTrans()->GetWPos();

	m_Col->GetTrans()->SetLScale(CVector{ 1.0f, 1.0f, 20.0f });
}

void GameRay::ShootRay(RayData _ray)
{
	CVector SysTest1 = _ray.Src;

	GetTrans()->SetWPos(m_Trans->GetTrans()->GetWPos());

	m_Vec = _ray.Dir;

	CVector SysTest2 = CVector::DirectionVector(m_Vec);

	m_Vec = SysTest2;

	m_bShoot = true;
}

void GameRay::TestCol(GameCol* _This, GameCol* _Other)
{
	_Other->GetTrans()->SetWScale(_Other->GetTrans()->GetWScale() * 1.5f);

	RayInit();
}

void GameRay::RayInit()
{
	m_Col->Off();
}

RayData GameRay::MakeRay(CVector _WinPos)
{
	CPtr<GameTransform> NewCam = m_Trans;

	CVector WinToCamPos = GameTransform::WinPosToSceenRatioStatic(_WinPos);

	CVector CamPos = NewCam->GetWPos();
	CVector CamRot = NewCam->GetWRot();

	RayData RD;
	RD.Src = CamPos;
	RD.Src.X += WinToCamPos.X;
	RD.Src.Y += WinToCamPos.Y;

	CVector DirOfProgress = (CamPos - CVector(RD.Src.X, RD.Src.Y, RD.Src.Z + 10.0f));
	RD.Dir = (DirOfProgress - CamRot).Normal3dVecReturn();
	CVector SysTest = RD.Dir;
	return RD;
}

void GameRay::RenderOnOff()
{
	if (true == m_bSwitch)
	{
		m_Render->Off();
	}
	else
	{
		m_Render->On();
	}
}

void GameRay::Init(CPtr<GameTransform> _Cam)
{
	m_bDebugSwitch = false;
	m_Trans = _Cam;

	if (nullptr == GameInput::FindKey(L"ADD"))
	{
		GameInput::CreateKey(L"ADD", VK_ADD);
	}

	{
		m_Col = GetActor()->CreateCom<GameCol>((int)COLTYPE::RAY3D);
		m_Col->SetParent(GetTrans());
		m_Col->ColType(COLTYPE::RAY3D);
		m_Col->SetLScale(CVector(1.0f, 1.0f, 1.0f));
		m_Col->PushEnterFunc(this, &GameRay::TestCol);
		m_Col->Off();
	}

	{
		m_Render = GetActor()->CreateCom<GameRenderer>(L"Cube", L"Deferred");
		m_Render->SetParent(GetTrans());
	}

	GetTrans()->WRotAddY( -90.0f );
	GetTrans()->WRotAddX( 45.0f );

}

void GameRay::Update()
{
	if (GameInput::Down(L"DEBUG_MODE"))
	{
		m_bDebugSwitch = !m_bDebugSwitch;
	}

	if (true == m_bDebugSwitch)
	{
		GameDebugPlus::DrawDebugText(L"Ray Pos X : %f, Y : %f, Z : %f : "
			, GetTrans()->GetWPos().X
			, GetTrans()->GetWPos().Y
			, GetTrans()->GetWPos().Z);

	}
	
	if (GameInput::Press(L"ADD"))
	{
		RayData SysRay = MakeRay(GameInput::MousePos3D());

		if (true == m_bDebugSwitch)
		{
			GameDebugPlus::DrawDebugText(L"Ray Dir X : %f, Y : %f, Z : %f : "
				, SysRay.Dir.X
				, SysRay.Dir.Y
				, SysRay.Dir.Z);

		}

		m_Col->On();
		ShootRay(SysRay);
	}
	else
	{
	}

	if (true == m_bShoot)
	{
		GetTrans()->WMove( m_Vec * 0.01f );
		CVector NewVec = m_Trans->GetWRot().Normal3dVecReturn();
	}

}