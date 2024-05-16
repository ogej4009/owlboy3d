#include "Hero.h"
#include "ValueData.h"
#include "EnumData.h"


void Hero::Stand()
{
	if (true == m_DirColorSensor[(unsigned int)DIR_STATE::DIRD])
	{
		ChangeState(HEROSTATE::FALL);
		return;
	}

	ChkBlock();

	if (GameInput::Press(L"LEFT") || GameInput::Press(L"RIGHT"))
	{
		ChangeState(HEROSTATE::RUN);
		return;
	}

	if (true == GameInput::Press(L"UP"))
	{
		ChangeState(HEROSTATE::JUMP);
		return;
	}

	if (true == GameInput::Down(L"SPACE"))
	{
		ChangeState(HEROSTATE::ROLLGROUND);
		return;
	}

	if (true == GameInput::Down(L"LMOUSE"))
	{
		ChangeState(HEROSTATE::TORNADO1);
		return;
	}

}

void Hero::Run()
{
	ChkBlock();

	if (m_PrevDir != m_Dir)
	{
		ChangeState(HEROSTATE::TURNTORUN);
		return;
	}

	if (GameInput::Up(L"LEFT") || GameInput::Up(L"RIGHT"))
	{
		ChangeState(HEROSTATE::STAND);
		return;
	}

	if (GameInput::Press(L"LEFT"))
	{
		Move(CVector::LEFT, m_MoveSpeed);
	}

	if (GameInput::Press(L"RIGHT"))
	{
		Move(CVector::RIGHT, m_MoveSpeed);
	}

	if (GameInput::Press(L"UP"))
	{
		ChangeState(HEROSTATE::JUMP);
		return;
	}

	if (GameInput::Down(L"SPACE"))
	{
		ChangeState(HEROSTATE::ROLLGROUND);
		return;
	}

	if (GameInput::Down(L"LMOUSE"))
	{
		ChangeState(HEROSTATE::TORNADO1);
		return;
	}

}

void Hero::TurnToRun()
{
	ChkBlock();

	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::RUN);
	return;
}

void Hero::Jump()
{

	GetTrans()->WMove(JumpVec * GameTime::DeltaTime(1.0f));
	JumpVec -= GravityVec * GameTime::DeltaTime(m_Gravity);

	if (JumpVec.Y <= 0 /*&& false == m_DirColorSensor[1]*/)
	{
		// JumpVector를 원래대로 돌려야 한다. 
		ChangeState(HEROSTATE::FALL);
		return;
	}

	if (GameInput::Press(L"LEFT"))
	{
		Move(CVector::LEFT, m_MoveSpeed);
	}

	if (GameInput::Press(L"RIGHT"))
	{
		Move(CVector::RIGHT, m_MoveSpeed);
	}

	if (GameInput::Down(L"UP"))
	{
		ChangeState(HEROSTATE::FLYUPSTART);
	}

}

void Hero::Fall()
{
	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	/// <summary>
	/// 되돌린다. 
	/// </summary>
	JumpVec = { 0.0f, 1.0f, 0.0f };

	ChkBlock();
	m_bLand = true;

	if (GameInput::Press(L"LEFT"))
	{
		Move(CVector::LEFT, m_MoveSpeed);
	}

	if (GameInput::Press(L"RIGHT"))
	{
		Move(CVector::RIGHT, m_MoveSpeed);
	}

	if (GameInput::Down(L"UP"))
	{
		ChangeState(HEROSTATE::FLYUPSTART);
		return;
	}
}

void Hero::Throw()
{
	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::FLY);
	return;

}

