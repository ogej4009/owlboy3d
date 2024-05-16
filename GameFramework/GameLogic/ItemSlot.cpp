#include "ItemSlot.h"

void ItemSlot::Init()
{
}

void ItemSlot::Update()
{
}

ItemSlot::ItemSlot()
{
}

ItemSlot::~ItemSlot()
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
*/