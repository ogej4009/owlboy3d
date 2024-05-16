#include "Hero.h"
#include "EnumData.h"
#include "ValueData.h"
#include <GameCol.h>
#include <GameDebugPlus.h>
#include "PickUp.h"
#include "CutScene.h"
#include "Arms.h"

Hero* Hero::MainPlayer;

void Hero::DirCheck()
{
	if (GameInput::Press(L"LEFT"))
	{
		m_Dir = DIR_STATE::DIRL;
	}

	if (GameInput::Press(L"RIGHT"))
	{
		m_Dir = DIR_STATE::DIRR;
	}

	ChangeDir(m_Dir);
}

void Hero::PrevDirCheck()
{
	if (m_PrevDir != m_Dir && m_Dir != DIR_STATE::DIRMAX)
	{
		m_PrevDir = m_Dir;
	}
}

void Hero::ChangeDir(DIR_STATE _Dir)
{
	switch (_Dir)
	{
	case DIR_STATE::DIRL:
		GetActor()->GetTrans()->SetLScale({ -1.0f, 1.0f, 1.0f });	
		break;
	case DIR_STATE::DIRR:
		GetActor()->GetTrans()->SetLScale({ 1.0f, 1.0f, 1.0f });
		break;
	case DIR_STATE::DIRU:
	case DIR_STATE::DIRD:
	case DIR_STATE::DIRMAX:
		break;
	default:
		break;
	}
}

void Hero::ChangeState(HEROSTATE _State)
{
	m_State = _State;
	m_Anim->ChangeAni(m_StateName[(UINT)_State]);
}

void Hero::Move(const CVector& _Dir, float _Speed)
{
	GetTrans()->WMove(_Dir * GameTime::DeltaTime(_Speed));
}

void Hero::JumpCheck()
{
	if (GameInput::Down(L"UP"))
	{
		GravityVec = { 0.0f, 0.03f, 0.0f };
		JumpVec = { 0.0f, 0.013f, 0.0f };
		ChangeState(HEROSTATE::JUMP);
	}
}

void Hero::Join(unsigned _Index)
{
	PickUpTarget = PickUp::ArrPickUpTarget[_Index]->FindComName<PickUp>(L"PickUp");
	PickUpTarget->Join(GetTrans());
	m_bPickUp = true;
}

void Hero::Withdraw()
{
	if (nullptr != PickUpTarget)
	{
		PickUpTarget->Withdraw();
		PickUpTarget = nullptr;
	}
	m_bPickUp = false;
}

