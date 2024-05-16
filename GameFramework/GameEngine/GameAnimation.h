#pragma once
#include "GameSpriteRenderer.h"

class GameAnimation : public ActorComponent
{

public:
	CPtr<GameSpriteRenderer> m_SpriteRenderer;

public:
	void Init(CPtr<GameSpriteRenderer> SpriteRender = nullptr); // nullptr�̾�� �Ѵ�. 
	void Update() override;

private:
	class CGameAni : public CRef
	{
	public:
		GameActor* Actor;// �� BŸ��(��Ż)
		GameString m_AnimName;
		GameString m_SpriteName;
		unsigned int m_Start;
		unsigned int m_End;
		float m_FrameTime;
		bool m_Loop;
		unsigned int m_CurFrame;
		float m_CurFrameTime;

		std::map<unsigned int, std::list<std::function<void(GameActor* _Actor)>>> m_StartFunc;// ��
		std::map<unsigned int, std::list<std::function<void(GameActor* _Actor)>>> m_EndFunc;// ��

	public:
		void CheckStartFunc(unsigned int _Frame)// ��
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

		void CheckEndFunc(unsigned int _Frame)// ��
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
		bool IsReverse()// ��
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
	bool CurAniEnd() // ��
	{
		return m_CurAni->m_CurFrame == m_CurAni->m_End;
	}

	unsigned int CurAniFrame() // ��
	{
		return m_CurAni->m_CurFrame;
	}

public:
	// � �ִϸ��̼� "IDLE"
	// � ������     5
	template<typename T>
	void PushStartFunc(const GameString& _AniName, unsigned int _Frame, T* _Obj, void(T::* _Ptr)(GameActor*))// ��
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr�� �Լ��� �־�����ϴ�. ������ �� �����ϴ�.");
		}

		CPtr<CGameAni> pAni = FindAni(_AniName);

		if (nullptr == pAni)
		{
			MSG_ASSERT_CODE(L"�������� �ʴ� �ִϸ��̼ǿ� �ݹ��� ������ �����ϴ�.");
		}

		std::map<unsigned int, std::list<std::function<void(GameActor* _Actor)>>>::iterator FindIter
			= pAni->m_StartFunc.find(_Frame);

		// ���� �� �����ӿ� �ڷᱸ���� �ִ��� �����Ѵ�.
		if (pAni->m_StartFunc.end() == FindIter)
		{
			// ������ �� �������� �ϴ� �����.
			// ������ ��������� �ȴ�.
			pAni->m_StartFunc[_Frame] = std::list<std::function<void(GameActor* _Actor)>>();
			FindIter = pAni->m_StartFunc.find(_Frame);
		}

		FindIter->second.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1));
	}

	void PushStartFunc(const GameString& _AniName, unsigned int _Frame, void(*_Ptr)(GameActor*))// ��
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
		}

		CPtr<CGameAni> pAni = FindAni(_AniName);
		if (nullptr == pAni)
		{
			MSG_ASSERT_CODE(L"�������� �ʴ� �ִϸ��̼ǿ� �ݹ��� ������ �����ϴ�.");
		}
		std::map<unsigned int, std::list<std::function<void(GameActor* _Actor)>>>::iterator FindIter
			= pAni->m_StartFunc.find(_Frame);

		// ���� �� �����ӿ� �ڷᱸ���� �ִ��� �����Ѵ�.
		if (pAni->m_StartFunc.end() == FindIter)
		{
			// ������ �� �������� �ϴ� �����.
			// ������ ��������� �ȴ�.
			pAni->m_StartFunc[_Frame] = std::list<std::function<void(GameActor* _Actor)>>();
			FindIter = pAni->m_StartFunc.find(_Frame);
		}

		FindIter->second.push_back(std::bind(_Ptr, std::placeholders::_1));
	}

	template<typename T>
	void PushEndFunc(const GameString& _AniName, unsigned int _Frame, T* _Obj, void(T::* _Ptr)(GameActor*))// ��
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
		}

		CPtr<CGameAni> pAni = FindAni(_AniName);
		if (nullptr == pAni)
		{
			MSG_ASSERT_CODE(L"�������� �ʴ� �ִϸ��̼ǿ� �ݹ��� ������ �����ϴ�.");
		}
		std::map<unsigned int, std::list<std::function<void(GameActor* _Actor)>>>::iterator FindIter
			= pAni->m_EndFunc.find(_Frame);

		// ���� �� �����ӿ� �ڷᱸ���� �ִ��� �����Ѵ�.
		if (pAni->m_EndFunc.end() == FindIter)
		{
			// ������ �� �������� �ϴ� �����.
			// ������ ��������� �ȴ�.
			pAni->m_EndFunc[_Frame] = std::list<std::function<void(GameActor* _Actor)>>();
			FindIter = pAni->m_EndFunc.find(_Frame);
		}

		FindIter->second.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1));
	}

	void PushEndFunc(const GameString& _AniName, unsigned int _Frame, void(*_Ptr)(GameActor*))// ��
	{
		if (nullptr == _Ptr)
		{
			MSG_ASSERT_CODE(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
		}

		CPtr<CGameAni> pAni = FindAni(_AniName);
		if (nullptr == pAni)
		{
			MSG_ASSERT_CODE(L"�������� �ʴ� �ִϸ��̼ǿ� �ݹ��� ������ �����ϴ�.");
		}
		std::map<unsigned int, std::list<std::function<void(GameActor* _Actor)>>>::iterator FindIter
			= pAni->m_EndFunc.find(_Frame);

		// ���� �� �����ӿ� �ڷᱸ���� �ִ��� �����Ѵ�.
		if (pAni->m_EndFunc.end() == FindIter)
		{
			// ������ �� �������� �ϴ� �����.
			// ������ ��������� �ȴ�.
			pAni->m_EndFunc[_Frame] = std::list<std::function<void(GameActor* _Actor)>>();
			FindIter = pAni->m_EndFunc.find(_Frame);
		}

		FindIter->second.push_back(std::bind(_Ptr, std::placeholders::_1));
	}


private:
	CPtr<CGameAni> FindAni(const GameString& _AniName);// ��

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
	//void ChangeAni(const GameString& _AniName, int _StartFrame, bool _IsEndOff = false);// ��
	//void ChangeAniReset(const GameString& _AniName, bool _IsEndOff = false);// ��

};