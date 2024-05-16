#pragma once
#include "GameSpriteRenderer.h"

class GameAnimation : public ActorComponent
{

public:
	CPtr<GameSpriteRenderer> m_SpriteRenderer;

public:
	void Init(CPtr<GameSpriteRenderer> SpriteRender = nullptr); // nullptr이어야 한다. 
	void Update() override;

private:
	class CGameAni : public CRef
	{
	public:
		GameActor* Actor;// ★ B타입(메탈)
		GameString m_AnimName;
		GameString m_SpriteName;
		unsigned int m_Start;
		unsigned int m_End;
		float m_FrameTime;
		bool m_Loop;
		unsigned int m_CurFrame;
		float m_CurFrameTime;

		std::map<unsigned int, std::list<std::function<void(GameActor* _Actor)>>> m_StartFunc;// ★
		std::map<unsigned int, std::list<std::function<void(GameActor* _Actor)>>> m_EndFunc;// ★

	public:
		void CheckStartFunc(unsigned int _Frame)// ★
		{
			if (m_StartFunc.end() == m_StartFunc.find(_Frame))
			{
				return;
			}

			for (auto& _Var : m_StartFunc[_Frame])
			{
				_Var(Actor);
			}
		}

		void CheckEndFunc(unsigned int _Frame)// ★
		{
			if (m_EndFunc.end() == m_EndFunc.find(_Frame))
			{
				return;
			}

			for (auto& _Var : m_EndFunc[_Frame])
			{
				_Var(Actor);
			}
		}


	public:
		bool IsReverse()// ★
		{
			return m_Start > m_End;
		}

		void Reset()
		{
			m_CurFrame = m_Start;
			m_CurFrameTime = m_FrameTime;
		}

	};

private:
	std::map<GameString, CPtr<CGameAni>> m_Anim;
	CPtr<CGameAni> m_CurAni;
	bool IsAniEndOff;
	bool m_IsEnd;

public:
	bool IsAniEnd()
	{
		return m_IsEnd;
	}

public:
	bool CurAniEnd() // ★
	{
		return m_CurAni->m_CurFrame == m_CurAni->m_End;
	}

	unsigned int CurAniFrame() // ★
	{
		return m_CurAni->m_CurFrame;
	}

public:
	// 어떤 애니메이션 "IDLE"
	// 어떤 프레임     5
	template<typename T>
	void PushStartFunc(const GameString& _AniName, unsigned int _Frame, T* _Obj, void(T::* _Ptr)(GameActor*))// ★
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr인 함수를 넣어줬습니다. 실행할 수 없습니다.");
		}

		CPtr<CGameAni> pAni = FindAni(_AniName);

		if (nullptr == pAni)
		{
			MSG_ASSERT_CODE(L"존재하지 않는 애니메이션에 콜백을 넣을수 없습니다.");
		}

		std::map<unsigned int, std::list<std::function<void(GameActor* _Actor)>>>::iterator FindIter
			= pAni->m_StartFunc.find(_Frame);

		// 먼저 저 프레임에 자료구조가 있는지 봐야한다.
		if (pAni->m_StartFunc.end() == FindIter)
		{
			// 없으면 그 프레임은 일단 만든다.
			// 무조건 만들어지게 된다.
			pAni->m_StartFunc[_Frame] = std::list<std::function<void(GameActor* _Actor)>>();
			FindIter = pAni->m_StartFunc.find(_Frame);
		}

		FindIter->second.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1));
	}

	void PushStartFunc(const GameString& _AniName, unsigned int _Frame, void(*_Ptr)(GameActor*))// ★
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		CPtr<CGameAni> pAni = FindAni(_AniName);
		if (nullptr == pAni)
		{
			MSG_ASSERT_CODE(L"존재하지 않는 애니메이션에 콜백을 넣을수 없습니다.");
		}
		std::map<unsigned int, std::list<std::function<void(GameActor* _Actor)>>>::iterator FindIter
			= pAni->m_StartFunc.find(_Frame);

		// 먼저 저 프레임에 자료구조가 있는지 봐야한다.
		if (pAni->m_StartFunc.end() == FindIter)
		{
			// 없으면 그 프레임은 일단 만든다.
			// 무조건 만들어지게 된다.
			pAni->m_StartFunc[_Frame] = std::list<std::function<void(GameActor* _Actor)>>();
			FindIter = pAni->m_StartFunc.find(_Frame);
		}

		FindIter->second.push_back(std::bind(_Ptr, std::placeholders::_1));
	}

	template<typename T>
	void PushEndFunc(const GameString& _AniName, unsigned int _Frame, T* _Obj, void(T::* _Ptr)(GameActor*))// ★
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		CPtr<CGameAni> pAni = FindAni(_AniName);
		if (nullptr == pAni)
		{
			MSG_ASSERT_CODE(L"존재하지 않는 애니메이션에 콜백을 넣을수 없습니다.");
		}
		std::map<unsigned int, std::list<std::function<void(GameActor* _Actor)>>>::iterator FindIter
			= pAni->m_EndFunc.find(_Frame);

		// 먼저 저 프레임에 자료구조가 있는지 봐야한다.
		if (pAni->m_EndFunc.end() == FindIter)
		{
			// 없으면 그 프레임은 일단 만든다.
			// 무조건 만들어지게 된다.
			pAni->m_EndFunc[_Frame] = std::list<std::function<void(GameActor* _Actor)>>();
			FindIter = pAni->m_EndFunc.find(_Frame);
		}

		FindIter->second.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1));
	}

	void PushEndFunc(const GameString& _AniName, unsigned int _Frame, void(*_Ptr)(GameActor*))// ★
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		CPtr<CGameAni> pAni = FindAni(_AniName);
		if (nullptr == pAni)
		{
			MSG_ASSERT_CODE(L"존재하지 않는 애니메이션에 콜백을 넣을수 없습니다.");
		}
		std::map<unsigned int, std::list<std::function<void(GameActor* _Actor)>>>::iterator FindIter
			= pAni->m_EndFunc.find(_Frame);

		// 먼저 저 프레임에 자료구조가 있는지 봐야한다.
		if (pAni->m_EndFunc.end() == FindIter)
		{
			// 없으면 그 프레임은 일단 만든다.
			// 무조건 만들어지게 된다.
			pAni->m_EndFunc[_Frame] = std::list<std::function<void(GameActor* _Actor)>>();
			FindIter = pAni->m_EndFunc.find(_Frame);
		}

		FindIter->second.push_back(std::bind(_Ptr, std::placeholders::_1));
	}


private:
	CPtr<CGameAni> FindAni(const GameString& _AniName);// ★

public:
	void CreateAni(const GameString& _AniName
		, const GameString& _SpriteName
		, unsigned int _Start
		, unsigned int _End
		, float _FrameTime
		, bool _Loop);

	//bool EndAni();
	void ChangeAni(const GameString& _AniName);
	//void ChangeAni(const GameString& _AniName, bool _IsEndOff = false);
	//void ChangeAni(const GameString& _AniName, int _StartFrame, bool _IsEndOff = false);// ★
	//void ChangeAniReset(const GameString& _AniName, bool _IsEndOff = false);// ★

};