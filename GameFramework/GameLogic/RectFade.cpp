#include "RectFade.h"
#include "GameTime.h"
void RectFade::Init()
{
	m_Render = GetActor()->FindComType<GameSpriteRenderer>();

	if (nullptr == m_Render)
	{
		MSG_ASSERT_CODE(L"Renderer의 값이 null이므로 이 효과를 사용할 수 없습니다.");
	}

	m_Mode = FADEIO::MAX;
}

void RectFade::Update()
{
	switch (m_Mode)
	{
	case FADEIO::FADEIN:
		if (0 >= m_Alpha)
		{
			m_Mode = FADEIO::MAX;
		}
		m_Alpha += GameTime::DeltaTime(0.01f);
		m_Render->SetAlpha(m_Alpha);
		m_Render->Off();
		break;
	case FADEIO::FADEOUT:
		if (1 < m_Alpha)
		{
			m_Mode = FADEIO::MAX;
		}
		m_Alpha -= GameTime::DeltaTime(0.01f);
		m_Render->SetAlpha(m_Alpha);
		m_Render->Off();
		break;
	case FADEIO::MAX:
		break;
	default:
		break;
	}
}

RectFade::RectFade() {}
RectFade::~RectFade() {}