#include "Shorts0.h"

void Shorts0::EVENT0()
{
}

void Shorts0::EVENT1()
{
}

void Shorts0::EVENT2()
{
}

void Shorts0::CutSceneInit()
{
	m_State = SHORTS0_STATE::EVENT0;
}

void Shorts0::CutSceneUpdate()
{
	switch (m_State)
	{
	case SHORTS0_STATE::EVENT0:	EVENT0();
		break;
	case SHORTS0_STATE::EVENT1:	EVENT1();
		break;
	case SHORTS0_STATE::EVENT2:	EVENT2();
		break;
	case SHORTS0_STATE::MAX:
		break;
	default:
		break;
	}
}

Shorts0::Shorts0()
{
}

Shorts0::~Shorts0()
{
}
