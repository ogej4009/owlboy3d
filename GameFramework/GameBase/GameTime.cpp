#include "GameTime.h"

GameTime::GameTimer GameTime::MainTimer = GameTime::GameTimer();

//////////////////////////// �߰��߽��ϴ�. 
float GameTime::BulletTime = 1.0f;


GameTime::GameTimer::GameTimer()
{
	CountStart();
}

GameTime::GameTimer::~GameTimer()
{
}

#pragma region Ÿ�̸Ӱ�ü����
/*
	GameTimer NewTimer;		Ÿ�̸� ��ü�� �������
	NewTimer.CountStart();	A->B ������ �ð��� ��� �Լ��̴�.
	NewTimer.TimeCheck();	������ ���������� �����ͷ� ��ŸŸ���� ����
*/
#pragma endregion

void GameTime::GameTimer::CountStart()
{
	QueryPerformanceFrequency(&m_CountTime);	// ������� �� �ð�,  ī���õ� �ð�
	QueryPerformanceCounter(&m_CurTime);		// ����ð��� �� ���ִٴ� ���� ����� �߿��� �����Ѵٴ� ���̴�. (������) 
	QueryPerformanceCounter(&m_PrevTime);
}

#pragma region DeltaTime
/*
	��ŸŸ�� = CurTime - PrevTime / CountTime;

	�ð��� �� ��, double �ڷ����� �� ������ �����ϸ�, �ִ��� �����ϰ� ����ϱ� ���ؼ� �� ��
	double dDeltaTime : double�� ���������� ���̴�.
	float fDeltaTime : ����� ���� float�� ���ϴ�. �������� ���� �� �ִ�.

	���� ������ ���� ���� ���´�.
	1000�� ����ƴٰ� �ϸ�, 1�ʾȿ� 1000�� ����Ǹ�, ����� 0.001������ �ȴ�.
	�� ��ǻ���� ������ �������� �ð��� ���, ������ �۰�, �� ���� ���� ���´�.
*/
#pragma endregion


void GameTime::GameTimer::TimeCheck()
{
	QueryPerformanceCounter(&m_CurTime);
	dDeltaTime = ((double)m_CurTime.QuadPart - (double)m_PrevTime.QuadPart) / (double)m_CountTime.QuadPart;
	m_PrevTime.QuadPart = m_CurTime.QuadPart;	// <-- �̷��� �ؼ� ���� ������ ����Ѵ�. 
	fDeltaTime = (float)dDeltaTime;

	//// 	fDeltaTime = (float)dDeltaTime * BulletTime;
}

void GameTime::Update()
{
	// ��� �������ش�.
	MainTimer.TimeCheck();
}

#pragma region TIME RESET
/*
	���� �� �� ����
	Ȥ��
	� ���ο� ���� ����� ����, 1���� ����
*/
#pragma endregion

void GameTime::TimeReset()
{
	MainTimer.CountStart();
}

GameTime::GameTime() {}
GameTime::~GameTime() {}