void Hero::Init()
{
	m_bBlock = true;

	m_StateName[(unsigned int)HEROSTATE::STAND] = L"STAND";
	m_StateName[(unsigned int)HEROSTATE::RUN] = L"RUN";
	m_StateName[(unsigned int)HEROSTATE::JUMP] = L"JUMP";
	m_StateName[(unsigned int)HEROSTATE::FALL] = L"FALL";
	m_StateName[(unsigned int)HEROSTATE::THROW] = L"THROW";
	m_StateName[(unsigned int)HEROSTATE::FLYIDLE] = L"FLYIDLE";
	m_StateName[(unsigned int)HEROSTATE::FLY] = L"FLY";
	m_StateName[(unsigned int)HEROSTATE::FLYUP] = L"FLYUP";
	m_StateName[(unsigned int)HEROSTATE::FLYGLIDE] = L"FLYGLIDE";
	m_StateName[(unsigned int)HEROSTATE::FLYCARRYIDLE] = L"FLYCARRYIDLE";
	m_StateName[(unsigned int)HEROSTATE::FLYCARRY] = L"FLYCARRY";
	m_StateName[(unsigned int)HEROSTATE::FLYCARRYUP] = L"FLYCARRYUP";
	m_StateName[(unsigned int)HEROSTATE::FLYCARRYGLIDE] = L"FLYCARRYGLIDE";
	m_StateName[(unsigned int)HEROSTATE::FLYDOWNSTART] = L"FLYDOWNSTART";
	m_StateName[(unsigned int)HEROSTATE::FLYDOWNSTARTCARRY] = L"FLYDOWNSTARTCARRY";
	m_StateName[(unsigned int)HEROSTATE::FLYUPSTART] = L"FLYUPSTART";
	m_StateName[(unsigned int)HEROSTATE::FLYUPSTARTCARRY] = L"FLYUPSTARTCARRY";
	m_StateName[(unsigned int)HEROSTATE::ROLL] = L"ROLL";
	m_StateName[(unsigned int)HEROSTATE::ROLLGROUND] = L"ROLLGROUND";
	m_StateName[(unsigned int)HEROSTATE::SPREADWINGS] = L"SPREADWINGS";
	m_StateName[(unsigned int)HEROSTATE::STARTRUN] = L"STARTRUN";
	m_StateName[(unsigned int)HEROSTATE::STARTTOFLY] = L"STARTTOFLY";
	m_StateName[(unsigned int)HEROSTATE::STARTTOFLYCARRY] = L"STARTTOFLYCARRY";
	m_StateName[(unsigned int)HEROSTATE::TURNTOFLY] = L"TURNTOFLY";
	m_StateName[(unsigned int)HEROSTATE::TURNTOFLYCARRY] = L"TURNTOFLYCARRY";
	m_StateName[(unsigned int)HEROSTATE::TURNTORUN] = L"TURNTORUN";
	m_StateName[(unsigned int)HEROSTATE::TORNADO1] = L"TORNADO1";
	m_StateName[(unsigned int)HEROSTATE::TORNADO2] = L"TORNADO2";
	m_StateName[(unsigned int)HEROSTATE::DREAMFALL] = L"DREAMFALL";
	m_StateName[(unsigned int)HEROSTATE::DREAMRETURN] = L"DREAMRETURN";
	m_StateName[(unsigned int)HEROSTATE::DREAMFLY] = L"DREAMFLY";
	m_StateName[(unsigned int)HEROSTATE::TIREDFLIGHT] = L"TIREDFLIGHT";
	m_StateName[(unsigned int)HEROSTATE::SLEEP] = L"SLEEP";
	m_StateName[(unsigned int)HEROSTATE::WAKEUP] = L"WAKEUP";
	m_StateName[(unsigned int)HEROSTATE::GETOUT] = L"GETOUT";
	m_StateName[(unsigned int)HEROSTATE::TREASURE] = L"TREASURE";
	m_StateName[(unsigned int)HEROSTATE::DEATHSPIN] = L"DEATHSPIN";
	m_StateName[(unsigned int)HEROSTATE::DIE] = L"DIE";
	m_StateName[(unsigned int)HEROSTATE::DRINK] = L"DRINK";
	m_StateName[(unsigned int)HEROSTATE::DRINKTEA] = L"DRINKTEA";
	m_StateName[(unsigned int)HEROSTATE::EATTHROW] = L"EATTHROW";
	m_StateName[(unsigned int)HEROSTATE::EATCHOMP] = L"EATCHOMP";
	m_StateName[(unsigned int)HEROSTATE::EATSWALLOW] = L"EATSWALLOW";
	m_StateName[(unsigned int)HEROSTATE::EATREACTION] = L"EATREACTION";
	m_StateName[(unsigned int)HEROSTATE::ENTERDOOR] = L"ENTERDOOR";
	m_StateName[(unsigned int)HEROSTATE::TURNBACK] = L"TURNBACK";
	m_StateName[(unsigned int)HEROSTATE::TURNBACKTOFRONT] = L"TURNBACKTOFRONT";
	m_StateName[(unsigned int)HEROSTATE::EXITEND] = L"EXITEND";
	m_StateName[(unsigned int)HEROSTATE::EXITLOOP] = L"EXITLOOP";
	m_StateName[(unsigned int)HEROSTATE::EXITSAD] = L"EXITSAD";
	m_StateName[(unsigned int)HEROSTATE::POWERUP] = L"POWERUP";
	m_StateName[(unsigned int)HEROSTATE::RECOVERFROMSTUN] = L"RECOVERFROMSTUN";
	m_StateName[(unsigned int)HEROSTATE::RECOVERSLOWLY] = L"RECOVERSLOWLY";
	m_StateName[(unsigned int)HEROSTATE::HURTSTAND] = L"HURTSTAND";
	m_StateName[(unsigned int)HEROSTATE::HURTFLY] = L"HURTFLY";
	m_StateName[(unsigned int)HEROSTATE::HURTFLYCARRY] = L"HURTFLYCARRY";
	m_StateName[(unsigned int)HEROSTATE::FALLINGEYESOPEN] = L"FALLINGEYESOPEN";
	m_StateName[(unsigned int)HEROSTATE::STUMBLE] = L"STUMBLE";
	m_StateName[(unsigned int)HEROSTATE::DIVE] = L"DIVE";
	m_StateName[(unsigned int)HEROSTATE::RUNBLANK1] = L"RUNBLANK1";
	m_StateName[(unsigned int)HEROSTATE::RUNBLANK2] = L"RUNBLANK2";
	m_StateName[(unsigned int)HEROSTATE::RUNSAD] = L"RUNSAD";
	m_StateName[(unsigned int)HEROSTATE::WALKBLANK] = L"WALKBLANK";
	m_StateName[(unsigned int)HEROSTATE::WALKSAD] = L"WALKSAD";
	m_StateName[(unsigned int)HEROSTATE::WALKSERIOUS] = L"WALKSERIOUS";
	m_StateName[(unsigned int)HEROSTATE::SITDOWN] = L"SITDOWN";
	m_StateName[(unsigned int)HEROSTATE::SITTALK] = L"SITTALK";
	m_StateName[(unsigned int)HEROSTATE::STANDUP] = L"STANDUP";
	m_StateName[(unsigned int)HEROSTATE::LOOKUPSKY] = L"LOOKUPSKY";
	m_StateName[(unsigned int)HEROSTATE::COWER] = L"COWER";
	m_StateName[(unsigned int)HEROSTATE::COWEREND] = L"COWEREND";
	m_StateName[(unsigned int)HEROSTATE::DEPRESSEDDOWN] = L"DEPRESSEDDOWN";
	m_StateName[(unsigned int)HEROSTATE::DEPRESSEDRECOVER] = L"DEPRESSEDRECOVER";
	m_StateName[(unsigned int)HEROSTATE::DEPRESSEDSTART] = L"DEPRESSEDSTART";
	m_StateName[(unsigned int)HEROSTATE::DEPRESSEDUP] = L"DEPRESSEDUP";
	m_StateName[(unsigned int)HEROSTATE::NERVOUSEND] = L"NERVOUSEND";
	m_StateName[(unsigned int)HEROSTATE::NERVOUSL] = L"NERVOUSL";
	m_StateName[(unsigned int)HEROSTATE::NERVOUSR] = L"NERVOUSR";
	m_StateName[(unsigned int)HEROSTATE::NERVOUSSTART] = L"NERVOUSSTART";
	m_StateName[(unsigned int)HEROSTATE::SMILE] = L"SMILE";
	m_StateName[(unsigned int)HEROSTATE::SMILE2] = L"SMILE2";
	m_StateName[(unsigned int)HEROSTATE::SAD] = L"SAD";

	RenderInit();
	ColInit();

	m_Anim->CreateAni(L"STAND", L"sprOtusStand_112x96_13x1.png", 0, 12, 0.1f, true);
	m_Anim->CreateAni(L"RUN", L"sprOtusRun_112x96_12x1.png", 0, 11, 0.1f, true);
	m_Anim->CreateAni(L"JUMP", L"sprOtusJumpFall_112x96_5x2.png", 0, 2, 0.1f, false);
	m_Anim->CreateAni(L"FALL", L"sprOtusJumpFall_112x96_5x2.png", 5, 9, 0.1f, false);
	m_Anim->CreateAni(L"THROW", L"sprOtusThrow_112x96_6x1.png", 0, 5, 0.1f, false);
	m_Anim->CreateAni(L"FLYIDLE", L"sprOtusFly_112x96_11x2.png", 0, 10, 0.1f, true);
	m_Anim->CreateAni(L"FLY", L"sprOtusFly_112x96_11x2.png", 0, 10, 0.1f, true);
	m_Anim->CreateAni(L"FLYUP", L"sprOtusFly_112x96_11x2.png", 0, 10, 0.1f, true);
	m_Anim->CreateAni(L"FLYGLIDE", L"sprOtusFly_112x96_11x2.png", 11, 13, 0.1f, true);
	m_Anim->CreateAni(L"FLYCARRYIDLE", L"sprOtusFlyCarry_112x96_11x2.png", 0, 10, 0.1f, true);
	m_Anim->CreateAni(L"FLYCARRY", L"sprOtusFlyCarry_112x96_11x2.png", 0, 10, 0.1f, true);
	m_Anim->CreateAni(L"FLYCARRYUP", L"sprOtusFlyCarry_112x96_11x2.png", 0, 10, 0.1f, true);
	m_Anim->CreateAni(L"FLYCARRYGLIDE", L"sprOtusFlyCarry_112x96_11x2.png", 11, 13, 0.1f, true);
	m_Anim->CreateAni(L"FLYDOWNSTART", L"sprOtusFlyDownStart_112x96_6x1.png", 0, 5, 0.1f, false);
	m_Anim->CreateAni(L"FLYDOWNSTARTCARRY", L"sprOtusFlyDownStartCarry_112x96_6x1.png", 0, 5, 0.1f, false);
	m_Anim->CreateAni(L"FLYUPSTART", L"sprOtusFlyUpStart_112x96_8x1.png", 0, 7, 0.1f, false);
	m_Anim->CreateAni(L"FLYUPSTARTCARRY", L"sprOtusFlyUpStartCarry_112x96_8x1.png", 0, 7, 0.1f, false);
	m_Anim->CreateAni(L"ROLL", L"sprOtusRoll_112x96_9x1.png", 0, 8, 0.1f, false);
	m_Anim->CreateAni(L"ROLLGROUND", L"sprOtusRollGround_112x96_6x1.png", 0, 5, 0.1f, false);
	m_Anim->CreateAni(L"SPREADWINGS", L"sprOtusSpreadWings_112x96_9x1.png", 0, 8, 0.1f, false);
	m_Anim->CreateAni(L"STARTRUN", L"sprOtusStartRun_112x96_5x1.png", 0, 4, 0.1f, false);
	m_Anim->CreateAni(L"STARTTOFLY", L"sprOtusStartToFly_112x96_8x1.png", 0, 7, 0.1f, false);
	m_Anim->CreateAni(L"STARTTOFLYCARRY", L"sprOtusStartToFlyCarry_112x96_8x1.png", 0, 7, 0.1f, false);
	m_Anim->CreateAni(L"TURNTOFLY", L"sprOtusTurnToFly_112x96_9x1.png", 0, 8, 0.1f, false);
	m_Anim->CreateAni(L"TURNTOFLYCARRY", L"sprOtusTurnToFlyCarry_112x96_9x1.png", 0, 8, 0.1f, false);
	m_Anim->CreateAni(L"TURNTORUN", L"sprOtusTurnToRun_112x96_5x1.png", 0, 4, 0.1f, false);
	m_Anim->CreateAni(L"TORNADO1", L"sprOtusTornado_112x96_9x2.png", 0, 5, 0.1f, false);
	m_Anim->CreateAni(L"TORNADO2", L"sprOtusTornado_112x96_9x2.png", 0, 5, 0.1f, false);
	m_Anim->CreateAni(L"DREAMFALL", L"sprOtusDream_112x96_17x3.png", 0, 3, 0.1f, false);
	m_Anim->CreateAni(L"DREAMRETURN", L"sprOtusDream_112x96_17x3.png", 17, 33, 0.1f, false);
	m_Anim->CreateAni(L"DREAMFLY", L"sprOtusDream_112x96_17x3.png", 34, 40, 0.1f, false);
	m_Anim->CreateAni(L"TIREDFLIGHT", L"sprOtusTiredFlight_112x96_8x1.png", 0, 7, 0.1f, false);
	m_Anim->CreateAni(L"SLEEP", L"sprOtusInBed_112x96_8x3.png", 0, 4, 0.1f, false);
	m_Anim->CreateAni(L"WAKEUP", L"sprOtusInBed_112x96_8x3.png", 8, 15, 0.1f, false);
	m_Anim->CreateAni(L"GETOUT", L"sprOtusInBed_112x96_8x3.png", 16, 17, 0.1f, false);
	m_Anim->CreateAni(L"TREASURE", L"sprOtusTreasure_112x96_7x1.png", 0, 6, 0.1f, false);
	m_Anim->CreateAni(L"DEATHSPIN", L"sprOtusDeathSpin_112x96_9x1.png", 0, 8, 0.1f, false);
	m_Anim->CreateAni(L"DIE", L"sprOtusDie_112x96_12x1.png", 0, 11, 0.1f, false);
	m_Anim->CreateAni(L"DRINK", L"sprOtusDrink_112x96_16x1.png", 0, 15, 0.1f, false);
	m_Anim->CreateAni(L"DRINKTEA", L"sprOtusDrinkTea_15x1.png", 0, 14, 0.1f, false);
	m_Anim->CreateAni(L"EATTHROW", L"sprOtusEatThrow_112x96_7x1.png", 0, 6, 0.1f, false);
	m_Anim->CreateAni(L"EATCHOMP", L"sprOtusEatChomp_112x96_3x1.png", 0, 2, 0.1f, false);
	m_Anim->CreateAni(L"EATSWALLOW", L"sprOtusEatSwallow_112x96_4x1.png", 0, 3, 0.1f, false);
	m_Anim->CreateAni(L"EATREACTION", L"sprOtusEatReaction_112x96_5x1.png", 0, 4, 0.1f, false);
	m_Anim->CreateAni(L"ENTERDOOR", L"sprOtusEnterDoor_112x96_13x1.png", 0, 12, 0.1f, false);
	m_Anim->CreateAni(L"TURNBACK", L"sprOtusTurnBack_112x96_9x1.png", 0, 8, 0.1f, false);
	m_Anim->CreateAni(L"TURNBACKTOFRONT", L"sprOtusTurnBackToFront_112x96_6x1.png", 0, 5, 0.1f, false);
	m_Anim->CreateAni(L"EXITEND", L"sprOtusExitEnd_112x96_4x1.png", 0, 3, 0.1f, false);
	m_Anim->CreateAni(L"EXITLOOP", L"sprOtusExitLoop_112x96_8x1.png", 0, 7, 0.1f, false);
	m_Anim->CreateAni(L"EXITSAD", L"sprOtusExitSad_112x96_15x1.png", 0, 14, 0.1f, false);
	m_Anim->CreateAni(L"POWERUP", L"sprOtusPowerup_112x96_8x1.png", 0, 7, 0.1f, false);
	m_Anim->CreateAni(L"RECOVERFROMSTUN", L"sprOtusRecoverFromStun_112x96_4x1.png", 0, 3, 0.1f, false);
	m_Anim->CreateAni(L"RECOVERSLOWLY", L"sprOtusRecoverSlowly_112x96_9x1.png", 0, 8, 0.1f, false);
	m_Anim->CreateAni(L"HURTSTAND", L"sprOtusHurt_112x96_2x3.png", 0, 1, 0.1f, false);
	m_Anim->CreateAni(L"HURTFLY", L"sprOtusHurt_112x96_2x3.png", 2, 3, 0.1f, false);
	m_Anim->CreateAni(L"HURTFLYCARRY", L"sprOtusHurt_112x96_2x3.png", 4, 5, 0.1f, false);
	m_Anim->CreateAni(L"FALLINGEYESOPEN", L"sprOtusFallingEyesOpen_112x96_4x1.png", 0, 3, 0.1f, false);
	m_Anim->CreateAni(L"STUMBLE", L"sprOtusStumble_112x96_9x1.png", 0, 8, 0.1f, false);
	m_Anim->CreateAni(L"DIVE", L"sprOtusDive_112x96_5x1.png", 0, 4, 0.1f, false);
	m_Anim->CreateAni(L"RUNBLANK1", L"sprOtusRunBlank1_112x96_8x1.png", 0, 7, 0.1f, false);
	m_Anim->CreateAni(L"RUNBLANK2", L"sprOtusRunBlank2_112x96_8x1.png", 0, 7, 0.1f, false);
	m_Anim->CreateAni(L"RUNSAD", L"sprOtusRunSad_112x96_8x1.png", 0, 7, 0.1f, false);
	m_Anim->CreateAni(L"WALKBLANK", L"sprOtusWalkBlank_112x96_8x1.png", 0, 7, 0.1f, false);
	m_Anim->CreateAni(L"WALKSAD", L"sprOtusWalkSad_112x96_8x1.png", 0, 7, 0.1f, false);
	m_Anim->CreateAni(L"WALKSERIOUS", L"sprOtusWalkSerious_112x96_8x1.png", 0, 7, 0.1f, false);
	m_Anim->CreateAni(L"SITDOWN", L"sprOtusSitDown_112x96_14x1.png", 0, 13, 0.1f, false);
	m_Anim->CreateAni(L"SITTALK", L"sprOtusSitTalk_112x96_17x1.png", 0, 16, 0.1f, false);
	m_Anim->CreateAni(L"STANDUP", L"sprOtusStandUp_112x96_6x1.png", 0, 5, 0.1f, false);
	m_Anim->CreateAni(L"LOOKUPSKY", L"sprOtusLookUpSky_112x96_7x1.png", 0, 6, 0.1f, false);
	m_Anim->CreateAni(L"COWER", L"sprOtusCower_112x96_10x1.png", 0, 9, 0.1f, false);
	m_Anim->CreateAni(L"COWEREND", L"sprOtusCowerEnd_112x96_2x1.png", 0, 1, 0.1f, false);
	m_Anim->CreateAni(L"DEPRESSEDDOWN", L"sprOtusDepressedDown_112x96_2x1.png", 0, 1, 0.1f, false);
	m_Anim->CreateAni(L"DEPRESSEDRECOVER", L"sprOtusDepressedRecover_112x96_2x1.png", 0, 1, 0.1f, false);
	m_Anim->CreateAni(L"DEPRESSEDSTART", L"sprOtusDepressedStart_112x96_4x1.png", 0, 3, 0.1f, false);
	m_Anim->CreateAni(L"DEPRESSEDUP", L"sprOtusDepressedUp_112x96_2x1.png", 0, 1, 0.1f, false);
	m_Anim->CreateAni(L"NERVOUSEND", L"sprOtusNervousEnd_112x96_3x1.png", 0, 2, 0.1f, false);
	m_Anim->CreateAni(L"NERVOUSL", L"sprOtusNervousL_112x96_2x1.png", 0, 1, 0.1f, false);
	m_Anim->CreateAni(L"NERVOUSR", L"sprOtusNervousR_112x96_2x1.png", 0, 1, 0.1f, false);
	m_Anim->CreateAni(L"NERVOUSSTART", L"sprOtusNervousStart_112x96_4x1.png", 0, 3, 0.1f, false);
	m_Anim->CreateAni(L"SMILE", L"sprOtusSmile_112x96_4x1.png", 0, 3, 0.1f, false);
	m_Anim->CreateAni(L"SMILE2", L"sprOtusSmile2_112x96_5x1.png", 0, 4, 0.1f, false);
	m_Anim->CreateAni(L"SAD", L"sprOtusSad_112x96_14x1.png", 0, 13, 0.1f, false);

	ChangeState(HEROSTATE::STAND);

	m_Dir = DIR_STATE::DIRR;
	m_PrevDir = DIR_STATE::DIRR;

	m_DirFrameSensor[(unsigned int)DIR_STATE::DIRU] = CVector::UP * 11.0f * ValueData::PIXEL_SCALE;
	m_DirFrameSensor[(unsigned int)DIR_STATE::DIRD] = CVector::DOWN * 29.0f * ValueData::PIXEL_SCALE;
	m_DirFrameSensor[(unsigned int)DIR_STATE::DIRL] = CVector::LEFT * 10.0f * ValueData::PIXEL_SCALE;
	m_DirFrameSensor[(unsigned int)DIR_STATE::DIRR] = CVector::RIGHT * 10.0f * ValueData::PIXEL_SCALE;

	HudInit();
	DebugInit();

	GravityVec = { 0.0f, 0.5f, 0.0f };
	JumpVec = { 0.0f, 1.0f, 0.0f };

	LinkCamera();

}

