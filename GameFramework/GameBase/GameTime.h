#pragma once
#include <Windows.h>


#pragma region 델타타임
/*

	CPU에 타이머 기능이 내장되어있다. 프로그램(APP)은 이 타이머와 무관하다.
	2가지가 있다.

	1초 당 셀 수 있는 시간(셈) == 1초 단위로 셈을 할 수 있는 수 == 능력
	어떤 컴퓨터가 고정적으로 1초에 100을 셈할 수 있다

	1초 당 셀 수 있는 시간(셈)으로 처음부터 원하는 시간까지 셈을 한 시간(셈)을 알 수 있다. == 결과
	1초당 100을 셀 수 있다면
	1초동안 숫자를 세었다면 100
	2초동안 숫자를 세었다면 200
	두가지의 사실을 모두 알수있는 함수가 있다.

	기저 ) <시간>이라는 개념을 <셈>을 할 것이다.

	1) 초 당 셀 수있는 시간을 계산하는 함수
	2) 현재까지 셈을 한 시간을 모두 계산해주는 함수

	CountTime	= 1초 당 셀 수 있는 시간		100		== 셀수 있는 능력
	CurTime		= 현재까지 (셈)시간				0		== 셈을 한 결과 리포트 1
	PrevTime	= 현재까지 (셈)시간				0		== 셈을 한 결과 리포트 2

	------------ 1초 후 ------------

	CurTime		= 현재까지 (셈)시간				100
	PrevTime	=

			   100       0        / 100
	델타타임 = CurTime - PrevTime / CountTime; == 	1.0F
	그리고 이 계산이 끝나면 PrevTime = CurTime; <-- 이렇게 해서 다음 연산을 대비한다.

	------------ 0.5초 후 ------------

	CurTime		= 현재까지 (셈)시간				150
	PrevTime	=								100

			   150       100      / 100
	델타타임 = CurTime - PrevTime / CountTime; == 	0.5F
	그리고 이 계산이 끝나면 PrevTime = CurTime; <-- 이렇게 해서 다음 연산을 대비한다.

	[셈을 한 결과 리포트 1 - 셈을 한 결과 리포트 2] / 셀수 있는 능력 == (1초 당~이였으므로) ???초 라는 결과가 나옴

	델타타임 1.0F는 1초를 의미하게 된다.
	즉, 실제 시간을 실수로 변환한것이 델타타임이다.

	A컴퓨터: 1초에 1번 게임데드타임함수가 돌아간다.
	B컴퓨터: 1초에 2번 게임데드타임함수가 돌아간다.

	같은 게임에서 캐릭터의 이동속력이 1이라면
	A는 초당 1을 이동한다.
	B는 초당 2를 이동한다.

	둘다 1초 움직였을때 공평하게 1을 이용하게 하려면

	A 의 이동량 = 1 * 1(델타타임) = 1;
	B 의 이동량 = 1 * 0.5F(델타타임) + 1 * 0.5F(델타타임) = 1;


*/
#pragma endregion


class GameTime
{

public:
	class GameTimer
	{
		friend GameTime;
	private:
		LARGE_INTEGER m_CountTime; // 초당 셀 수 있는 시간
		LARGE_INTEGER m_CurTime;
		LARGE_INTEGER m_PrevTime;
		double dDeltaTime; // 8 바이트 실수 
		float fDeltaTime; // 4 바이트 실수

	public:
		void CountStart();
		void TimeCheck();

	public:
		GameTimer();
		~GameTimer();
	};
private:
	static GameTimer MainTimer;

	/////////////////////////// 추가했습니다. 
	static float BulletTime;


#pragma region 
	/*
		GameTime은 MainTimer를 하나 두고,
		그걸 메인시간으로 해서 모든 게임에 관련된 객체나 코드들이 그것을 이용한다.
	*/
#pragma endregion

public:
	static float DeltaTime(float _Speed = 1.0f)
	{
		return MainTimer.fDeltaTime * _Speed;
	}

	static float DeltaTimeAccel(float _Speed, float _Accel)
	{
		return MainTimer.fDeltaTime * MainTimer.fDeltaTime * _Accel * 0.5f + MainTimer.fDeltaTime * _Speed;
	}

public:
	static void TimeReset();
	static void Update();

public:
	GameTime();
	~GameTime();
};