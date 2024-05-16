#include "UICam.h"
#include "EnumData.h"
#include "ValueData.h"


void UICam::ChangeState(BORDER_TRIGGER_STATE _State)
{
	m_BorderState = _State;
}

void UICam::Move(const CVector& _Dir, float _Speed)
{
	GetTrans()->WMove(_Dir * GameTime::DeltaTime(_Speed));
}

void UICam::Join(CPtr<GameTransform> _Parent)
{
}

void UICam::Withdraw()
{
}

void UICam::On()
{
	/*m_Time -= GameTime::DeltaTime();

	if (m_Time < 0.0f)
	{
		Run();
	}
	else
	{
		m_Actor_Top_Border->GetTrans()->WMove(CVector::DOWN * GameTime::DeltaTime(BORDER_MOV_SPEED));
		m_Actor_Bot_Border->GetTrans()->WMove(CVector::UP * GameTime::DeltaTime(BORDER_MOV_SPEED));
	}*/

	if (m_Actor_Top_Border->GetTrans()->GetWPos().Y < TOP_BORDER_FINAL_POS_Y ||
		m_Actor_Bot_Border->GetTrans()->GetWPos().Y > BOT_BORDER_FINAL_POS_Y)
	{
		ChangeState(BORDER_TRIGGER_STATE::BT_RUN);
		return;
	}
	else
	{
		m_Actor_Top_Border->GetTrans()->WMove(CVector::DOWN * GameTime::DeltaTime(BORDER_MOV_SPEED));
		m_Actor_Bot_Border->GetTrans()->WMove(CVector::UP * GameTime::DeltaTime(BORDER_MOV_SPEED));
	}


}

void UICam::Off()
{
	if (m_Actor_Top_Border->GetTrans()->GetWPos().Y > TOP_BORDER_START_POS_Y ||
		m_Actor_Bot_Border->GetTrans()->GetWPos().Y < BOT_BORDER_START_POS_Y)
	{
		ChangeState(BORDER_TRIGGER_STATE::BT_IDLE);
		return;
	}
	else
	{
		m_Actor_Top_Border->GetTrans()->WMove(CVector::UP * GameTime::DeltaTime(BORDER_MOV_SPEED));
		m_Actor_Bot_Border->GetTrans()->WMove(CVector::DOWN * GameTime::DeltaTime(BORDER_MOV_SPEED));
	}
}

void UICam::Idle()
{
	if (true == GameInput::Down(L"TRIGGER"))
	{
		ChangeState(BORDER_TRIGGER_STATE::BT_ON);
		return;
	}
}

void UICam::Run()
{
	if (true == GameInput::Down(L"TRIGGER2"))
	{
		ChangeState(BORDER_TRIGGER_STATE::BT_OFF);
		return;
	}
}

void UICam::Init()
{
	{
		m_Actor_Top_Border = GetScene()->CreateActor();
		m_Actor_Top_Border->GetTrans()->SetWPos({ 0.0f, TOP_BORDER_START_POS_Y, -9.0f});
		m_Render_Top_Border = m_Actor_Top_Border->CreateCom<GameSpriteRenderer>((UINT)RENDER_ORDER::RO_UI);
		m_Render_Top_Border->SetSprite(L"sprDark_32x32.png");
		m_Render_Top_Border->SetWScale({ 10.0f, 1.0f, 1.0f });
	}
	{
		m_Actor_Bot_Border = GetScene()->CreateActor();
		m_Actor_Bot_Border->GetTrans()->SetWPos({ 0.0f, BOT_BORDER_START_POS_Y, -9.0f });
		m_Render_Bot_Border = m_Actor_Bot_Border->CreateCom<GameSpriteRenderer>((UINT)RENDER_ORDER::RO_UI);
		m_Render_Bot_Border->SetSprite(L"sprDark_32x32.png");
		m_Render_Bot_Border->SetWScale({ 10.0f, 1.0f, 1.0f });
	}

	ChangeState(BORDER_TRIGGER_STATE::BT_IDLE);
}

void UICam::Update()
{
	switch (m_BorderState)
	{
	case BORDER_TRIGGER_STATE::BT_IDLE: Idle();
		break;
	case BORDER_TRIGGER_STATE::BT_ON: On();
		break;
	case BORDER_TRIGGER_STATE::BT_OFF: Off();
		break;
	case BORDER_TRIGGER_STATE::BT_RUN: Run();
		break;
	case BORDER_TRIGGER_STATE::MAX:
		break;
	default:
		break;
	}
}

UICam::UICam() 
	: m_Time(BORDER_TIME_DEFAULT)
{
}

UICam::~UICam()
{
}
