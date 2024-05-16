#pragma once
#include "Entity.h"

enum class HUDSTATE
{
	FIND,
	FLY,
	GRAB,
	TELEPORT,
	MAX,
};

enum class UI_R_STATE
{
	RMOUSE,
	EAT,
	SHOOT,
	MAX,
};

enum class UI_L_STATE
{
	LMOUSE,
	MASH,
	TELEPORT,
	MAX,
};

enum class HEROSTATE
{
	/* 이동동작 */
	STAND,					//sprOtusStand_112x96_13x1.png									 
	RUN,					//sprOtusRun_112x96_12x1.png							
	JUMP,					//sprOtusJumpFall_112x96_5x2.png			0,2						
	FALL,					//sprOtusJumpFall_112x96_5x2.png			5,9						
	THROW,					//sprOtusThrow_112x96_6x1.png
	FLYIDLE,
	FLY,					//sprOtusFly_112x96_11x2.png				0,10				
	FLYUP,
	FLYGLIDE,				//sprOtusFly_112x96_11x2.png				11,13	
	FLYCARRYIDLE,
	FLYCARRY,				//sprOtusFlyCarry_112x96_11x2.png			0,10		
	FLYCARRYUP,
	FLYCARRYGLIDE,			//sprOtusFlyCarry_112x96_11x2.png			11,13	
	FLYDOWNSTART,			//sprOtusFlyDownStart_112x96_6x1.png
	FLYDOWNSTARTCARRY,		//sprOtusFlyDownStartCarry_112x96_6x1.png
	FLYUPSTART,				//sprOtusFlyUpStart_112x96_8x1.png
	FLYUPSTARTCARRY,		//sprOtusFlyUpStartCarry_112x96_8x1.png
	ROLL,					//sprOtusRoll_112x96_9x1.png
	ROLLGROUND,				//sprOtusRollGround_112x96_6x1.png
	SPREADWINGS,			//sprOtusSpreadWings_112x96_9x1.png
	STARTRUN,				//sprOtusStartRun_112x96_5x1.png
	STARTTOFLY,				//sprOtusStartToFly_112x96_8x1.png
	STARTTOFLYCARRY,		//sprOtusStartToFlyCarry_112x96_8x1.png
	TURNTOFLY,				//sprOtusTurnToFly_112x96_9x1.png
	TURNTOFLYCARRY,			//sprOtusTurnToFlyCarry_112x96_9x1.png
	TURNTORUN,				//sprOtusTurnToRun_112x96_5x1.png
	TORNADO1,				//sprOtusTornado_112x96_9x2.png				0,5		
	TORNADO2,				//sprOtusTornado_112x96_9x2.png				9,17
	DREAMFALL,				//sprOtusDream_112x96_17x3.png				0,3
	DREAMRETURN,			//sprOtusDream_112x96_17x3.png				17,33 
	DREAMFLY,				//sprOtusDream_112x96_17x3.png				34,40
	TIREDFLIGHT,			//sprOtusTiredFlight_112x96_8x1.png
	/* 기타동작 */
	SLEEP,					//sprOtusInBed_112x96_8x3.png				0,4		
	WAKEUP,					//sprOtusInBed_112x96_8x3.png				8,15	
	GETOUT,					//sprOtusInBed_112x96_8x3.png				16,17							
	TREASURE,				//sprOtusTreasure_112x96_7x1.png
	DEATHSPIN,				//sprOtusDeathSpin_112x96_9x1.png
	DIE,					//sprOtusDie_112x96_12x1.png
	DRINK,					//sprOtusDrink_112x96_16x1.png
	DRINKTEA,				//sprOtusDrinkTea_15x1.png
	EATTHROW,				//sprOtusEatThrow_112x96_7x1.png
	EATCHOMP,				//sprOtusEatChomp_112x96_3x1.png
	EATSWALLOW,				//sprOtusEatSwallow_112x96_4x1.png
	EATREACTION,			//sprOtusEatReaction_112x96_5x1.png
	ENTERDOOR,				//sprOtusEnterDoor_112x96_13x1.png
	TURNBACK,				//sprOtusTurnBack_112x96_9x1.png
	TURNBACKTOFRONT,		//sprOtusTurnBackToFront_112x96_6x1.png
	EXITEND,				//sprOtusExitEnd_112x96_4x1.png
	EXITLOOP,				//sprOtusExitLoop_112x96_8x1.png
	EXITSAD,				//sprOtusExitSad_112x96_15x1.png
	POWERUP,				//sprOtusPowerup_112x96_8x1.png
	RECOVERFROMSTUN,		//sprOtusRecoverFromStun_112x96_4x1.png
	RECOVERSLOWLY,			//sprOtusRecoverSlowly_112x96_9x1.png
	HURTSTAND,				//sprOtusHurt_112x96_2x3.png				0,1					
	HURTFLY,				//sprOtusHurt_112x96_2x3.png				2,3					
	HURTFLYCARRY,			//sprOtusHurt_112x96_2x3.png				4,5		
	/* 이벤트동작 */
	FALLINGEYESOPEN,		//sprOtusFallingEyesOpen_112x96_4x1.png  
	STUMBLE,				//sprOtusStumble_112x96_9x1.png
	DIVE,					//sprOtusDive_112x96_5x1.png
	RUNBLANK1,				//sprOtusRunBlank1_112x96_8x1.png
	RUNBLANK2,				//sprOtusRunBlank2_112x96_8x1.png
	RUNSAD,					//sprOtusRunSad_112x96_8x1.png
	WALKBLANK,				//sprOtusWalkBlank_112x96_8x1.png
	WALKSAD,				//sprOtusWalkSad_112x96_8x1.png
	WALKSERIOUS,			//sprOtusWalkSerious_112x96_8x1.png
	SITDOWN,				//sprOtusSitDown_112x96_14x1.png
	SITTALK,				//sprOtusSitTalk_112x96_17x1.png
	STANDUP,				//sprOtusStandUp_112x96_6x1.png
	LOOKUPSKY,				//sprOtusLookUpSky_112x96_7x1.png	
	/* 감정대기 */
	COWER,					//sprOtusCower_112x96_10x1.png
	COWEREND,				//sprOtusCowerEnd_112x96_2x1.png
	DEPRESSEDDOWN,			//sprOtusDepressedDown_112x96_2x1.png
	DEPRESSEDRECOVER,		//sprOtusDepressedRecover_112x96_2x1.png
	DEPRESSEDSTART,			//sprOtusDepressedStart_112x96_4x1.png
	DEPRESSEDUP,			//sprOtusDepressedUp_112x96_2x1.png
	NERVOUSEND,				//sprOtusNervousEnd_112x96_3x1.png
	NERVOUSL,				//sprOtusNervousL_112x96_2x1.png
	NERVOUSR,				//sprOtusNervousR_112x96_2x1.png
	NERVOUSSTART,			//sprOtusNervousStart_112x96_4x1.png
	SMILE,					//sprOtusSmile_112x96_4x1.png
	SMILE2,					//sprOtusSmile2_112x96_5x1.png	
	SAD,					//sprOtusSad_112x96_14x1.png	
	MAX,
};
// chkColorOff
class PickUp;
class ClientCam;
class Arms;
class HudTrigger;
class UITrigger;
class Hero : public Entity
{
public:
	friend PickUp;
	friend ClientCam;
	friend Arms;


