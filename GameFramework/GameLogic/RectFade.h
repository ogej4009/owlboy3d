#pragma once
#include "Fade.h"
class RectFade : public Fade
{
	CPtr<GameSpriteRenderer> m_Render;
	float m_Alpha;

public:
	void FadeIn() override // �� > ��
	{
		m_Mode = FADEIO::FADEIN;
		m_Alpha = 1.0f;
	}

	void FadeOut() override // �� > ��
	{
		m_Mode = FADEIO::FADEOUT;
		m_Alpha = 0.0f;
	}

public:
	void Init() override;
	void Update() override;

public:
	RectFade();
	~RectFade();

};