void Hero::FlyIdle()
{

	ChkFly();
	m_bLand = true;

	if (m_PrevDir != m_Dir)
	{
		ChangeState(HEROSTATE::TURNTOFLY);
		return;
	}

	/* TELEPORT */
	if (true == GameInput::Down(L"1"))
	{
		ChangeState(HEROSTATE::FLYCARRYIDLE);
		Join(0);
		return;
	}

	/* TELEPORT */
	if (true == GameInput::Down(L"2"))
	{
		ChangeState(HEROSTATE::FLYCARRYIDLE);
		Join(1);
		return;
	}

	/* TELEPORT */
	if (true == GameInput::Down(L"3"))
	{
		ChangeState(HEROSTATE::FLYCARRYIDLE);
		Join(2);
		return;
	}

	/* TELEPORT */
	if (true == GameInput::Down(L"4"))
	{
		ChangeState(HEROSTATE::FLYCARRYIDLE);
		Join(3);
		return;
	}


	if (GameInput::Down(L"RIGHT") || GameInput::Down(L"LEFT"))
	{
		ChangeState(HEROSTATE::STARTTOFLY);
		return;
	}

	if (GameInput::Down(L"UP"))
	{
		ChangeState(HEROSTATE::FLYUPSTART);
		return;
	}

	if (GameInput::Down(L"DOWN"))
	{
		ChangeState(HEROSTATE::FLYDOWNSTART);
		return;
	}

	if (GameInput::Down(L"RMOUSE"))
	{
		ChangeState(HEROSTATE::FALL);
		return;
	}

	if (GameInput::Down(L"SPACE"))
	{
		ChangeState(HEROSTATE::ROLL);
		return;
	}

	if (GameInput::Down(L"LMOUSE"))
	{
		ChangeState(HEROSTATE::TORNADO2);
		return;
	}

}

void Hero::Fly()
{

	ChkFly();
	m_bLand = true;

	/* TELEPORT */
	if (GameInput::Down(L"1") ||
		GameInput::Down(L"2") ||
		GameInput::Down(L"3") ||
		GameInput::Down(L"4"))
	{
		ChangeState(HEROSTATE::FLYCARRYIDLE);
		return;
	}

	if (GameInput::Press(L"RIGHT"))
	{
		Move(CVector::RIGHT, m_MoveSpeed);
	}

	if (GameInput::Press(L"LEFT"))
	{
		Move(CVector::LEFT, m_MoveSpeed);
	}

	if (GameInput::Press(L"UP"))
	{
		Move(CVector::UP, m_MoveSpeed);
	}

	if (GameInput::Press(L"DOWN"))
	{
		ChangeState(HEROSTATE::FLYDOWNSTART);
		return;
	}

	if (GameInput::Press(L"SPACE"))
	{
		ChangeState(HEROSTATE::ROLL);
	}

	if (GameInput::Down(L"LMOUSE"))
	{
		ChangeState(HEROSTATE::TORNADO2);
	}

	if (GameInput::Down(L"RMOUSE"))
	{
		ChangeState(HEROSTATE::FALL);
	}

	if (GameInput::Free(L"UP") &&
		GameInput::Free(L"DOWN") &&
		GameInput::Free(L"RIGHT") &&
		GameInput::Free(L"LEFT"))
	{
		ChangeState(HEROSTATE::FLYIDLE);
		return;
	}

}

void Hero::FlyUp()
{
	ChkFly();

	if (GameInput::Press(L"UP"))
	{
		Move(CVector::UP, m_MoveSpeed);
	}

	if (GameInput::Press(L"RIGHT"))
	{
		Move(CVector::RIGHT, m_MoveSpeed);
	}

	if (GameInput::Press(L"LEFT"))
	{
		Move(CVector::LEFT, m_MoveSpeed);
	}

	if (GameInput::Press(L"DOWN"))
	{
		ChangeState(HEROSTATE::FLYDOWNSTART);
		return;
	}

	if (GameInput::Down(L"SPACE"))
	{
		ChangeState(HEROSTATE::ROLL);
		return;
	}

	if (GameInput::Down(L"LMOUSE"))
	{
		ChangeState(HEROSTATE::TORNADO2);
		return;
	}

	if (GameInput::Free(L"UP") &&
		GameInput::Free(L"DOWN") &&
		GameInput::Free(L"RIGHT") &&
		GameInput::Free(L"LEFT"))
	{
		ChangeState(HEROSTATE::FLYIDLE);
		return;
	}
}


