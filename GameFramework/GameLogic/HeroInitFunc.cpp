#include "Hero.h"
#include "ValueData.h"
#include "EnumData.h"
#include <GameCol.h>

void Hero::RenderInit()
{
	{
		ValueData::PIXEL_SCALE = 0.01f;
		ValueData::PIXEL_RATIO = 1.0f / ValueData::PIXEL_SCALE;
		m_Render = GetActor()->CreateCom<GameSpriteRenderer>((UINT)RENDER_ORDER::RO_ACTOR);
		m_Render->SetLScale({ 112.0f * ValueData::PIXEL_SCALE , 98.0f * ValueData::PIXEL_SCALE , 1.0f });
		m_Anim = GetActor()->CreateCom<GameAnimation>(m_Render);
	}

}

void Hero::ColInit()
{
	{
		ValueData::PIXEL_SCALE = 0.01f;
		ValueData::PIXEL_RATIO = 1.0f / ValueData::PIXEL_SCALE;
		m_Col = GetActor()->CreateCom<GameCol>((int)COLLISION_ORDER::CO_PLAYER);
		m_Col->SetWScale({ 20.0f * ValueData::PIXEL_SCALE, 60.0f * ValueData::PIXEL_SCALE, 1.0f });
		m_Col->ColType(COLTYPE::SPHERE2D);
		m_Col->PushStayFunc(this, &Hero::ColTriggerStay);
	}
}

void Hero::DebugInit()
{
	for (size_t i = 0; i < 4; i++)
	{
		m_DebugRender[i] = GetActor()->CreateCom<GameSpriteRenderer>((int)RENDER_ORDER::RO_COL_LEVEL);
		m_DebugRender[i]->SetLPos({ m_DirFrameSensor[i].X, m_DirFrameSensor[i].Y, -8.0f });
		m_DebugRender[i]->SetLScale({ 5.0f * ValueData::PIXEL_SCALE , 5.0f * ValueData::PIXEL_SCALE, 1.0f });
		m_DebugRender[i]->SetSprite(L"sprCircle_100x100.png");
	}

	DebugSubOff();
}

void Hero::HudInit()
{

}

void Hero::DebugSubOn()
{
	for (size_t i = 0; i < 4; i++)
	{
		m_DebugRender[i]->On();
	}
}

void Hero::DebugSubOff()
{
	for (size_t i = 0; i < 4; i++)
	{
		m_DebugRender[i]->Off();
	}
}


/*
	if (GAMEINPUT::Down(L"TELEPORT"))
	{
						���� static				->�̸����� ã�´�.
		PICKUPTARGET = VALUELOGIC::PickTarget[0]->FindComName<PICKUPCOM>(L"PICKUP");
		// �� �Լ��� ������ �߱���
		PICKUPTARGET->PickUp(TRANS());
		// ���� ���¸� �˾ƾ� �ϰ�,
		m_IsPickUpReady = false;
		// �̰��� �Ǵٸ� ������Ʈ�� �־��ٰž�
		m_ChildTrans = PICKUPTARGET;

		ChangeState(PLAYEROTUSSTATE::FLYGRABREADY);
		return;
	}


		if (GAMEINPUT::Down(L"LEFTMOUSE") &&
		PICKUPTARGET->ObjIndex == (int)PICKUPOBJTYPE::PICKUPVET)
	{
		ChangeState(PLAYEROTUSSTATE::EAT_THROW);

		VEGETABLE01::m_Vet->ChangeState(VEGISTATE::EAT);

		if (nullptr != m_ChildTrans)
		{
			m_ChildTrans->TRANS()->PARENT(nullptr);
			m_ChildTrans = nullptr;
		}
	}




		if (true == GAMEINPUT::Down(L"RIGHTMOUSE") && m_IsPickUpReady == true)
	{
		if (m_ChildTrans == nullptr)
		{
			ChangeState(PLAYEROTUSSTATE::FLYGRABREADY);
			//CLICKON->ChangeState(CLICKONSTATE::GRAB_STAY);
			PICKUPTARGET = _Other->Actor()->FindComName<PICKUPCOM>(L"PICKUP");
			PICKUPTARGET->PickUp(TRANS());
			m_ChildTrans = PICKUPTARGET;
			m_IsPickUpReady = false;
		}
	}



		// [THROW KEY] ������Ʈ���� �θ�-�ڽ��� ����(Release)�Ѵ�.
	if (GAMEINPUT::Down(L"CHILDOUT"))
	{
		// �ڽ��� �־�� ������ �����ϴ�
		if (nullptr != m_ChildTrans)
		{
			// �ڽ��� Ʈ�������� �θ���¸� null�� �����.
			m_ChildTrans->TRANS()->PARENT(nullptr);
			// �ڽ��� null�� �����.
			m_ChildTrans = nullptr;
			PICKUPTARGET->PickThrow();
			ChangeState(PLAYEROTUSSTATE::THROW);
		}
	}

	PICKCOM �Ⱦ� ������Ʈ�� �ִ�.

*/