	static Hero* MainPlayer;

	CPtr<ClientCam> m_CCam;
	CPtr<GameSpriteRenderer> m_Render;
	CPtr<GameAnimation> m_Anim;
	CPtr<GameCol> m_Col;

	DIR_STATE m_Dir;
	DIR_STATE m_PrevDir;

	HEROSTATE m_State;
	GameString m_StateName[(UINT)HEROSTATE::MAX];

	CVector m_DirFrameSensor[4];
	bool m_DirColorSensor[4];

	int m_Hp;
	float m_Ult;

	CPtr<GameActor> m_ArmsActor;
	CPtr<Arms> m_ArmsOverlay;

	bool m_bDebugText;
	bool m_bDebugCol;

	CPtr<GameSpriteRenderer> m_DebugRender[4];

	CVector JumpVec;
	CVector GravityVec;

	float m_Jump;
	float m_Gravity;// 
	float m_MoveSpeed;
	float m_RollSpeed;
	float m_AccelSpeed;

	CPtr<PickUp> PickUpTarget;
	bool m_bPickUp;

	float m_FpsTime;
	float m_CalFpsResult;

	bool m_bBlock;
	bool m_bLand;



private:
	class CamMoveInfo
	{
	public:
		float m_Angle;
		CVector m_Vector;
		CVector m_Pos;
	};
	std::list<CamMoveInfo> m_InfoList;
	CVector m_CamPos;

	float m_LimitDistance = 0.5f;

public:
	void LinkCamera();
	CamMoveInfo CamMovInfo();
	void CamMoveListUpdate(/*float _X, float _Y*/);

	float CamCalAngle();
	float CalDistance();

public:
	void CustomUpdate();

public:
	DIR_STATE GetCurDir()
	{
		return m_Dir;
	}

	DIR_STATE GetPrevDir()
	{
		return m_PrevDir;
	}

	bool GetPickUp()
	{
		return m_bPickUp;
	}

	void SetPickUp(bool _bPickUp)
	{
		m_bPickUp = _bPickUp;
	}

	HEROSTATE GetState()
	{
		return m_State;
	}

	bool CheckChild()
	{
		return PickUpTarget != nullptr;
	}

private:
	
