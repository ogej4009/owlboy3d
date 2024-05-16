#include "CircleFade.h"
#include "GameTime.h"
void CircleFade::Move(const CVector& _Dir, float _Speed)
{
	GetTrans()->WMove(_Dir * GameTime::DeltaTime(_Speed));
}

void CircleFade::Init()
{
	m_Render = GetActor()->FindComType<GameSpriteRenderer>();

	if (nullptr == m_Render)
	{
		MSG_ASSERT_CODE(L"Renderer의 값이 null이므로 이 효과를 사용할 수 없습니다.");
	}

	m_Mode = FADEIO::MAX;
}

void CircleFade::Update()
{
	switch (m_Mode)
	{
	case FADEIO::FADEIN:
		if (0 >= m_Speed)
		{
			m_Mode = FADEIO::MAX;
		}
		Move(CVector::FORWARD, m_Speed);
		/*m_Speed += GameTime::DeltaTime(0.01f);
		m_Render->SetAlpha(m_Speed);
		m_Render->Off();*/
		break;
	case FADEIO::FADEOUT:
		if (1 < m_Speed)
		{
			m_Mode = FADEIO::MAX;
		}
		Move(CVector::BACK, m_Speed);
		/*m_Speed -= GameTime::DeltaTime(0.01f);
		m_Render->SetAlpha(m_Speed);
		m_Render->Off();*/
		break;
	case FADEIO::MAX:
		break;
	default:
		break;
	}
}

CircleFade::CircleFade() {}
CircleFade::~CircleFade() {}