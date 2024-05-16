#pragma once
#include <Windows.h>


#pragma region ��ŸŸ��
/*

	CPU�� Ÿ�̸� ����� ����Ǿ��ִ�. ���α׷�(APP)�� �� Ÿ�̸ӿ� �����ϴ�.
	2������ �ִ�.

	1�� �� �� �� �ִ� �ð�(��) == 1�� ������ ���� �� �� �ִ� �� == �ɷ�
	� ��ǻ�Ͱ� ���������� 1�ʿ� 100�� ���� �� �ִ�

	1�� �� �� �� �ִ� �ð�(��)���� ó������ ���ϴ� �ð����� ���� �� �ð�(��)�� �� �� �ִ�. == ���
	1�ʴ� 100�� �� �� �ִٸ�
	1�ʵ��� ���ڸ� �����ٸ� 100
	2�ʵ��� ���ڸ� �����ٸ� 200
	�ΰ����� ����� ��� �˼��ִ� �Լ��� �ִ�.

	���� ) <�ð�>�̶�� ������ <��>�� �� ���̴�.

	1) �� �� �� ���ִ� �ð��� ����ϴ� �Լ�
	2) ������� ���� �� �ð��� ��� ������ִ� �Լ�

	CountTime	= 1�� �� �� �� �ִ� �ð�		100		== ���� �ִ� �ɷ�
	CurTime		= ������� (��)�ð�				0		== ���� �� ��� ����Ʈ 1
	PrevTime	= ������� (��)�ð�				0		== ���� �� ��� ����Ʈ 2

	------------ 1�� �� ------------

	CurTime		= ������� (��)�ð�				100
	PrevTime	=

			   100       0        / 100
	��ŸŸ�� = CurTime - PrevTime / CountTime; == 	1.0F
	�׸��� �� ����� ������ PrevTime = CurTime; <-- �̷��� �ؼ� ���� ������ ����Ѵ�.

	------------ 0.5�� �� ------------

	CurTime		= ������� (��)�ð�				150
	PrevTime	=								100

			   150       100      / 100
	��ŸŸ�� = CurTime - PrevTime / CountTime; == 	0.5F
	�׸��� �� ����� ������ PrevTime = CurTime; <-- �̷��� �ؼ� ���� ������ ����Ѵ�.

	[���� �� ��� ����Ʈ 1 - ���� �� ��� ����Ʈ 2] / ���� �ִ� �ɷ� == (1�� ��~�̿����Ƿ�) ???�� ��� ����� ����

	��ŸŸ�� 1.0F�� 1�ʸ� �ǹ��ϰ� �ȴ�.
	��, ���� �ð��� �Ǽ��� ��ȯ�Ѱ��� ��ŸŸ���̴�.

	A��ǻ��: 1�ʿ� 1�� ���ӵ���Ÿ���Լ��� ���ư���.
	B��ǻ��: 1�ʿ� 2�� ���ӵ���Ÿ���Լ��� ���ư���.

	���� ���ӿ��� ĳ������ �̵��ӷ��� 1�̶��
	A�� �ʴ� 1�� �̵��Ѵ�.
	B�� �ʴ� 2�� �̵��Ѵ�.

	�Ѵ� 1�� ���������� �����ϰ� 1�� �̿��ϰ� �Ϸ���

	A �� �̵��� = 1 * 1(��ŸŸ��) = 1;
	B �� �̵��� = 1 * 0.5F(��ŸŸ��) + 1 * 0.5F(��ŸŸ��) = 1;


*/
#pragma endregion


class GameTime
{

public:
	class GameTimer
	{
		friend GameTime;
	private:
		LARGE_INTEGER m_CountTime; // �ʴ� �� �� �ִ� �ð�
		LARGE_INTEGER m_CurTime;
		LARGE_INTEGER m_PrevTime;
		double dDeltaTime; // 8 ����Ʈ �Ǽ� 
		float fDeltaTime; // 4 ����Ʈ �Ǽ�

	public:
		void CountStart();
		void TimeCheck();

	public:
		GameTimer();
		~GameTimer();
	};
private:
	static GameTimer MainTimer;

	/////////////////////////// �߰��߽��ϴ�. 
	static float BulletTime;


#pragma region 
	/*
		GameTime�� MainTimer�� �ϳ� �ΰ�,
		�װ� ���νð����� �ؼ� ��� ���ӿ� ���õ� ��ü�� �ڵ���� �װ��� �̿��Ѵ�.
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