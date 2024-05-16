#pragma once
#include "GameUnity.h"

enum class CURSORSTATE
{
	IDLE,
	PICKUP_AIMING,
	SHOOTING,
	MAX,
};

class Cursor : public ActorComponent
{
	CURSORSTATE m_State;
	GameString	m_StateName[(UINT)CURSORSTATE::MAX];

	CPtr<GameCamera> m_Cam;
	CPtr<GameSpriteRenderer> m_Render;
	CPtr<GameAnimation> m_Anim;
	CPtr<GameCol> m_Col;
	CPtr<GameSpriteRenderer> m_ColRender;

	CVector m_Pos;
	CVector m_Scale;
	float m_Time;

	bool m_bPickUp;
	bool m_bShot;
	CVector m_HeroPos;

public:
	void Fit();
	void CheckState();

public:
	void ChangeState(CURSORSTATE _State);

public:
	void Idle();
	void PickUpAiming();
	void Shooting();

public:
	void Init() override;
	void Update() override;

public:
	Cursor();
	~Cursor();
};

#define CURSOR_DEFAULT_TIME_LIMIT 1.0f
#define CURSOR_IMG_SIZE_MAX 1000.0f