#include "DemoScene.h"
#include <ValueData.h>
#include <EnumData.h>
#include <GameTexture.h>
#include <GameSprite.h>
#include <GameSpriteRenderer.h>
#include <GameDebugPlus.h>
#include "DemoSceneObjUnity.h"

//#include "UITrigger.h"
#include "BorderTrigger.h"
//#include "HudTrigger.h"
#include "UICam.h"

void DemoScene::Init()
{
	//GetScene()->ColLink((UINT)COLLISION_ORDER::CO_PLAYER, (int)COLLISION_ORDER::CO_ENEMIES);
}

void DemoScene::Update()
{
	SceneDebugDisplay();

	// 수정 
	if (TRUE == GameInput::Down(L"NEXTPAGE"))
	{
		GameScene::ChangeScene(L"INTRO");
	}
}

void DemoScene::SceneChangeStart()
{
	// 필수 데이터 초기화 
	SceneValueDataInit();

	// 파일구성
	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Local");
		Dic.Move(L"Demo");
		auto FileList = Dic.DirAllFile();
		for (auto& _File : FileList)
		{
			GameTexture::Load(_File);
		}
		for (auto& _File : FileList)
		{
			GameSprite::Create(_File.FileName(), 1, 1);
		}
	}

	// 카메라 
	{
		// 액터
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos(ValueData::CAM_DEF_POS);
		// 등록부
		CPtr<GameCamera> NewCam = NewActor->CreateCom<GameCamera>(0, (UINT)RENDER_ORDER::RO_ACTOR, (UINT)RENDER_ORDER::RO_COL_LEVEL);
		NewCam->SetCamSize({ 6.4f, 3.6f });
		NewCam->SetMode(CAMMODE::PERS);
		// 컴포넌트 
		CPtr<ClientCam> CCam = NewActor->CreateCom<ClientCam>(); // <<< 등록 
		ClientCam::CamActor = NewActor;
	}


	{
		// 액터
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos(ValueData::CAM_DEF_POS);
		// 등록부
		CPtr<GameCamera> NewCam = NewActor->CreateCom<GameCamera>(1, (UINT)RENDER_ORDER::RO_UI);
		NewCam->SetCamSize({ 6.4f, 3.6f });
		NewCam->SetMode(CAMMODE::ORTH);
		// 컴포넌트 
		CPtr<UICam> CUICam = NewActor->CreateCom<UICam>(); // <<< 등록
	}

	// UI 
	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->CreateCom<Cursor>();
	}









	// 픽셀충돌
	/*{
		CVector Coord;
		Coord.X = ValueData::STAGE_SCALE.X * 0.5f;
		Coord.Y = ValueData::STAGE_SCALE.Y * -0.5f;
		Coord.Z = ValueData::DEBUG_DEFAULT_Z_ORDER;

		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWScale(ValueData::STAGE_SCALE);
		NewActor->GetTrans()->SetWPos(Coord);

		m_Debug = NewActor->CreateCom<GameSpriteRenderer>((UINT)RENDER_ORDER::RO_COL_LEVEL);
		m_Debug->SetSprite(ValueData::STAGE_NAME);
		m_Debug->SetSrcSizeOfTexture(ValueData::STAGE_NAME);
		m_Debug->Off();
	}*/


	// 플레이어
	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos(ValueData::PLAYER_DEFAULT_POS_INSTAGE);
		NewActor->CreateCom<Hero>();
	}

	//////////////////////////////////////////// 테스트 
	//{
	//	CPtr<GameActor> NewActor = GetScene()->CreateActor();
	//	NewActor->GetTrans()->SetWPos({ Hero::MainPlayer->GetTrans()->GetWPos().X, Hero::MainPlayer->GetTrans()->GetWPos().Y, -9.8f });
	//	CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>((UINT)RENDER_ORDER::RO_ACTOR);
	//	NewRender->SetSprite(L"sprCircleFade_400x400.png");
	//	NewRender->SetSrcSizeOfTexture(L"sprCircleFade_400x400.png");
	//	CPtr<CircleFade> NewFade = NewActor->CreateCom<CircleFade>();
	//	NewFade->FadeIn();
	//}


	////////////////////////////////////////////
	/*{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos({ 2.7f, -1.5f, -9.0f });
		NewActor->CreateCom<UITrigger>(L"sprBtnLMouseEat_36x35_2x1.png", 0.2f, 0, 1, true);
	}
	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos({ -2.7f, -1.5f, -9.0f });
		NewActor->CreateCom<UITrigger>(L"sprBtnLMouseEat_36x35_2x1.png", 0.2f, 0, 1, true);
	}*/

	













}

void DemoScene::SceneChangeEnd()
{
	// 지우기
	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Local");
		Dic.Move(L"Demo");
		auto FileList = Dic.DirAllFile();
		for (auto& _File : FileList)
		{
			GameTexture::Delete(_File.FileName());
		}
		for (auto& _File : FileList)
		{
			GameSprite::Delete(_File.FileName());
		}
	}
	GetScene()->ActorClear();
}

void DemoScene::SceneDebugDisplay()
{
	// 디버그 ON/OFF
	if (true == GameInput::Down(L"DEBUG"))
	{
		if (false == m_Debug->IsUpdateObj())
		{
			m_Debug->On();
		}
		else
		{
			m_Debug->Off();
		}
	}

	// 디버그 HUD 추가 
	// add ..
	// add ..
}

void DemoScene::SceneValueDataInit()
{
	ValueData::STAGE_NAME = L"sprDemoColLevel_1280x720.png"; // 이름 
	ValueData::STAGE_SCALE = { 1280.0f * 0.01f, 720.0f * 0.01f, 1.0f }; // TEX -> GET 크기 
	ValueData::PLAYER_DEFAULT_POS_INSTAGE = { 0.0f, 0.0f, ValueData::PLAYER_DEFAULT_Z_ORDER }; // 위치 
}

DemoScene::DemoScene()
{
}

DemoScene::~DemoScene()
{
}