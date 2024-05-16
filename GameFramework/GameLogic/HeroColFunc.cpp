#include "Hero.h"
#include "ValueData.h"
#include "EnumData.h"
#include <GameCol.h>
#include "PickUp.h"

void Hero::ColTriggerEnter(GameCol* _This, GameCol* _Other)
{

}

void Hero::ColTriggerStay(GameCol* _This, GameCol* _Other)
{
	if (true == GameInput::Down(L"LMOUSE"))
	{
		if (_Other->Order() != (int)COLLISION_ORDER::CO_TARGET)
		{
			return;
		}
		ChangeState(HEROSTATE::FLYCARRYIDLE);
		PickUpTarget = _Other->GetActor()->FindComName<PickUp>(L"PickUp");
		PickUpTarget->Join(GetTrans());
		m_bPickUp = true;
	}
}

void Hero::ColTriggerExit(GameCol* _This, GameCol* _Other)
{

}