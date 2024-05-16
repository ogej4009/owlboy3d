#include "Air.h"
#include "EnumData.h"
#include "ValueData.h"

void Air::Move(const CVector& _Dir, float _Speed)
{
	GetTrans()->WMove(_Dir * GameTime::DeltaTime(_Speed));
}

void Air::CalRand()
{
	//srand((unsigned int)time(nullptr));
	int RandomNum = rand() % 20;

	if (RandomNum != 0)
	{
		m_Speed = RandomNum * 0.1f;
	}
	else
	{
		m_Speed = (RandomNum + 1) * 0.1f;
	}
}

void Air::GetStageInfo()
{
	// 프레임범위를 가져온다. 
	m_FrameRange = ValueData::STAGE_SCALE;

	// 저장등록된 위치를 가져온다. 
	// m_Pos = ;
}

void Air::Reset()
{
	m_Alpha = AIR_ALPHA_DEFAULT_VALUE;
	GetTrans()->SetWPos(m_Pos);
}

void Air::Init()
{
	m_Render = GetActor()->FindComType<GameSpriteRenderer>();

	if (nullptr == m_Render)
	{
		MSG_ASSERT_CODE(L"값이 null입니다.");
	}

	GetStageInfo();

}

void Air::Update()
{
	// 엣지부분과 충돌하면 알파값이 줄어든다. 
	// 프레임에서 벗어나면 알파값 0 
	// 리셋한다. 알파값 , 위치, 
	//if ()
	//{
	//m_Alpha -= GameTime::DeltaTime();
	//m_Render->SetAlpha(m_Alpha);
	//}

	// 이동범위설정 


	// 기본 속도 설정 
	// 기본 방향 설정 
	Move(CVector::RIGHT, m_Speed);
}

Air::Air() {}
Air::~Air() {}