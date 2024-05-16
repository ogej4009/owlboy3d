#include "GameCamera.h"
#include <GameDebug.h>
#include <GameWin.h>
#include "GameActor.h"
#include <GameDebug.h>
#include "GameTransform.h"
#include "GameScene.h"
#include "GameRenderTarget.h"

#pragma region 진실
/*
	같은개념의공간에 있어야 계산이 가능하다.
	카메라를 들고있는 Actor의 위치가 곧 카메라가 보고 있는 위치다.
*/
#pragma endregion

void GameCamera::StartSetting(int _Order)
{
	if (nullptr == GetActor()->GetTrans())
	{
		MSG_ASSERT_CODE(L"트랜스폼이 없는 액터에 캠을 넣었습니다.");
	}

	Order(_Order);

	m_CamFov = 60.0F;
	m_CamFar = 1000.0F;
	m_CamNear = 0.1F;
	m_Mode = CAMMODE::ORTH;
	m_CamSize = GameWin::MainObj()->Size();

	GetActor()->GetScene()->PushCam(this);


	m_CamTarget = new GameRenderTarget();
	m_CamTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE);
	m_CamTarget->Depth(GameDevice::MainObj()->BackBufferRenderTarget()->Depth());



	m_ForwardCamTarget = new GameRenderTarget();
	m_ForwardCamTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE);
	m_ForwardCamTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(1), CVector::NONE, false);
	m_ForwardCamTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(2), CVector::NONE, false);
	m_ForwardCamTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(3), CVector::NONE, false);
	m_ForwardCamTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(4), CVector::NONE, false);
	m_ForwardCamTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(5), CVector::NONE, false);
	m_ForwardCamTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(6), CVector::NONE, false);
	m_ForwardCamTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(7), CVector::NONE, false);
	m_ForwardCamTarget->Depth(GameDevice::MainObj()->BackBufferRenderTarget()->Depth());

	m_DeferredCamTarget = new GameRenderTarget();
	m_DeferredCamTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE);
	m_DeferredCamTarget->Depth(GameDevice::MainObj()->BackBufferRenderTarget()->Depth());

	m_GbufferTarget = new GameRenderTarget();
	m_GbufferTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // 디퓨즈
	m_GbufferTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // 포지션
	m_GbufferTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // 노말
	m_GbufferTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // 깊이
	m_GbufferTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(4), CVector::NONE, false);
	m_GbufferTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(5), CVector::NONE, false);
	m_GbufferTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(6), CVector::NONE, false);
	m_GbufferTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(7), CVector::NONE, false);
	m_GbufferTarget->Depth(GameDevice::MainObj()->BackBufferRenderTarget()->Depth());

	DeferredLightPlayer = new GameRenderPlayer();
	DeferredLightPlayer->SetMesh(L"TargetFullRect");
	DeferredLightPlayer->SetMaterial(L"DeferredLight");
	DeferredLightPlayer->SetSampler(L"Smp", L"LWSMP");
	DeferredLightPlayer->SetTexture(L"PosTex", m_GbufferTarget->Texture(1));
	DeferredLightPlayer->SetTexture(L"NorTex", m_GbufferTarget->Texture(2));


	m_DeferredLightTarget = new GameRenderTarget();
	m_DeferredLightTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // 디퓨즈
	m_DeferredLightTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // 스펙큘러
	m_DeferredLightTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // 엠비언트
	m_DeferredLightTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // 그냥 다합쳐진 타겟
	m_DeferredLightTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(4), CVector::NONE, false);
	m_DeferredLightTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(5), CVector::NONE, false);
	m_DeferredLightTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(6), CVector::NONE, false);
	m_DeferredLightTarget->CreateTarget(GameDevice::MainObj()->DataRenderTarget()->Texture(7), CVector::NONE, false);
	m_DeferredLightTarget->Depth(GameDevice::MainObj()->BackBufferRenderTarget()->Depth());





	DeferredMergePlayer = new GameRenderPlayer();
	DeferredMergePlayer->SetMesh(L"TargetFullRect");
	DeferredMergePlayer->SetMaterial(L"DeferredMerge");
	DeferredMergePlayer->SetSampler(L"Smp", L"LWSMP");
	DeferredLightPlayer->SetSampler(L"ShadowSmp", L"LCSMP");
	DeferredMergePlayer->SetTexture(L"DifColor", m_GbufferTarget->Texture(0));
	DeferredMergePlayer->SetTexture(L"LightColor", m_DeferredLightTarget->Texture(3));

}

void GameCamera::RenderPrev()
{

#pragma region 뷰행렬이해
	//CVector Pos		= GetActor()->GetTrans()->GetWPos();
	//CVector Forward	= GetActor()->GetTrans()->WForward();
	//CVector Up		= GetActor()->GetTrans()->WUp();
	// 뷰행렬을 만드는 방법.(뷰행렬을 아는 것)(DXMAT에서 행렬로 확인)(회전행렬개념원리에서 유추한다.)  
	// 플레이어의위치에 뷰행렬을 곱하면 플레이어는 [0,0,0] 공간영역에 있다.
	// 그래서 실제 내가 보는 화면의 정가운데에 있다.
#pragma endregion

	m_View.VIEWLH(GetActor()->GetTrans()->GetWPos(), GetActor()->GetTrans()->WForward(), GetActor()->GetTrans()->WUp());

	switch (m_Mode)
	{
	case CAMMODE::ORTH:
		m_Proj.ORTHLH(m_CamSize, m_CamNear, m_CamFar);
		break;
	case CAMMODE::PERS:
		m_Proj.PERSDEG(m_CamFov, m_CamSize, m_CamNear, m_CamFar);
		break;
	default:
		MSG_ASSERT_CODE(L"캠 모드 설정이 잘못됐습니다.");
		break;
	}

}

