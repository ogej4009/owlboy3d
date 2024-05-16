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
	// �����ӹ����� �����´�. 
	m_FrameRange = ValueData::STAGE_SCALE;

	// �����ϵ� ��ġ�� �����´�. 
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
		MSG_ASSERT_CODE(L"���� null�Դϴ�.");
	}

	GetStageInfo();

}

void Air::Update()
{
	// �����κа� �浹�ϸ� ���İ��� �پ���. 
	// �����ӿ��� ����� ���İ� 0 
	// �����Ѵ�. ���İ� , ��ġ, 
	//if ()
	//{
	//m_Alpha -= GameTime::DeltaTime();
	//m_Render->SetAlpha(m_Alpha);
	//}

	// �̵��������� 


	// �⺻ �ӵ� ���� 
	// �⺻ ���� ���� 
	Move(CVector::RIGHT, m_Speed);
}

Air::Air() {}
Air::~Air() {}