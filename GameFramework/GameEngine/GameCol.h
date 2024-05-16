#pragma once
#include "GameTransform.h"
#include <unordered_set>
#include <functional>
#include <list>
#include <GameDebug.h>


#pragma region 충돌is트랜스폼
/*
	GameCol 자신이 상속관계로 트랜스폼이므로
	_ljTransData	m_TD
	이 멤버를 가지고 있다.
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
		일반적으로 레드블랙트리인 셋보다 빠르다.
		긴 문자열인 경우에는 너무 신경쓸 필요는 없다.
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
			MSG_ASSERT_CODE(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		m_EnterFunc.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1, std::placeholders::_2));
	}

	template<typename T>
	void PushStayFunc(T* _Obj, void(T::* _Ptr)(GameCol*, GameCol*))
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		m_StayFunc.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1, std::placeholders::_2));

	}

	template<typename T>
	void PushExitFunc(T* _Obj, void(T::* _Ptr)(GameCol*, GameCol*))
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		m_ExitFunc.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1, std::placeholders::_2));

	}

	void PushEnterFunc(void(*_Ptr)(GameCol*, GameCol*))
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		m_EnterFunc.push_back(std::bind(_Ptr, std::placeholders::_1, std::placeholders::_2));
	}

	void PushStayFunc(void(*_Ptr)(GameCol*, GameCol*))
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		m_StayFunc.push_back(std::bind(_Ptr, std::placeholders::_1, std::placeholders::_2));
	}

	void PushExitFunc(void(*_Ptr)(GameCol*, GameCol*)) {
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
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

