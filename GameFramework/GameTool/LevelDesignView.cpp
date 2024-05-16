#include "pch.h"
#include "LevelDesignView.h"
#include "RView.h"
// -------------------------------- BAS
// -------------------------------- ENG
#include <GameCol.h>
#include <GameDebugPlus.h>
// -------------------------------- LOG
#include <EnumData.h>
#include <ValueData.h>
#include <DesignCam.h>
#include <FreeCam.h>

LevelDesignView* LevelDesignView::MainView = nullptr;

LevelDesignView::LevelDesignView()
{
	MainView = this;

}

LevelDesignView::~LevelDesignView()
{
}

void LevelDesignView::Progress()
{
	GameScene::Progress();
}

void LevelDesignView::Init()
{
	if (nullptr == GameInput::FindKey(L"SELECT"))
	{
		GameInput::CreateKey(L"SELECT", VK_LBUTTON);
		GameInput::CreateKey(L"DELETE", VK_RBUTTON);
	}

	FileCreate();

	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetLPos(ValueData::CAM_DEF_POS);
		CPtr<GameCamera> NewCam = NewActor->CreateCom<GameCamera>(0
			, (UINT)RENDER_ORDER::RO_ACTOR
			, (UINT)RENDER_ORDER::RO_COL_LEVEL);
		NewCam->SetCamSize({ 12.8f, 7.2f });
		NewCam->SetMode(CAMMODE::ORTH);
		m_FreeCamCom = NewActor->CreateCom<FreeCam>(10.0f);
		m_FreeCamActor = NewActor;
	} 

	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetLScale({ 12.8f * 10.0f, 7.2f * 10.0f, 3.0f });
		NewActor->GetTrans()->SetWPos({ 0.0f, 0.0f, -8.0f });
		CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>(L"TestGrid.png", (int)RENDER_ORDER::RO_ACTOR);
		NewRender->SetSprite(L"TestGrid.png", 0);
	}
}

void LevelDesignView::Update()
{
	SceneDebugDisplay();
}

void LevelDesignView::SceneChangeStart()
{
	

}

void LevelDesignView::SceneChangeEnd()
{
	//FileDelete();
}

void LevelDesignView::SceneDebugDisplay()
{
	wchar_t Arr[256];

	swprintf_s(Arr
		, L"[MousePos] X : %f, Y : %f"
		, GameWin::MainObj()->MousePos().X
		, GameWin::MainObj()->MousePos().Y
	);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,10 }, CVector::WHITE);

	swprintf_s(Arr
		, L"[MousePos3D] X : %f, Y : %f, Z : %f"
		, GameWin::MainObj()->MousePosVec3D().X
		, GameWin::MainObj()->MousePosVec3D().Y
		, GameWin::MainObj()->MousePosVec3D().Z
	);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,30 }, CVector::WHITE);

	swprintf_s(Arr
		, L"[MouseScreenOrth] X : %f, Y : %f"
		, GetScene()->MainCam()->CamOrthMousePos2d().X
		, GetScene()->MainCam()->CamOrthMousePos2d().Y
	);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,50 }, CVector::WHITE);

	swprintf_s(Arr
		, L"[MouseWorldOrth] X : %f, Y : %f"
		, GetScene()->MainCam()->OrthWorldMousePos2d().X
		, GetScene()->MainCam()->OrthWorldMousePos2d().Y
	);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,70 }, CVector::WHITE);

	swprintf_s(Arr, L"[CamPos] X : %f, Y : %f, Z : %f"
		, m_FreeCamActor->GetTrans()->GetWPos().X
		, m_FreeCamActor->GetTrans()->GetWPos().Y
		, m_FreeCamActor->GetTrans()->GetWPos().Z
	);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,90 }, CVector::WHITE);

	//swprintf_s(Arr, L"[CamScreenSize] X : %f, Y : %f"
	//	, m_FreeCamCom->GetCamSize().X
	//	, m_FreeCamCom->GetCamSize().Y);
	//GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,110 }, CVector::WHITE);

}
