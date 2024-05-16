#include "GameAnimation.h"
#include "GameActor.h"
#include <GameTime.h>



///////////////////////////////////////////////////////////////////////////////////////////////
//#pragma region AŸ��-��
//
//void GameAnimation::Init(CPtr<GameSpriteRenderer> _SpriteRender)
//{
//	if (nullptr == _SpriteRender)
//	{
//		m_SpriteRenderer = GetActor()->FindComType<GameSpriteRenderer>(); // �˻�
//	}
//	else
//	{
//		m_SpriteRenderer = _SpriteRender; // ����
//	}
//
//	if (nullptr == m_SpriteRenderer)
//	{
//		MSG_ASSERT_CODE(L"������ �ִϸ��̼��� ��������Ʈ �������� �־�� ���� �� �ֽ��ϴ�");
//	}
//
//}
//
//void GameAnimation::Update()
//{
//	if (nullptr == m_CurAni)
//	{
//		MSG_ASSERT_CODE(L"�ִϸ��̼��� �������� �ʾҽ��ϴ�.");
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
//		MSG_ASSERT_CODE(_AniName + L"�̹� ������� �ִϸ��̼� �̸��Դϴ�");
//	}
//
//	if (nullptr == GameSprite::Find(_SpriteName))
//	{
//		MSG_ASSERT_CODE(_AniName + L"��������Ʈ�� �������� �ʾ� �ִϸ��̼��� ����� �����ϴ�.");
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
//		MSG_ASSERT_CODE(_AniName + L"�ִϸ��̼��� �������� �ʽ��ϴ�");
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

//#pragma region BŸ��-��Ż
//
//void GameAnimation::Init(CPtr<GameSpriteRenderer> _SpriteRender)
//{
//	if (nullptr == _SpriteRender)
//	{
//		m_SpriteRenderer = GetActor()->FindComType<GameSpriteRenderer>(); // �˻�
//	}
//	else
//	{
//		m_SpriteRenderer = _SpriteRender; // ����
//	}
//
//	if (nullptr == m_SpriteRenderer)
//	{
//		MSG_ASSERT_CODE(L"������ �ִϸ��̼��� ��������Ʈ �������� �־�� ���� �� �ֽ��ϴ�");
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
//		MSG_ASSERT_CODE(L"�ִϸ��̼��� �������� �ʾҽ��ϴ�.");
//	}
//
//	m_CurAni->m_CurFrameTime -= GameTime::DeltaTime();
//
//	if (0 >= m_CurAni->m_CurFrameTime)
//	{
//		// 9 �������̾���.
//		// 9 �������� ��
//		// END
//
//		if (false == m_CurAni->IsReverse())
//		{
//			m_CurAni->CheckEndFunc(m_CurAni->m_CurFrame);
//			// 10
//			++m_CurAni->m_CurFrame; // 11
//			// �̼��� 11
//			// 11�����ӿ� �����ϴ� �Լ��� ����ȴ�.
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
//			// end�� 0�̴� -1  
//			if (m_CurAni->m_End > m_CurAni->m_CurFrame)
//			{
//				if (true == m_CurAni->m_Loop)  // <--- �۵��� ���մϴ�. ������ �𸣰ڽ��ϴ�.
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
//			// //������ ���� ����  <--- �۵��� �ϴµ� �������� �ִϸ��̼��� �ߵ����� �ʴ´ٴ� ������ �ִ�.
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
//		MSG_ASSERT_CODE(_AniName + L"�̹� ������� �ִϸ��̼� �̸��Դϴ�");
//	}
//
//	if (nullptr == GameSprite::Find(_SpriteName))
//	{
//		MSG_ASSERT_CODE(_AniName + L"��������Ʈ�� �������� �ʾ� �ִϸ��̼��� ����� �����ϴ�.");
//	}
//
//	m_Anim[_AniName] = new CGameAni();
//	m_Anim[_AniName]->m_AnimName = _AniName;
//	m_Anim[_AniName]->m_SpriteName = _SpriteName;
//	m_Anim[_AniName]->m_Start = _Start;
//	m_Anim[_AniName]->m_End = _End;
//	m_Anim[_AniName]->m_FrameTime = _FrameTime;
//	m_Anim[_AniName]->m_Loop = _Loop;
//	m_Anim[_AniName]->Actor = GetActor(); //// �� BŸ��(��Ż)
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
//		MSG_ASSERT_CODE(_AniName + L"�ִϸ��̼��� �������� �ʽ��ϴ�");
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
//	m_IsEnd = false;// ��
//	m_SpriteRenderer->On();
//	m_CurAni = m_Anim[_AniName];
//	m_CurAni->Reset();
//	m_CurAni->CheckStartFunc(m_CurAni->m_Start); // ��
//	IsAniEndOff = _IsEndOff;// ��
//
//}
//
//void GameAnimation::ChangeAni(const GameString& _AniName, int _StartFrame, bool _IsEndOff)
//{
//	if (m_Anim.end() == m_Anim.find(_AniName))
//	{
//		MSG_ASSERT_CODE(_AniName + L"�ִϸ��̼��� �������� �ʽ��ϴ�");
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
//		MSG_ASSERT_CODE(_AniName + L"�ִϸ��̼��� �������� �ʽ��ϴ�");
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




#pragma region CŸ��-��


void GameAnimation::Init(CPtr<GameSpriteRenderer> _SpriteRender)
{
	if (nullptr == _SpriteRender)
	{
		m_SpriteRenderer = GetActor()->FindComType<GameSpriteRenderer>(); // �˻�
	}
	else
	{
		m_SpriteRenderer = _SpriteRender; // ����
	}

	if (nullptr == m_SpriteRenderer)
	{
		MSG_ASSERT_CODE(L"������ �ִϸ��̼��� ��������Ʈ �������� �־�� ���� �� �ֽ��ϴ�");
	}

}

void GameAnimation::Update()
{
	if (nullptr == m_CurAni)
	{
		MSG_ASSERT_CODE(L"�ִϸ��̼��� �������� �ʾҽ��ϴ�.");
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
		MSG_ASSERT_CODE(_AniName + L"�̹� ������� �ִϸ��̼� �̸��Դϴ�");
	}

	if (nullptr == GameSprite::Find(_SpriteName))
	{
		MSG_ASSERT_CODE(_AniName + L"��������Ʈ�� �������� �ʾ� �ִϸ��̼��� ����� �����ϴ�.");
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
		MSG_ASSERT_CODE(_AniName + L"�ִϸ��̼��� �������� �ʽ��ϴ�");
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