	union
	{
		struct
		{
			bool m_bArrColorSensorMarker[4];
		};
		struct
		{
			int m_ColorMarker;
		};
	};

	union
	{
		struct
		{
			bool m_bArrColorSensorPurple[4];
		};
		struct
		{
			int m_ColorPurple;
		};
	};

	union
	{
		struct
		{
			bool m_bArrColorSensorBlack[4];
		};
		struct
		{
			int m_ColorBlack;
		};
	};

	union
	{
		struct
		{
			bool m_bArrColorSensorMagenta[4];
		};
		struct
		{
			int m_ColorMagenta;
		};
	};

	union
	{
		struct
		{
			bool m_bArrColorSensorGreen[4];
		};
		struct
		{
			int m_ColorGreen;
		};
	};


	union
	{
		struct
		{
			bool m_bArrColorSensorRed[4];
		};
		struct
		{
			int m_ColorRed;
		};
	};
	
	union
	{
		struct
		{
			bool m_bArrColorSensorBlue[4];
		};
		struct
		{
			int m_ColorBlue;
		};
	};

	/////////////////////////////////////////
	CPtr<GameTransform> m_HudTrans;
	CPtr<GameActor>		m_HudSlot[(UINT)HUDSTATE::MAX];
	CPtr<HudTrigger>	m_HudTriggerSlot[(UINT)HUDSTATE::MAX];
	HUDSTATE	m_HudState;

public:
	void HudSlot1();
	void HudSlot2();
	void TEST_ENTER_HUD();

	/////////////////////////////////////////
	CPtr<GameTransform> m_UITrans[2];
	CPtr<GameActor>		m_UISlot[2];
	CPtr<UITrigger>		m_UITriggerSlot[2];

public:
	void UISlot1();
	void UISlot2();
	void TEST_ENTER_UI();
	/////////////////////////////////////////


public:
	void JumpCheck();
	


public:
	void RenderInit();
	void ColInit();
	void DebugInit();
	void HudInit();
	void DebugSubOn();
	void DebugSubOff();
	void DebugDisplay(bool _bDebugText);

public:
	void Join(unsigned _Index);
	void Withdraw();

	///////////////////////////////////////
public:

	void ChkBlock();
	void ChkFly();
	void ChkJump();
	///////////////////////////////////////

public:
	void DirCheck();
	void PrevDirCheck();
	void ChangeDir(DIR_STATE _Dir);
	void ChangeState(HEROSTATE _State);

public:
	void Move(const CVector& _Dir, float _Speed);
	void ColLevelBlock();

public:
	void ColTriggerEnter(GameCol* _This, GameCol* _Other);
	void ColTriggerStay(GameCol* _This, GameCol* _Other);
	void ColTriggerExit(GameCol* _This, GameCol* _Other);

public:
	void Stand();
	void Run();
	void Jump();
	void Fall();
	void Throw();
	void FlyIdle();
	void Fly();
	void FlyUp();
	void FlyGlide();
	void FlyCarryIdle();
	void FlyCarry();
	void FlyCarryUp();
	void FlyCarryGlide();
	void FlyDownStart();
	void FlyDownStartCarry();
	void FlyUpStart();
	void FlyUpStartCarry();
	void Roll();
	void RollGround();
	void SpreadWings();
	void StartRun();
	void StartToFly();
	void StartToFlyCarry();
	void TurnToFly();
	void TurnToFlyCarry();
	void TurnToRun();
	void Tornado1();
	void Tornado2();
	void DreamFall();
	void DreamReturn();
	void DreamFly();
	void TiredFlight();
	void Sleep();
	void WakeUp();
	void GetOut();
	void Treasure();
	void DeathSpin();
	void Die();
	void Drink();
	void DrinkTea();
	void EatThrow();
	void EatChomp();
	void EatSwallow();
	void EatReaction();
	void EnterDoor();
	void TurnBack();
	void TurnBackToFront();
	void ExitEnd();
	void ExitLoop();
	void ExitSad();
	void Powerup();
	void RecoverFromStun();
	void RecoverSlowly();
	void HurtStand();
	void HurtFly();
	void HurtFlyCarry();
	void FallingEyesOpen();
	void Stumble();
	void Dive();
	void RunBlank1();
	void RunBlank2();
	void RunSad();
	void WalkBlank();
	void WalkSad();
	void WalkSerious();
	void SitDown();
	void SitTalk();
	void StandUp();
	void LookUpSky();
	void Cower();
	void CowerEnd();
	void DepressedDown();
	void DepressedRecover();
	void DepressedStart();
	void DepressedUp();
	void NervousEnd();
	void NervousL();
	void NervousR();
	void NervousStart();
	void Smile();
	void Smile2();
	void Sad();

public:
	void Init() override;
	void Update() override;

public:
	Hero();
	~Hero();
};