void Hero::Update()
{

	if (true == CutScene::IsCutScene())
	{
		return;
	}

	//////////////////////////////////////////// TEST
	if (true == GameInput::Down(L"TRIGGER"))
	{
		TEST_ENTER_HUD();
		TEST_ENTER_UI();
	}

	if (true == GameInput::Down(L"DEBUG"))
	{
		if (true == m_bDebugCol)
		{
			m_bDebugCol = false;
			DebugSubOff();
		}
		else
		{
			m_bDebugCol = true;
			DebugSubOn();
		}
	}

	if (true == GameInput::Down(L"DEBUG"))
	{
		if (true == m_bDebugText)
		{
			m_bDebugText = false;
		}
		else
		{
			m_bDebugText = true;
		}
	}

	DebugDisplay(m_bDebugText);

	ColLevelBlock();

	DirCheck();

	switch (m_State)
	{
	case HEROSTATE::STAND:
		Stand();
		break;
	case HEROSTATE::RUN:
		Run();
		break;
	case HEROSTATE::JUMP:
		Jump();
		break;
	case HEROSTATE::FALL:
		Fall();
		break;
	case HEROSTATE::THROW:
		Throw();
		break;
	case HEROSTATE::FLYIDLE:
		FlyIdle();
		break;
	case HEROSTATE::FLY:
		Fly();
		break;
	case HEROSTATE::FLYUP:
		FlyUp();
		break;
	case HEROSTATE::FLYGLIDE:
		FlyGlide();
		break;
	case HEROSTATE::FLYCARRYIDLE:
		FlyCarryIdle();
		break;
	case HEROSTATE::FLYCARRY:
		FlyCarry();
		break;
	case HEROSTATE::FLYCARRYUP:
		FlyCarryUp();
		break;
	case HEROSTATE::FLYCARRYGLIDE:
		FlyCarryGlide();
		break;
	case HEROSTATE::FLYDOWNSTART:
		FlyDownStart();
		break;
	case HEROSTATE::FLYDOWNSTARTCARRY:
		FlyDownStartCarry();
		break;
	case HEROSTATE::FLYUPSTART:
		FlyUpStart();
		break;
	case HEROSTATE::FLYUPSTARTCARRY:
		FlyUpStartCarry();
		break;
	case HEROSTATE::ROLL:
		Roll();
		break;
	case HEROSTATE::ROLLGROUND:
		RollGround();
		break;
	case HEROSTATE::SPREADWINGS:
		SpreadWings();
		break;
	case HEROSTATE::STARTTOFLY:
		StartToFly();
		break;
	case HEROSTATE::STARTTOFLYCARRY:
		StartToFlyCarry();
		break;
	case HEROSTATE::TURNTOFLY:
		TurnToFly();
		break;
	case HEROSTATE::TURNTOFLYCARRY:
		TurnToFlyCarry();
		break;
	case HEROSTATE::TURNTORUN:
		TurnToRun();
		break;
	case HEROSTATE::TORNADO1:
		Tornado1();
		break;
	case HEROSTATE::TORNADO2:
		Tornado2();
		break;
	case HEROSTATE::DREAMFALL:
		DreamFall();
		break;
	case HEROSTATE::DREAMRETURN:
		DreamReturn();
		break;
	case HEROSTATE::DREAMFLY:
		DreamFly();
		break;
	case HEROSTATE::TIREDFLIGHT:
		TiredFlight();
		break;
	case HEROSTATE::SLEEP:
		Sleep();
		break;
	case HEROSTATE::WAKEUP:
		WakeUp();
		break;
	case HEROSTATE::GETOUT:
		GetOut();
		break;
	case HEROSTATE::TREASURE:
		Treasure();
		break;
	case HEROSTATE::DEATHSPIN:
		DeathSpin();
		break;
	case HEROSTATE::DIE:
		Die();
		break;
	case HEROSTATE::DRINK:
		Drink();
		break;
	case HEROSTATE::DRINKTEA:
		DrinkTea();
		break;
	case HEROSTATE::EATTHROW:
		EatThrow();
		break;
	case HEROSTATE::EATCHOMP:
		EatChomp();
		break;
	case HEROSTATE::EATSWALLOW:
		EatSwallow();
		break;
	case HEROSTATE::EATREACTION:
		EatReaction();
		break;
	case HEROSTATE::ENTERDOOR:
		EnterDoor();
		break;
	case HEROSTATE::TURNBACK:
		TurnBack();
		break;
	case HEROSTATE::TURNBACKTOFRONT:
		TurnBackToFront();
		break;
	case HEROSTATE::EXITEND:
		ExitEnd();
		break;
	case HEROSTATE::EXITLOOP:
		ExitLoop();
		break;
	case HEROSTATE::EXITSAD:
		ExitSad();
		break;
	case HEROSTATE::POWERUP:
		Powerup();
		break;
	case HEROSTATE::RECOVERFROMSTUN:
		RecoverFromStun();
		break;
	case HEROSTATE::RECOVERSLOWLY:
		RecoverSlowly();
		break;
	case HEROSTATE::HURTSTAND:
		HurtStand();
		break;
	case HEROSTATE::HURTFLY:
		HurtFly();
		break;
	case HEROSTATE::HURTFLYCARRY:
		HurtFlyCarry();
		break;
	case HEROSTATE::FALLINGEYESOPEN:
		FallingEyesOpen();
		break;
	case HEROSTATE::STUMBLE:
		Stumble();
		break;
	case HEROSTATE::DIVE:
		Dive();
		break;
	case HEROSTATE::STARTRUN:
		StartRun();
		break;
	case HEROSTATE::RUNBLANK1:
		RunBlank1();
		break;
	case HEROSTATE::RUNBLANK2:
		RunBlank2();
		break;
	case HEROSTATE::RUNSAD:
		RunSad();
		break;
	case HEROSTATE::WALKBLANK:
		WalkBlank();
		break;
	case HEROSTATE::WALKSAD:
		WalkSad();
		break;
	case HEROSTATE::WALKSERIOUS:
		WalkSerious();
		break;
	case HEROSTATE::SITDOWN:
		SitDown();
		break;
	case HEROSTATE::SITTALK:
		SitTalk();
		break;
	case HEROSTATE::STANDUP:
		StandUp();
		break;
	case HEROSTATE::LOOKUPSKY:
		LookUpSky();
		break;
	case HEROSTATE::COWER:
		Cower();
		break;
	case HEROSTATE::COWEREND:
		CowerEnd();
		break;
	case HEROSTATE::DEPRESSEDDOWN:
		DepressedDown();
		break;
	case HEROSTATE::DEPRESSEDRECOVER:
		DepressedRecover();
		break;
	case HEROSTATE::DEPRESSEDSTART:
		DepressedStart();
		break;
	case HEROSTATE::DEPRESSEDUP:
		DepressedUp();
		break;
	case HEROSTATE::NERVOUSEND:
		NervousEnd();
		break;
	case HEROSTATE::NERVOUSL:
		NervousL();
		break;
	case HEROSTATE::NERVOUSR:
		NervousR();
		break;
	case HEROSTATE::NERVOUSSTART:
		NervousStart();
		break;
	case HEROSTATE::SMILE:
		Smile();
		break;
	case HEROSTATE::SMILE2:
		Smile2();
		break;
	case HEROSTATE::SAD:
		Sad();
		break;
	case HEROSTATE::MAX:
		break;
	default:
		break;
	}

	PrevDirCheck();

	CamMoveListUpdate();

	int a = 0;

}


