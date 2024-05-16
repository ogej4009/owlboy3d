#pragma once
#include "GameUnity.h"

enum class UITRIGGERSTATE
{
	UI_IDLE,
	UI_ON,
	UI_OFF,
	UI_RUN,
	MAX,
};

enum class UITRIGGERDIR
{
	UI_R,
	UI_L,
	MAX,
};

class UITrigger : public ActorComponent
{
	static CPtr<GameTexture> m_Tex;
	CPtr<GameSpriteRenderer> m_Render;
	CPtr<GameAnimation> m_Anim;
	CPtr<GameTransform> m_Trans;
	GameString m_Name;

	float m_Delay;
	float m_Alpha;

	UINT m_Dir;

	UITRIGGERSTATE m_State;
	GameString m_StateName[(UINT)UITRIGGERSTATE::MAX];

public:
	void SetUITrans(CPtr<GameTransform> _UITrans)
	{
		m_Trans = _UITrans;
	}

	CPtr<GameTransform> GetUITrans()
	{
		return m_Trans;
	}

	void SetUIRender(CPtr<GameSpriteRenderer> _UIRender)
	{
		m_Render = _UIRender;
	}

	CPtr<GameSpriteRenderer> GetUIRender()
	{
		return m_Render;
	}

	void SetUIName(GameString _UIName)
	{
		m_Name = _UIName;
	}

	GameString GetUIName()
	{
		return m_Name;
	}

public:
	void ChangeState(UITRIGGERSTATE _State);
	void Move(const CVector& _Dir, float _Speed);

public:
	void Idle();
	void On();
	void Off();
	void Run();

public:
	void Init() override;
	//void Init(const GameString& _SprName, float _Speed, int _Start, int _End, bool _Chk);
	void Init(GameString _Name, UINT _Dir);
	void Update() override;

public:
	UITrigger();
	~UITrigger();
};

#define UI_DELAY_TIME_DEFAULT 1.0f
#define UI_ALPHA_MAX 1.0f
#define UI_ALPHA_MIN 0.0f
#define UI_TRIGGER_MOVE_SPEED 0.5f
