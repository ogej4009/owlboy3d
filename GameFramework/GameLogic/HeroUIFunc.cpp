#include "Hero.h"
#include "EnumData.h"
#include "ValueData.h"
#include "UITrigger.h"

void Hero::TEST_ENTER_UI()
{
	int  a = 0;
	/*if (_Other->Order() != (int)COLLISION_ORDER::CO_TARGET)
	{
		return;
	}*/

	/*if (_Other->GetTrans()->GetParent() != nullptr)
	{
		return;
	}*/

	{
		m_UISlot[1] = GetScene()->CreateActor();
		m_UITriggerSlot[1] = m_UISlot[1]->CreateCom<UITrigger>(L"sprBtnLMouseMash_35x36_2x1.png", 1);
		m_UISlot[1]->GetTrans()->SetParent(GetTrans());
		m_UISlot[1]->GetTrans()->SetLPos({ 3.0f, -1.5f, 0.0f });
		m_UITrans[1] = m_UISlot[1]->GetTrans();
	}

	{
		m_UISlot[0] = GetScene()->CreateActor();
		m_UITriggerSlot[0] = m_UISlot[0]->CreateCom<UITrigger>(L"sprBtnLMouseMash_35x36_2x1.png", 0);
		m_UISlot[0]->GetTrans()->SetParent(GetTrans());
		m_UISlot[0]->GetTrans()->SetLPos({ -3.0f, -1.5f, 0.0f });
		m_UITrans[0] = m_UISlot[0]->GetTrans();
	}
		/*switch (m_HudState)
		{
		case HUDSTATE::FIND:
			break;
		case HUDSTATE::FLY:
			break;
		case HUDSTATE::GRAB:
			break;
		case HUDSTATE::TELEPORT:
			break;
		case HUDSTATE::MAX:
			break;
		default:
			break;
		}*/

	//m_UITriggerSlot[0]->SetUITrans(m_UITrans);



	/*if (nullptr != m_HudTriggerSlot[0]->GetHudTrans()
		//&& nullptr != m_HudTriggerSlot[1]->GetHudTrans())
	{
		return;
	}

	if (nullptr != m_HudTrans)
	{
		m_HudTrans->GetActor()->Off();
	}*/

	//_Other->GetActor()->GetTrans()->SetParent(GetTrans());
	//CPtr<GameCol> ACTORCOL = _Other->GetActor()->FindComType<GameCol>();
	//_Other->GetActor()->GetTrans()->SetLPos({ 0.05f, 0.05f,-0.8f });
	//_Other->GetActor()->GetTrans()->SetWScale({ 1.28f,1.28f,0.1f });
	//m_HudTrans = _Other->GetActor()->GetTrans();

	/*if (nullptr == m_HudTriggerSlot[0]->GetHudTrans()
		&& nullptr == m_HudTriggerSlot[1]->GetHudTrans())
	{
		m_HudSlot[0] = m_HudTrans->GetActor();
		m_HudTriggerSlot[0]->SetHudTrans(m_HudTrans);
	}
	else if (nullptr == m_HudTriggerSlot[1]->GetHudTrans())
	{
		m_HudSlot[1] = m_HudTrans->GetActor();
		m_HudTriggerSlot[1]->SetHudTrans(m_HudTrans);

		HudSlot2();
	}*/
}