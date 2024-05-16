#pragma once
#include "GameTransform.h"
#include <unordered_set>
#include <functional>
#include <list>
#include <GameDebug.h>


#pragma region �浹isƮ������
/*
	GameCol �ڽ��� ��Ӱ���� Ʈ�������̹Ƿ�
	_ljTransData	m_TD
	�� ����� ������ �ִ�.
*/
#pragma endregion


class GameCol : public GameTransform
{
private:
	COLTYPE m_Type;
	int ColOrder;

public:
	void SetColOrder(int _Order)
	{
		ColOrder = _Order;
	}

	int GetColOrder()
	{
		return ColOrder;
	}

public:
	void ColType(COLTYPE _Type)
	{
		m_Type = _Type;
	}


private:
#pragma region std::unordered_set
	/*
		�Ϲ������� �����Ʈ���� �º��� ������.
		�� ���ڿ��� ��쿡�� �ʹ� �Ű澵 �ʿ�� ����.
	*/
#pragma endregion
	std::unordered_set<GameCol*> m_ColSet;

private:
	std::list<std::function<void(GameCol*, GameCol*)>> m_EnterFunc;
	std::list<std::function<void(GameCol*, GameCol*)>> m_StayFunc;
	std::list<std::function<void(GameCol*, GameCol*)>> m_ExitFunc;

public:
	template<typename T>
	void PushEnterFunc(T* _Obj, void(T::* _Ptr)(GameCol*, GameCol*))
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
		}

		m_EnterFunc.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1, std::placeholders::_2));
	}

	template<typename T>
	void PushStayFunc(T* _Obj, void(T::* _Ptr)(GameCol*, GameCol*))
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
		}

		m_StayFunc.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1, std::placeholders::_2));

	}

	template<typename T>
	void PushExitFunc(T* _Obj, void(T::* _Ptr)(GameCol*, GameCol*))
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
		}

		m_ExitFunc.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1, std::placeholders::_2));

	}

	void PushEnterFunc(void(*_Ptr)(GameCol*, GameCol*))
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
		}

		m_EnterFunc.push_back(std::bind(_Ptr, std::placeholders::_1, std::placeholders::_2));
	}

	void PushStayFunc(void(*_Ptr)(GameCol*, GameCol*))
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
		}

		m_StayFunc.push_back(std::bind(_Ptr, std::placeholders::_1, std::placeholders::_2));
	}

	void PushExitFunc(void(*_Ptr)(GameCol*, GameCol*)) {
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
		}

		m_ExitFunc.push_back(std::bind(_Ptr, std::placeholders::_1, std::placeholders::_2));
	}

private:
	void CallEnter(GameCol* _Other);
	void CallStay(GameCol* _Other);
	void CallExit(GameCol* _Other);

public:
	void ColCheck(CPtr<GameCol> _Other);
	void Release() override;
	void Off() override;

public:
	void Init(int _Order);

public:
	bool IsMouse;

public:
	DirectX::SimpleMath::Ray RAY3D() override;

public:
	GameCol();
	~GameCol();

};

