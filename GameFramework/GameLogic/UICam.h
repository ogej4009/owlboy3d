#pragma once
#include "GameUnity.h"

enum class BORDER_TRIGGER_STATE
{
	BT_IDLE,
	BT_ON,
	BT_OFF,
	BT_RUN,
	MAX,
};

class UICam : public ActorComponent
{
	bool m_bCheck;

public:
	CPtr<GameActor> m_Actor_Top_Border;
	CPtr<GameActor> m_Actor_Bot_Border;

	CPtr<GameSpriteRenderer> m_Render_Top_Border;
	CPtr<GameSpriteRenderer> m_Render_Bot_Border;

	float m_Time;

	BORDER_TRIGGER_STATE m_BorderState;
	GameString m_BorderStateName[(UINT)BORDER_TRIGGER_STATE::MAX];

public:
	void ChangeState(BORDER_TRIGGER_STATE _State);

public:
	void Move(const CVector& _Dir, float _Speed);
	void Join(CPtr<GameTransform> _Parent);
	void Withdraw();

public:
	void Idle();
	void On();
	void Off();
	void Run();

public:
	void Init() override;
	void Update() override;

public:
	UICam();
	~UICam();
};

#define	TOP_BORDER_START_POS_Y 3.0f
#define BOT_BORDER_START_POS_Y -3.0f

#define TOP_BORDER_FINAL_POS_Y 2.0f
#define BOT_BORDER_FINAL_POS_Y -2.0f

#define BORDER_MOV_SPEED 1.0f
#define BORDER_TIME_DEFAULT 1.5f
