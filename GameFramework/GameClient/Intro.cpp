#include "Intro.h"
#include <ValueData.h>
#include <EnumData.h>
#include <GameTexture.h>
#include <GameSprite.h>
#include <GameSpriteRenderer.h>
#include <GameDebugPlus.h>
#include <ScrollCam.h>
#include <RectFade.h>

void Intro::Init()
{
}

void Intro::Update()
{
	SceneDebugDisplay();

	// 수정 
	//if (TRUE == GameInput::Down(L"NEXTPAGE"))
	//{
	//	GameScene::ChangeScene(L"INTRO");
	//}
}

void Intro::SceneChangeStart()
{
	SceneValueDataInit();

	// 파일구성
	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Local");
		Dic.Move(L"Intro");
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
		CPtr<GameCamera> NewCam = NewActor->CreateCom<GameCamera>(0, (UINT)RENDER_ORDER::RO_ACTOR);
		NewCam->SetCamSize({ 6.4f * 4.0f, 3.6f * 4.0f });
		NewCam->SetMode(CAMMODE::ORTH);
		// 컴포넌트 
		//CPtr<ScrollCam> CCam = NewActor->CreateCom<ScrollCam>(); // <<< 등록 
	}

	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos({ 0.0f, 0.0f, 10.0f });
		CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>((UINT)RENDER_ORDER::RO_ACTOR);
		NewRender->SetSprite(L"sprIntro_2782x1564.png");
		NewRender->SetSrcSizeOfTexture(L"sprIntro_2782x1564.png");
	}

	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos({ 0.0f, 0.0f, 0.0f });
		CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>();
		NewRender->SetSprite(L"sprDark_32x32.png");
		NewRender->SetWScale({ 100.0f, 100.0f, 1.0f });
		CPtr<RectFade> NewFade = NewActor->CreateCom<RectFade>();
		NewFade->FadeIn();
	}

}

void Intro::SceneChangeEnd()
{

	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Local");
		Dic.Move(L"Intro");
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

void Intro::SceneDebugDisplay()
{

	// 디버그 ON/OFF
	// 디버그 HUD 추가 
}

void Intro::SceneValueDataInit()
{
}

Intro::Intro()
{
}

Intro::~Intro()
{
}