Hero::Hero() :	m_Gravity(1.0f),
				m_RollSpeed(2.0f),
				m_MoveSpeed(2.0f),
				m_Jump(1.0f),
				m_bLand(false),
				m_bPickUp(false)
{ 
	MainPlayer = this; 
}

Hero::~Hero() {}


// 업데이트에서 하는 것이다 /////////////////////////////////////////////////////// 카메라 
//
//if (0 == m_Master->m_MoveList.size())
//{
//	ChangeState(IDLE);
//	return;
//}
//else
//{
//	MOVEDATA Data = ChildMove();
//
//
//	// 그것과의 거리가 0이 아니다 
//	if (0 != Data.m_MovePos.Len())
//	{
//		if (m_Dir != Data.m_eDir)
//		{
//			m_Dir = Data.m_eDir;
//			ChangeState(m_eState);
//		}
//
//		if (m_eState != WALK)
//		{
//			ChangeState(WALK);
//		}
//	}
//	else // 그것과의 거리가 0이다 
//	{
//		if (false == HSPLAYER::m_DirKey)
//		{
//			ChangeState(m_Dir, IDLE);
//		}
//	}
//}

///
/*
해당 스테이트에서

////////////list PushBack///////
	m_MoveList.push_back({ m_Dir, HSVEC2::DELTADIR(m_Dir) * m_MoveSpeed , Pos()});
	CamRectCheck();

	if (false == m_DirKey)
	{
		ChangeState(IDLE);
	}
이것을 추가
*/