#pragma once
#include "Fade.h"
class CircleFade : public Fade
{
	CPtr<GameSpriteRenderer> m_Render;
	float m_Speed;

public:
	void FadeIn() override // 커진다
	{
		m_Mode = FADEIO::FADEIN;
		m_Speed = 1.0f; // 카메라 조절
	}

	void FadeOut() override // 작아진다. 
	{
		m_Mode = FADEIO::FADEOUT;
		m_Speed = 0.0f; // 카메라 조절
	}

	void Move(const CVector& _Dir, float _Speed);

public:
	void Init() override;
	void Update() override;

public:
	CircleFade();
	~CircleFade();
};