void Hero::FlyGlide()
{
	ChkFly();
	m_bLand = true;

	if (GameInput::Press(L"UP"))
	{
		ChangeState(HEROSTATE::FLYUPSTART);
		return;
	}

	if (GameInput::Press(L"DOWN"))
	{
		Move(CVector::DOWN, m_MoveSpeed);
	}

	if (GameInput::Press(L"RIGHT"))
	{
		Move(CVector::RIGHT, m_MoveSpeed);
	}

	if (GameInput::Press(L"LEFT"))
	{
		Move(CVector::LEFT, m_MoveSpeed);
	}

	if (GameInput::Down(L"SPACE"))
	{
		ChangeState(HEROSTATE::ROLL);
		return;
	}

	if (GameInput::Down(L"LMOUSE"))
	{
		ChangeState(HEROSTATE::TORNADO2);
		return;
	}

	if (GameInput::Down(L"RMOUSE"))
	{
		ChangeState(HEROSTATE::FALL);
		return;
	}

	if (GameInput::Free(L"UP") &&
		GameInput::Free(L"DOWN") &&
		GameInput::Free(L"RIGHT") &&
		GameInput::Free(L"LEFT"))
	{
		ChangeState(HEROSTATE::FLYIDLE);
		return;
	}

}



void Hero::StartToFly()
{
	ChkFly();

	if (m_Dir == DIR_STATE::DIRL)
	{
		Move(CVector::LEFT, m_AccelSpeed);
	}
	else if (m_Dir == DIR_STATE::DIRR)
	{
		Move(CVector::RIGHT, m_AccelSpeed);
	}

	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::FLY);
	return;

}



void Hero::TurnToFly()
{
	ChkFly();

	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::FLY);
	return;
}



void Hero::FlyDownStart()
{
	ChkFly();
	m_bLand = true;
	Move(CVector::DOWN, m_AccelSpeed);

	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::FLYGLIDE);
	return;

}

void Hero::FlyUpStart()
{
	ChkFly();


	Move(CVector::UP, m_AccelSpeed);

	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::FLY);
	return;

}

void Hero::Roll()
{

	if (GameInput::Press(L"RIGHT"))
	{
		Move(CVector::RIGHT, m_RollSpeed);
	}

	if (GameInput::Press(L"LEFT"))
	{
		Move(CVector::LEFT, m_RollSpeed);
	}

	if (GameInput::Press(L"UP"))
	{
		Move(CVector::UP, m_RollSpeed);
	}

	if (GameInput::Press(L"DOWN"))
	{
		Move(CVector::DOWN, m_RollSpeed);
	}

	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::FLY);
	return;
}

void Hero::RollGround()
{
	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::STAND);
	return;
}


void Hero::Tornado1()
{

	if (m_Dir == DIR_STATE::DIRL)
	{
		Move(CVector::LEFT, m_AccelSpeed);
	}
	else if (m_Dir == DIR_STATE::DIRR)
	{
		Move(CVector::RIGHT, m_AccelSpeed);
	}

	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::STAND);
	return;
}

void Hero::Tornado2()
{
	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::SPREADWINGS);
	return;
}

void Hero::SpreadWings()
{
	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::FLYIDLE);
	return;

}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::: ITEM CARRY :::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


