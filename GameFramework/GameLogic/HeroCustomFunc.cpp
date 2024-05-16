#include "Hero.h"
#include "ValueData.h"
#include "EnumData.h"

void Hero::CustomUpdate()
{

}



/*

void WEQUIPMENTSLOT::SetWeapon(WPTR<WTRANS> _Trans)
{
	// 제가 프레임워크 구조는 어떤 오브젝트에 들어가는
	// 컴포넌트 하나라도 알면
	// 다 알아낼수 있게 만들었다.

	WPTR<WBASICWEAPON> Weapon = _Trans->ACTOR()->FindComName<WBASICWEAPON>(L"Weapon");

	if (nullptr == Weapon)
	{
		return;
	}

	Render_SLOTWEAPON->SPRITE(Weapon->GetSlotName(), 0);
	Render_SLOTWEAPON->OriginScale(Weapon->GetSlotName());
	Render_SLOTWEAPON->WSCALE(Render_SLOTWEAPON->WSCALE() * 3.0f);
	Render_SLOTWEAPON->WPOS({ Render_SLOTWEAPON->WPOS().X,Render_SLOTWEAPON->WPOS().Y,Render_SLOTWEAPON->WPOS().Z - 1.0f });
	//Weapon->
	m_Weapon = _Trans;

	//Render_SLOTWEAPON->SPRITE(_String);
	//Render_SLOTWEAPON->OriginScale(_String);
	//Render_SLOTWEAPON->WSCALE(Render_SLOTWEAPON->WSCALE() * 3.0f);

}





:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: WBASICWEAPON







void WGAMEPLAYER::SLOTONE()
{
	if (PLAYEREQUIPMENTSLOT[1]->TRANS()->WPOS().X == 560.0f)
	{
		{
			PLAYEREQUIPMENTSLOT[0]->TRANS()->WPOS({ 560.0f,-310.0f,0.0f });
		}

		{
			PLAYEREQUIPMENTSLOT[1]->TRANS()->WPOS({ 580.0f,-300.0f,1.0f });
			PLAYEREQUIPMENTSLOT[1]->GetWeaponRender()->TRANS()->WMOVE({ 0.0f,0.0f,5.0f });
		}
		if (nullptr != PLAYEREQUIPMENTSLOT[0]->GetWeapon())
		{
			Slot[0]->On();
			m_Weapon = Slot[0]->TRANS();
			if (Slot[1] != nullptr)
			{
				Slot[1]->Off();
			}

		}
	}
}






void WGAMEPLAYER::SLOTTWO()
{
	if (PLAYEREQUIPMENTSLOT[0]->TRANS()->WPOS().X == 560.0f)
	{
		{
			PLAYEREQUIPMENTSLOT[1]->TRANS()->WPOS({ 560.0f,-310.0f,0.0f });
		}

		{
			PLAYEREQUIPMENTSLOT[0]->TRANS()->WPOS({ 580.0f,-300.0f,1.0f });
			PLAYEREQUIPMENTSLOT[0]->GetWeaponRender()->TRANS()->WMOVE({ 0.0f,0.0f,5.0f });
		}
		if (nullptr != PLAYEREQUIPMENTSLOT[1]->GetWeapon())
		{
			Slot[1]->On();
			Slot[0]->Off();
			m_Weapon = Slot[1]->TRANS();
		}
	}
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void WGAMEPLAYER::WeaponEnter(WCOL* _This, WCOL* _Other)
{
	if (_Other->Order() != (int)COLORDER::COLORDER_WEAPON)
	{
		return;
	}

	if (_Other->TRANS()->PARENT() != nullptr)
	{
		return;
	}

	if (nullptr != PLAYEREQUIPMENTSLOT[0]->GetWeapon()
		&& nullptr != PLAYEREQUIPMENTSLOT[1]->GetWeapon())
	{
		return;
	}

	if (nullptr != m_Weapon)
	{
		m_Weapon->ACTOR()->Off();
	}
	// 회전시키는게.
	//무기 위치
	// 아무것 빈액터를 만드세요.
	// 손을 만드세요.


	// _Other->ACTOR()->TRANS()->PARENT(WeaponPivot->TRANS());
	_Other->ACTOR()->TRANS()->PARENT(TRANS());
	WPTR<WCOL> ACTORCOL = _Other->ACTOR()->FindComType<WCOL>();
	_Other->ACTOR()->TRANS()->LPOS({ 0.05f, 0.05f,-0.8f });
	_Other->ACTOR()->TRANS()->WSCALE({ 1.28f,1.28f,0.1f });
	m_Weapon = _Other->ACTOR()->TRANS();
	ATTRESET();

	// 둘다 비어있다.
	if (nullptr == PLAYEREQUIPMENTSLOT[0]->GetWeapon()
		&& nullptr == PLAYEREQUIPMENTSLOT[1]->GetWeapon())
	{
		Slot[0] = m_Weapon->ACTOR();
		PLAYEREQUIPMENTSLOT[0]->SetWeapon(m_Weapon);
		WGAMESOUND::Play(L"PLAYERGETITEM", L"GetItem.wav");

	}
	else if (nullptr == PLAYEREQUIPMENTSLOT[1]->GetWeapon())
	{
		Slot[1] = m_Weapon->ACTOR();
		PLAYEREQUIPMENTSLOT[1]->SetWeapon(m_Weapon);

		WGAMESOUND::Play(L"PLAYERGETITEM", L"GetItem.wav");
		SLOTTWO();
	}
}







void WGAMEPLAYER::BossMapSet(WPTR<WGAMEACTOR> PTR1, WPTR<WGAMEACTOR> PTR2)
{
	{
		PTR1->TRANS()->PARENT(TRANS());
		WPTR<WCOL> ACTORCOL = PTR1->FindComType<WCOL>();
		PTR1->TRANS()->LPOS({ 0.05f, 0.05f,-0.8f });
		PTR1->TRANS()->WSCALE({ 1.28f,1.28f,0.1f });
		m_Weapon = PTR1->TRANS();

		Slot[0] = m_Weapon->ACTOR();
		PLAYEREQUIPMENTSLOT[0]->SetWeapon(m_Weapon);
	}
	{
		PTR2->TRANS()->PARENT(TRANS());
		WPTR<WCOL> ACTORCOL = PTR2->FindComType<WCOL>();
		PTR2->TRANS()->LPOS({ 0.05f, 0.05f,-0.8f });
		PTR2->TRANS()->WSCALE({ 1.28f,1.28f,0.1f });
		m_Weapon = PTR2->TRANS();

		Slot[1] = m_Weapon->ACTOR();
		PLAYEREQUIPMENTSLOT[1]->SetWeapon(m_Weapon);
	}
	SLOTTWO();
	SLOTONE();

}






*/