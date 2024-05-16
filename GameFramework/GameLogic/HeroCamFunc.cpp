#include "Hero.h"
#include "ValueData.h"
#include "EnumData.h"
#include "ClientCam.h"

void Hero::LinkCamera()
{
	m_CCam = ClientCam::CamActor->FindComType<ClientCam>();
	//m_Cam->Join(GetTrans());
}

float Hero::CalDistance()
{
	float TotalLength = 0.0f;

	for (CamMoveInfo& CMI : m_InfoList)
	{
		TotalLength += CMI.m_Pos.Length2d();
	}

	return TotalLength;
}

Hero::CamMoveInfo Hero::CamMovInfo() 
{
	CamMoveInfo m_CamMovInfo;

	// 델타타임이 관여하지않게 무조건 한정된 거리를 유지한다. 
	// 플레이어가 지나간 거리  
	if (m_LimitDistance < CalDistance())
	{
		CVector PlayerPos = GetActor()->GetTrans()->GetWPos();
		CVector CamPos = m_CCam->GetActor()->GetTrans()->GetWPos();
		CVector DirVector = PlayerPos - CamPos;
		CVector MovingData = m_InfoList.front().m_Pos;

		m_CamMovInfo = { CamCalAngle(), DirVector.Normal2dVecReturn(), MovingData };

		m_InfoList.push_back(m_CamMovInfo);

		if (0.1f < DirVector.Length2d())
		{
			m_CCam->Move(DirVector.Normal2dVecReturn(), 1.5f);
		}

		while (m_LimitDistance <= CalDistance())
		{
			m_InfoList.pop_front();
		}

		return m_CamMovInfo;
	}
	else
	{
		return m_CamMovInfo;
	}

}

float Hero::CamCalAngle()
{
	CVector PlayerPos = GetActor()->GetTrans()->GetWPos();
	CVector CamPos = m_CCam->GetActor()->GetTrans()->GetWPos();
	CVector NewVector = PlayerPos - CamPos;
	float NewAngle = CVector::VectorToVectorAngle2D(CVector::UP, NewVector);
	return NewAngle;
}

void Hero::CamMoveListUpdate(/*float _X, float _Y*/)
{
	//m_Cam->GetActor()->GetTrans()->SetWPos({ GetTrans()->GetWPos().X + _X, GetTrans()->GetWPos().Y + _Y, -10.0f });

	CVector PlayerPos = GetActor()->GetTrans()->GetWPos();
	CVector CamPos = m_CCam->GetActor()->GetTrans()->GetWPos();
	CVector DirVector = PlayerPos - CamPos;

	m_InfoList.push_back({ CamCalAngle(), DirVector.Normal2dVecReturn(), GetActor()->GetTrans()->GetWPos() });

	int a = 0;
}

//m_PixelCam->OverCheck();