void Hero::FlyCarryIdle()
{
	m_bLand = false;

	ChkFly();

	//// 테스트 
	//if (true == m_ChkPickUp)
	//{
	//	m_HeroArmOverlay->ChangeState(HEROARMSTATE::FLY);
	//	m_HeroArmOverlay->On();
	//	m_HeroArmOverlay->GetTrans()->SetWPos({ GetTrans()->GetWPos().X,
	//											GetTrans()->GetWPos().Y,
	//											-5.0f });
	//}
	//else
	//{
	//	//m_HeroArmOverlay->Off();
	//}

	if (m_PrevDir != m_Dir)
	{
		ChangeState(HEROSTATE::TURNTOFLYCARRY);
		return;
	}

	if (GameInput::Down(L"RIGHT") || GameInput::Down(L"LEFT"))
	{
		ChangeState(HEROSTATE::STARTTOFLYCARRY);
		return;
	}

	if (GameInput::Down(L"UP"))
	{
		ChangeState(HEROSTATE::FLYUPSTARTCARRY);
		return;
	}

	if (GameInput::Down(L"DOWN"))
	{
		ChangeState(HEROSTATE::FLYDOWNSTARTCARRY);
		return;
	}

	if (GameInput::Down(L"RMOUSE"))
	{
		ChangeState(HEROSTATE::THROW);
		Withdraw();
		return;
	}

}

void Hero::FlyCarry()
{
	m_bLand = false;

	ChkFly();

	//if (true == m_ChkPickUp)
	//{
	//	m_HeroArmOverlay->ChangeState(HEROARMSTATE::FLY);
	//	m_HeroArmOverlay->On();
	//}
	//else
	//{
	//	//m_HeroArmOverlay->Off();
	//}

	/* TELEPORT */
	if (GameInput::Down(L"1") ||
		GameInput::Down(L"2") ||
		GameInput::Down(L"3") ||
		GameInput::Down(L"4"))
	{
		ChangeState(HEROSTATE::FLYCARRYIDLE);
		return;
	}

	if (GameInput::Press(L"RIGHT"))
	{
		Move(CVector::RIGHT, m_MoveSpeed);
	}

	if (GameInput::Press(L"LEFT"))
	{
		Move(CVector::LEFT, m_MoveSpeed);
	}

	if (GameInput::Press(L"UP"))
	{
		Move(CVector::UP, m_MoveSpeed);
	}

	if (GameInput::Press(L"DOWN"))
	{
		ChangeState(HEROSTATE::FLYDOWNSTARTCARRY);
		return;
	}

	if (GameInput::Down(L"RMOUSE"))
	{
		ChangeState(HEROSTATE::THROW);
		Withdraw();
	}

	if (GameInput::Free(L"UP") &&
		GameInput::Free(L"DOWN") &&
		GameInput::Free(L"RIGHT") &&
		GameInput::Free(L"LEFT"))
	{
		ChangeState(HEROSTATE::FLYCARRYIDLE);
		return;
	}
}

void Hero::FlyCarryUp()
{
	m_bLand = false;

	ChkFly();

	if (GameInput::Press(L"UP"))
	{
		Move(CVector::UP, m_MoveSpeed);
	}

	if (GameInput::Press(L"RIGHT"))
	{
		Move(CVector::RIGHT, m_MoveSpeed);
	}

	if (GameInput::Press(L"LEFT"))
	{
		Move(CVector::LEFT, m_MoveSpeed);
	}

	if (GameInput::Press(L"DOWN"))
	{
		ChangeState(HEROSTATE::FLYDOWNSTARTCARRY);
		return;
	}

	if (GameInput::Free(L"UP") &&
		GameInput::Free(L"DOWN") &&
		GameInput::Free(L"RIGHT") &&
		GameInput::Free(L"LEFT"))
	{
		ChangeState(HEROSTATE::FLYCARRYIDLE);
		return;
	}
}

