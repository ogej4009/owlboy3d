#include "GameAnimation.h"
#include "GameActor.h"
#include <GameTime.h>



///////////////////////////////////////////////////////////////////////////////////////////////
//#pragma region A타입-아
//
//void GameAnimation::Init(CPtr<GameSpriteRenderer> _SpriteRender)
//{
//	if (nullptr == _SpriteRender)
//	{
//		m_SpriteRenderer = GetActor()->FindComType<GameSpriteRenderer>(); // 검색
//	}
//	else
//	{
//		m_SpriteRenderer = _SpriteRender; // 실행
//	}
//
//	if (nullptr == m_SpriteRenderer)
//	{
//		MSG_ASSERT_CODE(L"프레임 애니메이션은 스프라이트 랜더러가 있어야 만들 수 있습니다");
//	}
//
//}
//
//void GameAnimation::Update()
//{
//	if (nullptr == m_CurAni)
//	{
//		MSG_ASSERT_CODE(L"애니메이션이 지정되지 않았습니다.");
//	}
//
//	m_CurAni->m_CurFrameTime -= GameTime::DeltaTime();
//
//	if (0 >= m_CurAni->m_CurFrameTime)
//	{
//		++m_CurAni->m_CurFrame;
//
//		m_CurAni->m_CurFrameTime = m_CurAni->m_FrameTime;
//
//		unsigned int Frame = m_CurAni->m_CurFrame;
//
//		if (m_CurAni->m_End < m_CurAni->m_CurFrame)
//		{
//			if (true == m_CurAni->m_Loop)
//			{
//				m_CurAni->m_CurFrame = m_CurAni->m_Start;
//			}
//			else
//			{
//				if (true == IsAniEndOff)
//				{
//					m_SpriteRenderer->Off();
//
//				}
//
//				m_IsEnd = true;
//				
//				--m_CurAni->m_CurFrame;
//			}
//		}
//	}
//
//	unsigned int Check = m_CurAni->m_CurFrame;
//	
//	m_SpriteRenderer->SetSprite(m_CurAni->m_SpriteName, m_CurAni->m_CurFrame);
//
//}
//
//void GameAnimation::CreateAni(const GameString& _AniName, const GameString& _SpriteName, unsigned int _Start, unsigned int _End, float _FrameTime, bool _Loop)
//{
//	if (m_Anim.end() != m_Anim.find(_AniName))
//	{
//		MSG_ASSERT_CODE(_AniName + L"이미 만들어진 애니메이션 이름입니다");
//	}
//
//	if (nullptr == GameSprite::Find(_SpriteName))
//	{
//		MSG_ASSERT_CODE(_AniName + L"스프라이트가 존재하지 않아 애니메이션을 만들수 없습니다.");
//	}
//
//	m_Anim[_AniName] = new CGameAni();
//	m_Anim[_AniName]->m_AnimName = _AniName;
//	m_Anim[_AniName]->m_SpriteName = _SpriteName;
//	m_Anim[_AniName]->m_Start = _Start;
//	m_Anim[_AniName]->m_End = _End;
//	m_Anim[_AniName]->m_FrameTime = _FrameTime;
//	m_Anim[_AniName]->m_Loop = _Loop;
//
//}
//
//
//void GameAnimation::ChangeAni(const GameString& _AniName, bool _IsEndOff)
//{
//	if (m_Anim.end() == m_Anim.find(_AniName))
//	{
//		MSG_ASSERT_CODE(_AniName + L"애니메이션이 존재하지 않습니다");
//	}
//
//	if (m_CurAni != nullptr && m_CurAni == m_Anim[_AniName])
//	{
//		return;
//	}
//
//	m_IsEnd = false;
//	m_SpriteRenderer->On();
//	m_CurAni = m_Anim[_AniName];
//	m_CurAni->Reset();
//	IsAniEndOff = _IsEndOff;
//
//}
//
//#pragma endregion

///////////////////////////////////////////////////////////////////////////////////////////////

