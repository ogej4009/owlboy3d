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
	// ���� �����ӿ�ũ ������ � ������Ʈ�� ����
	// ������Ʈ �ϳ��� �˸�
	// �� �˾Ƴ��� �ְ� �������.

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