#pragma region 위치계산법
/*
	CamOrthMousePos2d : 캠영역안의마우스위치좌표
	OrthWorldMousePos2d : 월드영역에서의위치좌표

	<필요한것>
	화면의커서위치
	뷰포트행렬(0~1강제함)

	"행렬의 곱으로 스페이스를 넘어가겠다."
	역행렬 : 스페이스의전환 뷰포트스페이스->투영스페이스->뷰스페이스->월드스페이스->로컬스페이스

	Result >> 윈도우영역의위치벡터 x [역행렬곱한]뷰포트행렬(투영스페이스) ---(결과)---> 투영공간 ORTH공간
	"Result x 캠사이즈" 이것이 CamOrthMousePos2d()의 결과

	- 같은개념의공간에 있어야 계산이 가능하다. -
	- 카메라를 들고있는 Actor의 위치가 곧 카메라가 보고 있는 위치다. -

	카메라가보고있는위치 + CamOrthMousePos2d() => OrthWorldMousePos2d()

*/
#pragma endregion

CVector GameCamera::CamOrthMousePos2d()
{
	CVector ScreenMousePos = GameWin::MainObj()->MousePos();
	CMatrix ScreenViewPort = GameWin::MainObj()->ViewPort();

	ScreenViewPort.INVERSE();
	ScreenMousePos *= ScreenViewPort;
	ScreenMousePos *= GetCamSize().HalfVec();
	return ScreenMousePos;
}


CVector GameCamera::OrthWorldMousePos2d()
{
	return GetTrans()->GetWPos2d() + CamOrthMousePos2d();
}



CVector GameCamera::ScreenPos3dToWorldPos(const CVector& _ScreenPos)
{
	CVector WinScale = GameWin::MainObj()->Size();
	CVector ConPos;
	ConPos.X = _ScreenPos.X * m_CamSize.X / WinScale.X;
	ConPos.Y = _ScreenPos.Y * m_CamSize.Y / WinScale.Y;
	ConPos += GetTrans()->GetWPos();
	return ConPos;
}


/////////////////////////////////////////////////////////////////////////


void GameCamera::CamTargetMerge()
{
	m_CamTarget->Clear(false);
	m_CamTarget->Merge(m_ForwardCamTarget);
	m_CamTarget->Merge(m_DeferredCamTarget);
}

void GameCamera::CalDeferredLight(const LightData& _Data, CPtr<GameTexture> _Tex)
{
	m_DeferredLightTarget->Setting();
	DeferredLightPlayer->SetCBuffer(L"OneLightData", (void*)&_Data, CBUFMODE::CB_LINK);
	DeferredLightPlayer->SetTexture(L"ShadowTex", _Tex);
	DeferredLightPlayer->Render();
	DeferredLightPlayer->Reset();
}



CPtr<GameRenderTarget> GameCamera::CamTarget()
{
	return m_CamTarget;
}

CPtr<GameRenderTarget> GameCamera::ForwardCamTarget()
{
	return m_ForwardCamTarget;
}

CPtr<GameRenderTarget> GameCamera::DeferredCamTarget()
{
	return m_DeferredCamTarget;
}

CPtr<GameRenderTarget> GameCamera::GbufferTarget()
{
	return m_GbufferTarget;
}


void GameCamera::DeferredMerge()
{
	m_DeferredCamTarget->Clear(false);
	m_DeferredCamTarget->Setting();
	DeferredMergePlayer->Render();
	DeferredMergePlayer->Reset();
}



CPtr<GameRenderTarget> GameCamera::DeferredLightTarget()
{
	return m_DeferredLightTarget;
}

void GameFilter::StartTargetCreate()
{
	OutTarget = new GameRenderTarget();
	OutTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE);
}

void GameCamera::CamMergeNextEffect()
{
	for (auto& _Filter : GameObjListTFuncMgr<GameFilter>::m_ObjList)
	{
		_Filter.Obj->CamMergeNextEffect();
	}
}

void GameCamera::CamMergePrevEffect()
{
	for (auto& _Filter : GameObjListTFuncMgr<GameFilter>::m_ObjList)
	{
		_Filter.Obj->CamMergePrevEffect();
	}
}

void GameCamera::DeferredMergeNextEffect()
{
	for (auto& _Filter : GameObjListTFuncMgr<GameFilter>::m_ObjList)
	{
		_Filter.Obj->DeferredMergeNextEffect();
	}
}

void GameCamera::DeferredMergePrevEffect()
{
	for (auto& _Filter : GameObjListTFuncMgr<GameFilter>::m_ObjList)
	{
		_Filter.Obj->DeferredMergePrevEffect();
	}
}