//#pragma region B타입-메탈
//
//void GameAnimation::Init(CPtr<GameSpriteRenderer> _SpriteRender)
//{
//	if (nullptr == _SpriteRender)
//	{
//		m_SpriteRenderer = GetActor()->FindComType<GameSpriteRenderer>(); // 검색
//	}
//	else
//	{
//		m_SpriteRenderer = _SpriteRender; // 실행
//	}
//
//	if (nullptr == m_SpriteRenderer)
//	{
//		MSG_ASSERT_CODE(L"프레임 애니메이션은 스프라이트 랜더러가 있어야 만들 수 있습니다");
//	}
//
//	IsAniEndOff = false;
//
//}
//
//void GameAnimation::Update()
//{
//
//	if (nullptr == m_CurAni)
//	{
//		MSG_ASSERT_CODE(L"애니메이션이 지정되지 않았습니다.");
//	}
//
//	m_CurAni->m_CurFrameTime -= GameTime::DeltaTime();
//
//	if (0 >= m_CurAni->m_CurFrameTime)
//	{
//		// 9 프레임이었다.
//		// 9 프레임의 끝
//		// END
//
//		if (false == m_CurAni->IsReverse())
//		{
//			m_CurAni->CheckEndFunc(m_CurAni->m_CurFrame);
//			// 10
//			++m_CurAni->m_CurFrame; // 11
//			// 이순간 11
//			// 11프레임에 시작하는 함수가 실행된다.
//			m_CurAni->CheckStartFunc(m_CurAni->m_CurFrame);
//
//			m_CurAni->m_CurFrameTime = m_CurAni->m_FrameTime;
//
//			int Frame = m_CurAni->m_CurFrame;
//
//			if (m_CurAni->m_End < m_CurAni->m_CurFrame)
//			{
//				if (true == m_CurAni->m_Loop)
//				{
//					m_CurAni->m_CurFrame = m_CurAni->m_Start;
//				}
//				else
//				{
//					if (true == IsAniEndOff)
//					{
//						m_SpriteRenderer->Off();
//					}
//					--m_CurAni->m_CurFrame;
//				}
//			}
//		}
//		else if (true == m_CurAni->IsReverse())
//		{
//			m_CurAni->CheckEndFunc(m_CurAni->m_CurFrame);
//			--m_CurAni->m_CurFrame;
//			m_CurAni->CheckStartFunc(m_CurAni->m_CurFrame);
//
//			m_CurAni->m_CurFrameTime = m_CurAni->m_FrameTime;
//
//			int Frame = m_CurAni->m_CurFrame;
//
//			// end가 0이다 -1  
//			if (m_CurAni->m_End > m_CurAni->m_CurFrame)
//			{
//				if (true == m_CurAni->m_Loop)  // <--- 작동을 안합니다. 이유를 모르겠습니다.
//				{
//					m_CurAni->m_CurFrame = m_CurAni->m_Start;
//				}
//				else
//				{
//					if (true == IsAniEndOff)
//					{
//						m_SpriteRenderer->Off();
//					}
//					++m_CurAni->m_CurFrame;
//				}
//			}
//			// //프레임 음수 방지  <--- 작동은 하는데 정상적인 애니메이션이 발동하지 않는다는 문제가 있다.
//		}
//
//	}
//
//	unsigned int Check = m_CurAni->m_CurFrame;
//
//	m_SpriteRenderer->SetSprite(m_CurAni->m_SpriteName, m_CurAni->m_CurFrame);
//
//}
//
//CPtr<GameAnimation::CGameAni> GameAnimation::FindAni(const GameString& _AniName)
//{
//	if (m_Anim.end() == m_Anim.find(_AniName))
//	{
//		return nullptr;
//	}
//
//	return m_Anim[_AniName];
//}
//
//void GameAnimation::CreateAni(const GameString& _AniName, const GameString& _SpriteName, unsigned int _Start, unsigned int _End, float _FrameTime, bool _Loop)
//{
//	if (m_Anim.end() != m_Anim.find(_AniName))
//	{
//		MSG_ASSERT_CODE(_AniName + L"이미 만들어진 애니메이션 이름입니다");
//	}
//
//	if (nullptr == GameSprite::Find(_SpriteName))
//	{
//		MSG_ASSERT_CODE(_AniName + L"스프라이트가 존재하지 않아 애니메이션을 만들수 없습니다.");
//	}
//
//	m_Anim[_AniName] = new CGameAni();
//	m_Anim[_AniName]->m_AnimName = _AniName;
//	m_Anim[_AniName]->m_SpriteName = _SpriteName;
//	m_Anim[_AniName]->m_Start = _Start;
//	m_Anim[_AniName]->m_End = _End;
//	m_Anim[_AniName]->m_FrameTime = _FrameTime;
//	m_Anim[_AniName]->m_Loop = _Loop;
//	m_Anim[_AniName]->Actor = GetActor(); //// ★ B타입(메탈)
//}
//
//bool GameAnimation::EndAni()
//{
//	if (m_CurAni->m_End == m_CurAni->m_CurFrame)
//	{
//		return true;
//	}
//	return false;
//}
//
//void GameAnimation::ChangeAni(const GameString& _AniName, bool _IsEndOff)
//{
//
//	if (m_Anim.end() == m_Anim.find(_AniName))
//	{
//		MSG_ASSERT_CODE(_AniName + L"애니메이션이 존재하지 않습니다");
//	}
//
//	//if (m_CurAni != nullptr && m_CurAni == m_Anim[_AniName])
//	//{
//	//	return;
//	//}
//
//	if (m_CurAni == m_Anim[_AniName])
//	{
//		return;
//	}
//
//	m_IsEnd = false;// ★
//	m_SpriteRenderer->On();
//	m_CurAni = m_Anim[_AniName];
//	m_CurAni->Reset();
//	m_CurAni->CheckStartFunc(m_CurAni->m_Start); // ★
//	IsAniEndOff = _IsEndOff;// ★
//
//}
//
//void GameAnimation::ChangeAni(const GameString& _AniName, int _StartFrame, bool _IsEndOff)
//{
//	if (m_Anim.end() == m_Anim.find(_AniName))
//	{
//		MSG_ASSERT_CODE(_AniName + L"애니메이션이 존재하지 않습니다");
//	}
//
//	if (m_CurAni == m_Anim[_AniName])
//	{
//		return;
//	}
//
//	m_SpriteRenderer->On();
//	m_CurAni = m_Anim[_AniName];
//	m_CurAni->Reset();
//
//	if (_StartFrame != -1)
//	{
//		m_CurAni->m_CurFrame = _StartFrame;
//	}
//
//	m_CurAni->CheckStartFunc(m_CurAni->m_Start);
//	IsAniEndOff = _IsEndOff;
//}
//
//void GameAnimation::ChangeAniReset(const GameString& _AniName, bool _IsEndOff)
//{
//	if (m_Anim.end() == m_Anim.find(_AniName))
//	{
//		MSG_ASSERT_CODE(_AniName + L"애니메이션이 존재하지 않습니다");
//	}
//
//	m_SpriteRenderer->On();
//	m_CurAni = m_Anim[_AniName];
//	m_CurAni->Reset();
//	m_CurAni->CheckStartFunc(m_CurAni->m_Start);
//	IsAniEndOff = _IsEndOff;
//}
//
//#pragma endregion



