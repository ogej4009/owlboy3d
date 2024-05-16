#include "UITrigger.h"
#include "ValueData.h"
#include "EnumData.h"

CPtr<GameTexture> UITrigger::m_Tex;

void UITrigger::ChangeState(UITRIGGERSTATE _State)
{
	m_State = _State;
	m_Anim->ChangeAni(m_StateName[(UINT)_State]);
}

void UITrigger::Move(const CVector& _Dir, float _Speed)
{
	GetTrans()->WMove(_Dir * GameTime::DeltaTime(_Speed));
}

void UITrigger::Idle()
{
	m_Delay = UI_DELAY_TIME_DEFAULT;
	m_Alpha = UI_ALPHA_MIN;

	if (true == GameInput::Down(L"TRIGGER")) // TEST CODE
	{
		ChangeState(UITRIGGERSTATE::UI_ON);
		return;
	}
}

void UITrigger::On()
{
	// OFF > ON : Y값, Z값이 커진다. 
	// SPR도 투명or꺼짐에서 선명or켜짐으로 
	m_Delay -= GameTime::DeltaTime();

	if (m_Delay < 0.0f)
	{
		ChangeState(UITRIGGERSTATE::UI_RUN);
		return;
	}
	else
	{
		m_Alpha += GameTime::DeltaTime();
		m_Render->SetAlpha(m_Alpha);
		Move(CVector::BACK, UI_TRIGGER_MOVE_SPEED);
		if (0 == m_Dir)
		{
			Move(CVector::RIGHT, UI_TRIGGER_MOVE_SPEED);
		}
		else
		{
			Move(CVector::LEFT, UI_TRIGGER_MOVE_SPEED);
		}

	}
}

void UITrigger::Off()
{
	m_Delay -= GameTime::DeltaTime();

	if (m_Delay < 0.0f)
	{
		ChangeState(UITRIGGERSTATE::UI_IDLE);
		return;
	}
	else
	{
		m_Alpha -= GameTime::DeltaTime();
		m_Render->SetAlpha(m_Alpha);
		Move(CVector::FORWARD, UI_TRIGGER_MOVE_SPEED);
		if (0 == m_Dir)
		{
			Move(CVector::LEFT, UI_TRIGGER_MOVE_SPEED);
		}
		else
		{
			Move(CVector::RIGHT, UI_TRIGGER_MOVE_SPEED);
		}
	}
}

void UITrigger::Run()
{
	m_Delay = UI_DELAY_TIME_DEFAULT;
	m_Alpha = UI_ALPHA_MAX;

	if (true == GameInput::Down(L"TRIGGER2")) // TEST CODE
	{
		ChangeState(UITRIGGERSTATE::UI_OFF);
		return;
	}
}

void UITrigger::Init()
{
}

void UITrigger::Init(GameString _Name, UINT _Dir)
{
	if ( 0 == _Dir)
	{
		m_Dir = (UINT)UITRIGGERDIR::UI_R;
	}
	else
	{
		m_Dir = (UINT)UITRIGGERDIR::UI_L;
	}

	m_StateName[(unsigned int)UITRIGGERSTATE::UI_IDLE] = L"UI_IDLE";
	m_StateName[(unsigned int)UITRIGGERSTATE::UI_ON] = L"UI_ON";
	m_StateName[(unsigned int)UITRIGGERSTATE::UI_OFF] = L"UI_OFF";
	m_StateName[(unsigned int)UITRIGGERSTATE::UI_RUN] = L"UI_RUN";

	{
		ValueData::PIXEL_SCALE = 0.01f;
		ValueData::PIXEL_RATIO = 1.0f / ValueData::PIXEL_SCALE;
		m_Render = GetActor()->CreateCom<GameSpriteRenderer>((UINT)RENDER_ORDER::RO_UI);
		m_Render->SetSprite(_Name);
		m_Render->SetSrcSizeOfTexture(_Name);
		//m_Render->SetLScale({ 20.0f * ValueData::PIXEL_SCALE , 36.0f * ValueData::PIXEL_SCALE , 1.0f });
		m_Anim = GetActor()->CreateCom<GameAnimation>(m_Render);
	}

	m_Anim->CreateAni(L"UI_IDLE", _Name, 0, 0, 0.1f, true);
	m_Anim->CreateAni(L"UI_ON", _Name, 0, 0, 0.1f, false);
	m_Anim->CreateAni(L"UI_OFF", _Name, 0, 0, 0.1f, false);
	m_Anim->CreateAni(L"UI_RUN", _Name, 0, 1, 0.1f, true);

	m_Render->SetAlpha(m_Alpha);
	m_Render->Off();

	ChangeState(UITRIGGERSTATE::UI_IDLE);

}

void UITrigger::Update()
{
	switch (m_State)
	{
	case UITRIGGERSTATE::UI_IDLE: Idle();
		break;
	case UITRIGGERSTATE::UI_ON: On();
		break;
	case UITRIGGERSTATE::UI_OFF: Off();
		break;
	case UITRIGGERSTATE::UI_RUN: Run();
		break;
	case UITRIGGERSTATE::MAX:
		break;
	default:
		break;
	}
}

UITrigger::UITrigger()
	: m_Delay(UI_DELAY_TIME_DEFAULT)
	, m_Alpha(UI_ALPHA_MIN)
{
}

UITrigger::~UITrigger()
{
}

//
//void UITrigger::Init(const GameString& _SprName, float _Speed, int _Start, int _End, bool _Chk)
//{
//	{
//		m_Render = GetActor()->CreateCom<GameSpriteRenderer>((int)RENDER_ORDER::RO_UI);
//		m_Render->SetSprite(_SprName);
//		m_Render->SetSrcSizeOfTexture(_SprName);
//		m_Anim = GetActor()->CreateCom<GameAnimation>(m_Render);
//
//		CPtr<GameSprite> Sprite = GameSprite::Find(_SprName);
//
//		if (-1 == _Start)
//		{
//			m_Anim->CreateAni(L"DEFAULT", _SprName, 0, (int)Sprite->Count(), _Speed, _Chk);
//		}
//		else
//		{
//			m_Anim->CreateAni(L"DEFAULT", _SprName, _Start, _End, _Speed, _Chk);
//		}
//
//		m_Anim->ChangeAni(L"DEFAULT");
//	}
//}