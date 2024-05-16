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
						액터 static				->이름으로 찾는다.
		PICKUPTARGET = VALUELOGIC::PickTarget[0]->FindComName<PICKUPCOM>(L"PICKUP");
		// 이 함수를 쓰려구 했구나
		PICKUPTARGET->PickUp(TRANS());
		// 지금 상태를 알아야 하고,
		m_IsPickUpReady = false;
		// 이것을 또다른 컴포넌트에 넣어줄거야
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



		// [THROW KEY] 업데이트에서 부모-자식을 해제(Release)한다.
	if (GAMEINPUT::Down(L"CHILDOUT"))
	{
		// 자식이 있어야 해제가 가능하다
		if (nullptr != m_ChildTrans)
		{
			// 자식의 트랜스폼의 부모상태를 null로 만든다.
			m_ChildTrans->TRANS()->PARENT(nullptr);
			// 자식을 null로 만든다.
			m_ChildTrans = nullptr;
			PICKUPTARGET->PickThrow();
			ChangeState(PLAYEROTUSSTATE::THROW);
		}
	}

	PICKCOM 픽업 컴포넌트가 있다.

*/