////////////////////////////////////////////////////////////////////////////////////////////////////




#pragma region C타입-루


void GameAnimation::Init(CPtr<GameSpriteRenderer> _SpriteRender)
{
	if (nullptr == _SpriteRender)
	{
		m_SpriteRenderer = GetActor()->FindComType<GameSpriteRenderer>(); // 검색
	}
	else
	{
		m_SpriteRenderer = _SpriteRender; // 실행
	}

	if (nullptr == m_SpriteRenderer)
	{
		MSG_ASSERT_CODE(L"프레임 애니메이션은 스프라이트 랜더러가 있어야 만들 수 있습니다");
	}

}

void GameAnimation::Update()
{
	if (nullptr == m_CurAni)
	{
		MSG_ASSERT_CODE(L"애니메이션이 지정되지 않았습니다.");
	}

	m_CurAni->m_CurFrameTime -= GameTime::DeltaTime();

	if (0 >= m_CurAni->m_CurFrameTime)
	{
		m_CurAni->CheckEndFunc(m_CurAni->m_CurFrame);
		++m_CurAni->m_CurFrame;
		m_CurAni->CheckStartFunc(m_CurAni->m_CurFrame);
		m_CurAni->m_CurFrameTime = m_CurAni->m_FrameTime;

		unsigned int Frame = m_CurAni->m_CurFrame;

		if (m_CurAni->m_End < m_CurAni->m_CurFrame)
		{
			if (true == m_CurAni->m_Loop)
			{
				m_CurAni->m_CurFrame = m_CurAni->m_Start;
			}
			else
			{
				--m_CurAni->m_CurFrame;
			}
		}
	}

	unsigned int Check = m_CurAni->m_CurFrame;
	m_SpriteRenderer->SetSprite(m_CurAni->m_SpriteName, m_CurAni->m_CurFrame);

}


void GameAnimation::CreateAni(const GameString& _AniName, const GameString& _SpriteName, unsigned int _Start, unsigned int _End, float _FrameTime, bool _Loop)
{
	if (m_Anim.end() != m_Anim.find(_AniName))
	{
		MSG_ASSERT_CODE(_AniName + L"이미 만들어진 애니메이션 이름입니다");
	}

	if (nullptr == GameSprite::Find(_SpriteName))
	{
		MSG_ASSERT_CODE(_AniName + L"스프라이트가 존재하지 않아 애니메이션을 만들수 없습니다.");
	}

	m_Anim[_AniName] = new CGameAni();
	m_Anim[_AniName]->m_AnimName = _AniName;
	m_Anim[_AniName]->m_SpriteName = _SpriteName;
	m_Anim[_AniName]->m_Start = _Start;
	m_Anim[_AniName]->m_End = _End;
	m_Anim[_AniName]->m_FrameTime = _FrameTime;
	m_Anim[_AniName]->m_Loop = _Loop;
	m_Anim[_AniName]->Actor = GetActor();

}

void GameAnimation::ChangeAni(const GameString& _AniName)
{
	if (m_Anim.end() == m_Anim.find(_AniName))
	{
		MSG_ASSERT_CODE(_AniName + L"애니메이션이 존재하지 않습니다");
	}

	m_CurAni = m_Anim[_AniName];
	m_CurAni->Reset();
	m_CurAni->CheckStartFunc(m_CurAni->m_Start);
}

CPtr<GameAnimation::CGameAni> GameAnimation::FindAni(const GameString& _AniName)
{
	if (m_Anim.end() == m_Anim.find(_AniName))
	{
		return nullptr;
	}

	return m_Anim[_AniName];
}

#pragma endregion

