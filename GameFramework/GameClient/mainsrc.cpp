#include <memory> // c++형식 헤더 (#include <memory.h> 은 c형식 헤더) 
#include <GameWin.h>
#include <GameDevice.h>
#include <GameDebugPlus.h>
//#include <GameSound.h> 
#include <GameUnity.h>
#include "DemoScene.h"
#include "Intro.h"

#pragma comment(lib, "GameBase.lib")
#pragma comment(lib, "GameEngine.lib")
#pragma comment(lib, "GameLogic.lib")

int __stdcall EntityLoad()
{
	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Global");

		auto FileList = Dic.DirAllFile();
		for (auto& _File : FileList)
		{
			GameTexture::Load(_File);
		}
		//for (auto& _File : FileList)
		//{
		//	GameSprite::Create(_File.FileName(), 1, 1);
		//}
		GameSprite::Create(L"sprCursor_36x36_6x3.png", 6, 3); 
		GameSprite::Create(L"sprCircle_100x100.png", 1, 1); 
		GameSprite::Create(L"sprRect_100x100.png", 1, 1);
		GameSprite::Create(L"sprCircleFade_400x400.png", 1, 1);
		GameSprite::Create(L"sprSpotlight_167x55.png", 1, 1);
		GameSprite::Create(L"sprBorder_690x404.png", 1, 1);


		//sprBorder_690x404



	}

	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Global");
		Dic.Move(L"Grid");
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


	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Global");
		Dic.Move(L"Trigger");

		auto FileList = Dic.DirAllFile();
		for (auto& _File : FileList)
		{
			GameTexture::Load(_File);
		}
		GameSprite::Create(L"sprBtnLMouseEat_36x35_2x1.png", 2, 1);
		GameSprite::Create(L"sprBtnLMouseMash_35x36_2x1.png", 2, 1);
		GameSprite::Create(L"sprBtnRMouseGrab_36x35_2x1.png", 2, 1);
		GameSprite::Create(L"sprBtnRMouseThrow_36x35_2x1.png", 2, 1);
		GameSprite::Create(L"sprBtnRTeleport_47x31_2x1.png", 2, 1);
		GameSprite::Create(L"sprKeyTeleportGunner_52x48_2x1.png", 2, 1);
		GameSprite::Create(L"sprKeyFly_20x36_2x1.png", 2, 1);


	}

	{
		GameDirectory Dic;

		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Global");
		Dic.Move(L"Otus");

		auto FileList = Dic.DirAllFile();

		for (auto& _File : FileList)
		{
			GameTexture::Load(_File);
		}

		GameSprite::Create(L"sprOtusStand_112x96_13x1.png", 13, 1);
		GameSprite::Create(L"sprOtusRun_112x96_12x1.png", 12, 1);
		GameSprite::Create(L"sprOtusJumpFall_112x96_5x2.png", 5, 2);
		GameSprite::Create(L"sprOtusThrow_112x96_6x1.png", 6, 1);
		GameSprite::Create(L"sprOtusFly_112x96_11x2.png", 11, 2);
		GameSprite::Create(L"sprOtusFlyCarry_112x96_11x2.png", 11, 2);
		GameSprite::Create(L"sprOtusFlyDownStart_112x96_6x1.png", 6, 1);
		GameSprite::Create(L"sprOtusFlyDownStartCarry_112x96_6x1.png", 6, 1);
		GameSprite::Create(L"sprOtusFlyUpStart_112x96_8x1.png", 8, 1);
		GameSprite::Create(L"sprOtusFlyUpStartCarry_112x96_8x1.png", 8, 1);
		GameSprite::Create(L"sprOtusRoll_112x96_9x1.png", 9, 1);
		GameSprite::Create(L"sprOtusRollGround_112x96_6x1.png", 6, 1);
		GameSprite::Create(L"sprOtusSpreadWings_112x96_9x1.png", 9, 1);
		GameSprite::Create(L"sprOtusStartRun_112x96_5x1.png", 5, 1);
		GameSprite::Create(L"sprOtusStartToFly_112x96_8x1.png", 8, 1);
		GameSprite::Create(L"sprOtusStartToFlyCarry_112x96_8x1.png", 8, 1);
		GameSprite::Create(L"sprOtusTurnToFly_112x96_9x1.png", 9, 1);
		GameSprite::Create(L"sprOtusTurnToFlyCarry_112x96_9x1.png", 9, 1);
		GameSprite::Create(L"sprOtusTurnToRun_112x96_5x1.png", 5, 1);
		GameSprite::Create(L"sprOtusTornado_112x96_9x2.png", 9, 2);
		GameSprite::Create(L"sprOtusDream_112x96_17x3.png", 17, 3);
		GameSprite::Create(L"sprOtusTiredFlight_112x96_8x1.png", 8, 1);
		GameSprite::Create(L"sprOtusInBed_112x96_8x3.png", 8, 3);
		GameSprite::Create(L"sprOtusTreasure_112x96_7x1.png", 7, 1);
		GameSprite::Create(L"sprOtusDeathSpin_112x96_9x1.png", 9, 1);
		GameSprite::Create(L"sprOtusDie_112x96_12x1.png", 12, 1);
		GameSprite::Create(L"sprOtusDrink_112x96_16x1.png", 16, 1);
		GameSprite::Create(L"sprOtusDrinkTea_15x1.png", 15, 1);
		GameSprite::Create(L"sprOtusEatThrow_112x96_7x1.png", 7, 1);
		GameSprite::Create(L"sprOtusEatChomp_112x96_3x1.png", 3, 1);
		GameSprite::Create(L"sprOtusEatSwallow_112x96_4x1.png", 4, 1);
		GameSprite::Create(L"sprOtusEatReaction_112x96_5x1.png", 5, 1);
		GameSprite::Create(L"sprOtusEnterDoor_112x96_13x1.png", 13, 1);
		GameSprite::Create(L"sprOtusTurnBack_112x96_9x1.png", 9, 1);
		GameSprite::Create(L"sprOtusTurnBackToFront_112x96_6x1.png", 6, 1);
		GameSprite::Create(L"sprOtusExitEnd_112x96_4x1.png", 4, 1);
		GameSprite::Create(L"sprOtusExitLoop_112x96_8x1.png", 8, 1);
		GameSprite::Create(L"sprOtusExitSad_112x96_15x1.png", 15, 1);
		GameSprite::Create(L"sprOtusPowerup_112x96_8x1.png", 8, 1);
		GameSprite::Create(L"sprOtusRecoverFromStun_112x96_4x1.png", 4, 1);
		GameSprite::Create(L"sprOtusRecoverSlowly_112x96_9x1.png", 9, 1);
		GameSprite::Create(L"sprOtusHurt_112x96_2x3.png", 2, 3);
		GameSprite::Create(L"sprOtusFallingEyesOpen_112x96_4x1.png", 4, 1);
		GameSprite::Create(L"sprOtusStumble_112x96_9x1.png", 9, 1);
		GameSprite::Create(L"sprOtusDive_112x96_5x1.png", 5, 1);
		GameSprite::Create(L"sprOtusRunBlank1_112x96_8x1.png", 8, 1);
		GameSprite::Create(L"sprOtusRunBlank2_112x96_8x1.png", 8, 1);
		GameSprite::Create(L"sprOtusRunSad_112x96_8x1.png", 8, 1);
		GameSprite::Create(L"sprOtusWalkBlank_112x96_8x1.png", 8, 1);
		GameSprite::Create(L"sprOtusWalkSad_112x96_8x1.png", 8, 1);
		GameSprite::Create(L"sprOtusWalkSerious_112x96_8x1.png", 8, 1);
		GameSprite::Create(L"sprOtusSitDown_112x96_14x1.png", 14, 1);
		GameSprite::Create(L"sprOtusSitTalk_112x96_17x1.png", 17, 1);
		GameSprite::Create(L"sprOtusStandUp_112x96_6x1.png", 6, 1);
		GameSprite::Create(L"sprOtusLookUpSky_112x96_7x1.png", 7, 1);
		GameSprite::Create(L"sprOtusCower_112x96_10x1.png", 10, 1);
		GameSprite::Create(L"sprOtusCowerEnd_112x96_2x1.png", 2, 1);
		GameSprite::Create(L"sprOtusDepressedDown_112x96_2x1.png", 2, 1);
		GameSprite::Create(L"sprOtusDepressedRecover_112x96_2x1.png", 2, 1);
		GameSprite::Create(L"sprOtusDepressedStart_112x96_4x1.png", 4, 1);
		GameSprite::Create(L"sprOtusDepressedUp_112x96_2x1.png", 2, 1);
		GameSprite::Create(L"sprOtusNervousEnd_112x96_3x1.png", 3, 1);
		GameSprite::Create(L"sprOtusNervousL_112x96_2x1.png", 2, 1);
		GameSprite::Create(L"sprOtusNervousR_112x96_2x1.png", 2, 1);
		GameSprite::Create(L"sprOtusNervousStart_112x96_4x1.png", 4, 1);
		GameSprite::Create(L"sprOtusSmile_112x96_4x1.png", 4, 1);
		GameSprite::Create(L"sprOtusSmile2_112x96_5x1.png", 5, 1);
		GameSprite::Create(L"sprOtusSad_112x96_14x1.png", 14, 1);


	}




	return 1;
}

