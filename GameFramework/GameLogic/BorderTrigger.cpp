#include "BorderTrigger.h"
#include "EnumData.h"
#include "ValueData.h"
void BorderTrigger::Move(const CVector& _Dir, float _Speed)
{
	GetTrans()->WMove(_Dir * GameTime::DeltaTime(_Speed));
}

void BorderTrigger::Init()
{
	m_Render = GetActor()->FindComType<GameSpriteRenderer>();

	if (nullptr == m_Render)
	{
		MSG_ASSERT_CODE(L"Renderer의 값이 null이므로 이 효과를 사용할 수 없습니다.");
	}
}

void BorderTrigger::Update()
{
}

BorderTrigger::BorderTrigger()
{
}

BorderTrigger::~BorderTrigger()
{
}
