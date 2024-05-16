#include "Hero.h"
#include "EnumData.h"
#include "ValueData.h"
#include "HudTrigger.h"


/* 
	CPTR<GAMETRANSFORM> m_Weapon; m_HudTrans
	CPTR<GAMEACTOR> Slot[2];  m_HudSlot
*/

void Hero::TEST_ENTER_HUD()
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
		m_HudSlot[0] = GetScene()->CreateActor();
		m_HudTriggerSlot[0] = m_HudSlot[0]->CreateCom<HudTrigger>(L"sprKeyFly_20x36_2x1.png");
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

	}

	m_HudSlot[0]->GetTrans()->SetParent(GetTrans());
	m_HudSlot[0]->GetTrans()->SetLPos({ 0.0f, 0.2f, 0.0f });
	m_HudTrans = m_HudSlot[0]->GetTrans();
	m_HudTriggerSlot[0]->SetHudTrans(m_HudTrans);


	/*if (nullptr != m_HudTriggerSlot[0]->GetHudTrans()
		&& nullptr != m_HudTriggerSlot[1]->GetHudTrans())
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



void Hero::HudSlot1()
{
	if (m_HudTriggerSlot[1]->GetTrans()->GetWPos().X == 560.0f)
	{
		{
			m_HudTriggerSlot[0]->GetTrans()->SetWPos({ 560.0f,-310.0f,0.0f });
		}

		{
			m_HudTriggerSlot[1]->GetTrans()->SetWPos({ 580.0f,-300.0f,1.0f });
			m_HudTriggerSlot[1]->GetHudRender()->GetTrans()->WMove({ 0.0f,0.0f,5.0f });
		}
		if (nullptr != m_HudTriggerSlot[0]->GetHudTrans())
		{
			m_HudSlot[0]->On();
			m_HudTrans = m_HudSlot[0]->GetTrans();
			if (m_HudSlot[1] != nullptr)
			{
				m_HudSlot[1]->Off();
			}

		}
	}
}

void Hero::HudSlot2()
{
	if (m_HudTriggerSlot[0]->GetTrans()->GetWPos().X == 560.0f)
	{
		{
			m_HudTriggerSlot[1]->GetTrans()->SetWPos({ 560.0f,-310.0f,0.0f });
		}

		{
			m_HudTriggerSlot[0]->GetTrans()->SetWPos({ 580.0f,-300.0f,1.0f });
			m_HudTriggerSlot[0]->GetHudRender()->GetTrans()->WMove({ 0.0f,0.0f,5.0f });
		}
		if (nullptr != m_HudTriggerSlot[1]->GetHudTrans())
		{
			m_HudSlot[1]->On();
			m_HudSlot[0]->Off();
			m_HudTrans = m_HudSlot[1]->GetTrans();
		}
	}
}

/* 


void WGAMEPLAYER::ChildEnter(WCOL* _This, WCOL* _Other)
{
	// _Other->PARENT(TRANS());
	if (false == Check)
	{
		_Other->ACTOR()->TRANS()->PARENT(TRANS());
		_Other->ACTOR()->TRANS()->LPOS({ 0.0f, -0.6f, 0.0f });
		m_Weapon = _Other->ACTOR()->TRANS();
	}
}

*/


/* 

void WGAMEPLAYER::ATTCHECK()
{
	if (nullptr == m_Weapon)
	{
		return;
	}

	if (true == AttCheck)
	{
		ATT();
		return;
	}

	W3DDEBUG::DrawDebugText(L"ANGLE : %f", WVECTOR::VectorToVectorAngle2D(WVECTOR::RIGHT, WGAMESCENE::m_CurScene->MainCam()->OrthWorldMousePos2D() - TRANS()->WPOS()));

	if (false == AttackTwinCheck)
	{
		if (m_eDir == ACTORDIR::AD_RIGHT)
		{
			m_Weapon->LROT({ 0, 0, WVECTOR::VectorToVectorAngle2D(WVECTOR::RIGHT, WGAMESCENE::m_CurScene->MainCam()->OrthWorldMousePos2D() - TRANS()->WPOS()) });
		}
		else
		{
			m_Weapon->LROT({ 0, 0, WVECTOR::VectorToVectorAngle2D(WVECTOR::LEFT, WGAMESCENE::m_CurScene->MainCam()->OrthWorldMousePos2D() - TRANS()->WPOS()) });
		}
		m_Weapon->WPOS({ m_Weapon->WPOS().X, m_Weapon->WPOS().Y, -1.0f });
	}
	else
	{
		if (m_eDir == ACTORDIR::AD_RIGHT)
		{
			m_Weapon->LROT({ 0,0, WVECTOR::VectorToVectorAngle2D(WVECTOR::UP, WGAMESCENE::m_CurScene->MainCam()->OrthWorldMousePos2D() - TRANS()->WPOS()) });

		}
		else
		{
			m_Weapon->LROT({ 0,0, WVECTOR::VectorToVectorAngle2D(WVECTOR::UP, WGAMESCENE::m_CurScene->MainCam()->OrthWorldMousePos2D() - TRANS()->WPOS()) });
		}
		m_Weapon->WPOS({ m_Weapon->WPOS().X, m_Weapon->WPOS().Y, -5.0f });
	}

	if (true == WGAMEINPUT::Down(L"PLAYERATT") && false == AttCheck)
	{
		AttCheck = true;
	}

}

*/




/* 

void WGAMEPLAYER::BossMapSet(WPTR<WGAMEACTOR> PTR1, WPTR<WGAMEACTOR> PTR2)
{
	{
		PTR1->TRANS()->PARENT(TRANS());
		WPTR<WCOL> ACTORCOL = PTR1->FindComType<WCOL>();
		PTR1->TRANS()->LPOS({ 0.05f, 0.05f,-0.8f });
		PTR1->TRANS()->WSCALE({ 1.28f,1.28f,0.1f });
		m_Weapon = PTR1->TRANS();

		Slot[0] = m_Weapon->ACTOR();
		m_HudTriggerSlot[0]->SetWeapon(m_Weapon);
	}
	{
		PTR2->TRANS()->PARENT(TRANS());
		WPTR<WCOL> ACTORCOL = PTR2->FindComType<WCOL>();
		PTR2->TRANS()->LPOS({ 0.05f, 0.05f,-0.8f });
		PTR2->TRANS()->WSCALE({ 1.28f,1.28f,0.1f });
		m_Weapon = PTR2->TRANS();

		Slot[1] = m_Weapon->ACTOR();
		m_HudTriggerSlot[1]->SetWeapon(m_Weapon);
	}
	SLOTTWO();
	SLOTONE();

}

*/