int __stdcall Start()
{

	if (nullptr == GameInput::FindKey(L"UP"))
	{
		GameInput::CreateKey(L"DEBUG", 'Q');
		GameInput::CreateKey(L"LEFT", 'A');
		GameInput::CreateKey(L"RIGHT", 'D');
		GameInput::CreateKey(L"UP", 'W');
		GameInput::CreateKey(L"DOWN", 'S');
		GameInput::CreateKey(L"SPACE", VK_SPACE);
		GameInput::CreateKey(L"LMOUSE", VK_LBUTTON);
		GameInput::CreateKey(L"RMOUSE", VK_RBUTTON);
		GameInput::CreateKey(L"MMOUSE", VK_MBUTTON);
		GameInput::CreateKey(L"1", '1'); // mechanic
		GameInput::CreateKey(L"2", '2'); // pirate
		GameInput::CreateKey(L"3", '3'); // spider
		GameInput::CreateKey(L"4", '4'); // kernelle
		GameInput::CreateKey(L"NEXTPAGE", 'P'); 
		GameInput::CreateKey(L"TRIGGER", 'T'); 
		GameInput::CreateKey(L"TRIGGER2", 'Y');


	}

#pragma region Sound 
	//{
	//	_ljGameDirectory Dic;
	//	Dic.MoveParent(L"_ljDxOwlboy");
	//	Dic.Move(L"RES");
	//	Dic.Move(L"Sound");
	//	auto FileList = Dic.DirAllFile();
	//	for (auto& _File : FileList)
	//	{
	//		_ljGameSound::Load(_File);
	//	}
	//	_ljGameSound::Play(L"25. Owl Temple.mp3");
	//} Win
#pragma endregion

	EntityLoad();


	GameScene::Create<DemoScene>(L"DEMO");
	GameScene::Create<Intro>(L"INTRO");

	GameScene::ChangeScene(L"INTRO");
	return 1;
}

int __stdcall Loop()
{
	GameScene::Progress();
	return 1;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
#pragma region 체크 사항
	/*
		4byte leak을 체크한다.
		_ljGameWin -> m_AllObj를 확인한다.
		_ljGameDevice -> m_AllObj를 확인한다.
		FirstObj 를 통해서 처음 만들어진 _ljGameWin, _ljGameDevice 를 쓰는 순간을 확인한다.
	*/
#pragma endregion

	new int();
	GameWin::Create(L"MainWindow");
	GameWin::MainObj()->Size({ 1280.0f, 720.0f });
	GameDevice::Create(L"MainWindow");
	GameWin::WINMESSAGE(Start, Loop);

}