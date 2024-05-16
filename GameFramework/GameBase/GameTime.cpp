#include "GameTime.h"

GameTime::GameTimer GameTime::MainTimer = GameTime::GameTimer();

//////////////////////////// 추가했습니다. 
float GameTime::BulletTime = 1.0f;


GameTime::GameTimer::GameTimer()
{
	CountStart();
}

GameTime::GameTimer::~GameTimer()
{
}

#pragma region 타이머객체사용법
/*
	GameTimer NewTimer;		타이머 객체를 만들었다
	NewTimer.CountStart();	A->B 순간의 시간을 재는 함수이다.
	NewTimer.TimeCheck();	실행한 순간까지의 데이터로 델타타임을 결정
*/
#pragma endregion

void GameTime::GameTimer::CountStart()
{
	QueryPerformanceFrequency(&m_CountTime);	// 현재까지 센 시간,  카운팅된 시간
	QueryPerformanceCounter(&m_CurTime);		// 현재시간을 알 수있다는 것은 디버깅 중에도 동작한다는 것이다. (언제나) 
	QueryPerformanceCounter(&m_PrevTime);
}

#pragma region DeltaTime
/*
	델타타임 = CurTime - PrevTime / CountTime;

	시간을 잴 때, double 자료형을 쓴 이유를 유추하면, 최대한 정밀하게 계산하기 위해서 한 것
	double dDeltaTime : double은 정밀하지만 무겁다.
	float fDeltaTime : 사용할 때는 float이 편하다. 여기저기 넣을 수 있다.

	보통 굉장히 작은 수가 나온다.
	1000번 실행됐다고 하면, 1초안에 1000번 실행되면, 결과로 0.001나오게 된다.
	즉 컴퓨터의 성능이 좋을수록 시간을 재면, 간격이 작고, 더 작은 수가 나온다.
*/
#pragma endregion


void GameTime::GameTimer::TimeCheck()
{
	QueryPerformanceCounter(&m_CurTime);
	dDeltaTime = ((double)m_CurTime.QuadPart - (double)m_PrevTime.QuadPart) / (double)m_CountTime.QuadPart;
	m_PrevTime.QuadPart = m_CurTime.QuadPart;	// <-- 이렇게 해서 다음 연산을 대비한다. 
	fDeltaTime = (float)dDeltaTime;

	//// 	fDeltaTime = (float)dDeltaTime * BulletTime;
}

void GameTime::Update()
{
	// 계속 실행해준다.
	MainTimer.TimeCheck();
}

#pragma region TIME RESET
/*
	최초 한 번 실행
	혹은
	어떤 새로운 씬을 만드는 순간, 1번만 실행
*/
#pragma endregion

void GameTime::TimeReset()
{
	MainTimer.CountStart();
}

GameTime::GameTime() {}
GameTime::~GameTime() {}