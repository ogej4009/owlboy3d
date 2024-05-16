#pragma once
#include "GameUnity.h"
class Air : public ActorComponent
{
	float m_Speed;
	float m_Alpha;
	float m_Time;
	CVector m_FrameRange;
	CVector m_Pos;
	CPtr<GameSpriteRenderer> m_Render;

public:
	void Move(const CVector& _Dir, float _Speed);
	void CalRand();
	void GetStageInfo();
	void Reset();

public:
	void Init() override;
	void Update() override;

public:
	Air();
	~Air();
};
#define AIR_ALPHA_DEFAULT_VALUE 100.0f
#define AIR_SPEED 0.5f