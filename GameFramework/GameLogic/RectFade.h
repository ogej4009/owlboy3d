#pragma once
#include "Fade.h"
class RectFade : public Fade
{
	CPtr<GameSpriteRenderer> m_Render;
	float m_Alpha;

public:
	void FadeIn() override // พ๎ > นเ
	{
		m_Mode = FADEIO::FADEIN;
		m_Alpha = 1.0f;
	}

	void FadeOut() override // นเ > พ๎
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

