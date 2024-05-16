#include "GameCamera.h"
#include <GameDebug.h>
#include <GameWin.h>
#include "GameActor.h"
#include <GameDebug.h>
#include "GameTransform.h"
#include "GameScene.h"
#include "GameRenderTarget.h"

#pragma region ����
/*
	���������ǰ����� �־�� ����� �����ϴ�.
	ī�޶� ����ִ� Actor�� ��ġ�� �� ī�޶� ���� �ִ� ��ġ��.
*/
#pragma endregion

void GameCamera::StartSetting(int _Order)
{
	if (nullptr == GetActor()->GetTrans())
	{
		MSG_ASSERT_CODE(L"Ʈ�������� ���� ���Ϳ� ķ�� �־����ϴ�.");
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
	m_GbufferTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // ��ǻ��
	m_GbufferTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // ������
	m_GbufferTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // �븻
	m_GbufferTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // ����
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
	m_DeferredLightTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // ��ǻ��
	m_DeferredLightTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // ����ŧ��
	m_DeferredLightTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // �����Ʈ
	m_DeferredLightTarget->CreateTarget(GameWin::MainObj()->Size(), CVector::NONE); // �׳� �������� Ÿ��
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

#pragma region ���������
	//CVector Pos		= GetActor()->GetTrans()->GetWPos();
	//CVector Forward	= GetActor()->GetTrans()->WForward();
	//CVector Up		= GetActor()->GetTrans()->WUp();
	// ������� ����� ���.(������� �ƴ� ��)(DXMAT���� ��ķ� Ȯ��)(ȸ����İ���������� �����Ѵ�.)  
	// �÷��̾�����ġ�� ������� ���ϸ� �÷��̾�� [0,0,0] ���������� �ִ�.
	// �׷��� ���� ���� ���� ȭ���� ������� �ִ�.
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
		MSG_ASSERT_CODE(L"ķ ��� ������ �߸��ƽ��ϴ�.");
		break;
	}

}

#pragma region ��ġ����
/*
	CamOrthMousePos2d : ķ�������Ǹ��콺��ġ��ǥ
	OrthWorldMousePos2d : ���念����������ġ��ǥ

	<�ʿ��Ѱ�>
	ȭ����Ŀ����ġ
	����Ʈ���(0~1������)

	"����� ������ �����̽��� �Ѿ�ڴ�."
	����� : �����̽�����ȯ ����Ʈ�����̽�->���������̽�->�佺���̽�->���彺���̽�->���ý����̽�

	Result >> �����쿵������ġ���� x [����İ���]����Ʈ���(���������̽�) ---(���)---> �������� ORTH����
	"Result x ķ������" �̰��� CamOrthMousePos2d()�� ���

	- ���������ǰ����� �־�� ����� �����ϴ�. -
	- ī�޶� ����ִ� Actor�� ��ġ�� �� ī�޶� ���� �ִ� ��ġ��. -

	ī�޶󰡺����ִ���ġ + CamOrthMousePos2d() => OrthWorldMousePos2d()

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