void Hero::FlyCarryGlide()
{
	m_bLand = false;

	ChkFly();

	if (GameInput::Press(L"UP"))
	{
		ChangeState(HEROSTATE::FLYUPSTARTCARRY);
		return;
	}

	if (GameInput::Press(L"DOWN"))
	{
		Move(CVector::DOWN, m_MoveSpeed);
	}

	if (GameInput::Press(L"RIGHT"))
	{
		Move(CVector::RIGHT, m_MoveSpeed);
	}

	if (GameInput::Press(L"LEFT"))
	{
		Move(CVector::LEFT, m_MoveSpeed);
	}

	if (GameInput::Free(L"UP") &&
		GameInput::Free(L"DOWN") &&
		GameInput::Free(L"RIGHT") &&
		GameInput::Free(L"LEFT"))
	{
		ChangeState(HEROSTATE::FLYCARRYIDLE);
		return;
	}
}

void Hero::FlyDownStartCarry()
{
	m_bLand = false;

	ChkFly();

	Move(CVector::DOWN, m_AccelSpeed);

	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::FLYCARRYGLIDE);
	return;
}

void Hero::FlyUpStartCarry()
{
	m_bLand = false;

	ChkFly();

	Move(CVector::UP, m_AccelSpeed);

	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::FLYCARRY);
	return;
}

void Hero::StartToFlyCarry()
{
	m_bLand = false;

	ChkFly();

	if (m_Dir == DIR_STATE::DIRL)
	{
		Move(CVector::LEFT, m_AccelSpeed);
	}
	else if (m_Dir == DIR_STATE::DIRR)
	{
		Move(CVector::RIGHT, m_AccelSpeed);
	}

	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::FLYCARRY);
	return;

}

void Hero::TurnToFlyCarry()
{
	m_bLand = false;

	ChkFly();

	if (false == m_Anim->IsAniEnd())
	{
		return;
	}

	ChangeState(HEROSTATE::FLYCARRY);
	return;
}


// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::: CUTSCENE :::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: Dream1

void Hero::TiredFlight()
{
}

void Hero::DreamFall()
{
}

void Hero::DreamReturn()
{
}

void Hero::DreamFly()
{
}

// Dream2

void Hero::Sleep()
{
}

void Hero::WakeUp()
{
}

void Hero::GetOut()
{
}

void Hero::DrinkTea()
{
}

// Event

void Hero::Treasure()
{
}

// Demage

void Hero::DeathSpin()
{
}

void Hero::Die()
{
}

// Blink

void Hero::Drink()
{
}

// Eat

void Hero::EatThrow()
{
}

void Hero::EatChomp()
{
}

void Hero::EatSwallow()
{
}

void Hero::EatReaction()
{
}

void Hero::Powerup()
{
}

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: Door

void Hero::EnterDoor()
{
}

void Hero::TurnBack()
{
}

void Hero::TurnBackToFront()
{
}

void Hero::ExitEnd()
{
}

void Hero::ExitLoop()
{
}

void Hero::ExitSad()
{
}

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: Battle

void Hero::RecoverFromStun()
{
}

void Hero::RecoverSlowly()
{
}

void Hero::HurtStand()
{
}

void Hero::HurtFly()
{
}

void Hero::HurtFlyCarry()
{
}

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: Fall Event 

void Hero::FallingEyesOpen()
{
}

void Hero::Stumble()
{
}

void Hero::Dive()
{
}

// Run Cut
void Hero::StartRun() {}
void Hero::RunBlank1() {}
void Hero::RunBlank2() {}
void Hero::RunSad() {}

// Walk Cut
void Hero::WalkBlank() {}
void Hero::WalkSad() {}
void Hero::WalkSerious() {}

// Epilogue Cut 
void Hero::SitDown() {}
void Hero::SitTalk() {}
void Hero::StandUp() {}
void Hero::LookUpSky() {}

// Emotion
void Hero::Cower() {}
void Hero::CowerEnd() {}

void Hero::DepressedDown() {}
void Hero::DepressedRecover() {}
void Hero::DepressedStart() {}
void Hero::DepressedUp() {}

void Hero::NervousEnd() {}
void Hero::NervousL() {}
void Hero::NervousR() {}
void Hero::NervousStart() {}

void Hero::Smile() {}
void Hero::Smile2() {}
void Hero::Sad() {}