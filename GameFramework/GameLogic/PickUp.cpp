#include "PickUp.h"
#include "Hero.h"

PickUp* PickUp::m_PickUp = nullptr;
CPtr<GameActor> PickUp::ArrPickUpTarget[(int)PICKUPTARGET::MAX] = { nullptr };

PickUp::PickUp()
{
	m_PickUp = this;
}

void PickUp::Join(CPtr<GameTransform> _Parent)
{
	if (false == Hero::MainPlayer->GetPickUp())
	{
		GetActor()->GetTrans()->SetParent(_Parent);
	}
}

void PickUp::Withdraw()
{
	GetActor()->GetTrans()->SetParent(nullptr);

	Hero::MainPlayer->SetPickUp(false);
}


