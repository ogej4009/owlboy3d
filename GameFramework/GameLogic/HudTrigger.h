#pragma once
#include "GameUnity.h"

enum class HUDTRIGGERSTATE
{
	HUD_IDLE,
	HUD_ON,
	HUD_OFF,
	HUD_RUN,
	MAX,
};

class HudTrigger : public ActorComponent
{
	static CPtr<GameTexture> m_Tex;
	
	CPtr<GameSpriteRenderer> m_Render;
	CPtr<GameAnimation> m_Anim;
	CPtr<GameTransform> m_Trans;
	GameString m_Name;

	float m_Delay;
	float m_Alpha;

	HUDTRIGGERSTATE m_State;
	GameString m_StateName[(UINT)HUDTRIGGERSTATE::MAX];

public:
	void SetHudTrans(CPtr<GameTransform> _HudTrans)
	{
		m_Trans = _HudTrans;
	}
	
	CPtr<GameTransform> GetHudTrans()
	{
		return m_Trans;
	}

	void SetHudRender(CPtr<GameSpriteRenderer> _HudRender)
	{
		m_Render = _HudRender;
	}

	CPtr<GameSpriteRenderer> GetHudRender()
	{
		return m_Render;
	}

	void SetHudName(GameString _HudName)
	{
		m_Name = _HudName;
	}

	GameString GetHudName()
	{
		return m_Name;
	}

public:
	void ChangeState(HUDTRIGGERSTATE _State);
	void Move(const CVector& _Dir, float _Speed);

public:
	void Idle();
	void On();
	void Off();
	void Run();

public:
	void Init() override;
	void Init(GameString _Name);
	void Update() override;

public:
	HudTrigger();
	~HudTrigger();
};

#define HUD_DELAY_TIME_DEFAULT 1.0f
#define HUD_ALPHA_MAX 1.0f
#define HUD_ALPHA_MIN 0.0f
#define HUD_UP_DOWN_SPEED 0.5f
