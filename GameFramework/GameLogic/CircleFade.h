#pragma once
#include "Fade.h"
class CircleFade : public Fade
{
	CPtr<GameSpriteRenderer> m_Render;
	float m_Speed;

public:
	void FadeIn() override // Ŀ����
	{
		m_Mode = FADEIO::FADEIN;
		m_Speed = 1.0f; // ī�޶� ����
	}

	void FadeOut() override // �۾�����. 
	{
		m_Mode = FADEIO::FADEOUT;
		m_Speed = 0.0f; // ī�޶� ����
	}

	void Move(const CVector& _Dir, float _Speed);

public:
	void Init() override;
	void Update() override;

public:
	CircleFade();
	~CircleFade();
};