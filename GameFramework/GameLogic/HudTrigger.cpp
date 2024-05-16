#include "HudTrigger.h"
#include "ValueData.h"
#include "EnumData.h"

CPtr<GameTexture> HudTrigger::m_Tex;

void HudTrigger::Move(const CVector& _Dir, float _Speed)
{
	GetTrans()->WMove(_Dir * GameTime::DeltaTime(_Speed));
}

void HudTrigger::Idle()
{
	m_Delay = HUD_DELAY_TIME_DEFAULT;
	m_Alpha = HUD_ALPHA_MIN;

	if (true == GameInput::Down(L"TRIGGER")) // TEST CODE
	{
		ChangeState(HUDTRIGGERSTATE::HUD_ON);
		return;
	}
}

void HudTrigger::On()
{
	// OFF > ON : Y값, Z값이 커진다. 
	// SPR도 투명or꺼짐에서 선명or켜짐으로 
	m_Delay -= GameTime::DeltaTime();

	if (m_Delay < 0.0f)
	{
		ChangeState(HUDTRIGGERSTATE::HUD_RUN);
		return;
	}
	else
	{
		m_Alpha += GameTime::DeltaTime();
		m_Render->SetAlpha(m_Alpha);
		Move(CVector::FORWARD, HUD_UP_DOWN_SPEED);
		Move(CVector::UP, HUD_UP_DOWN_SPEED);
	}

}

void HudTrigger::Off()
{
	m_Delay -= GameTime::DeltaTime();

	if (m_Delay < 0.0f)
	{
		ChangeState(HUDTRIGGERSTATE::HUD_IDLE); 
		return;
	}
	else
	{
		m_Alpha -= GameTime::DeltaTime();
		m_Render->SetAlpha(m_Alpha);
		Move(CVector::BACK, HUD_UP_DOWN_SPEED);
		Move(CVector::DOWN, HUD_UP_DOWN_SPEED);
	}
}

void HudTrigger::Run()
{
	m_Delay = HUD_DELAY_TIME_DEFAULT;
	m_Alpha = HUD_ALPHA_MAX;

	if (true == GameInput::Down(L"TRIGGER2")) // TEST CODE
	{
		ChangeState(HUDTRIGGERSTATE::HUD_OFF);
		return;
	}
}

void HudTrigger::ChangeState(HUDTRIGGERSTATE _State)
{
	m_State = _State;
	m_Anim->ChangeAni(m_StateName[(UINT)_State]);
}

void HudTrigger::Init()
{
}

void HudTrigger::Init(GameString _Name)
{
	m_StateName[(unsigned int)HUDTRIGGERSTATE::HUD_IDLE] = L"HUD_IDLE";
	m_StateName[(unsigned int)HUDTRIGGERSTATE::HUD_ON] = L"HUD_ON";
	m_StateName[(unsigned int)HUDTRIGGERSTATE::HUD_OFF] =  L"HUD_OFF";
	m_StateName[(unsigned int)HUDTRIGGERSTATE::HUD_RUN] = L"HUD_RUN";


	{
		ValueData::PIXEL_SCALE = 0.01f;
		ValueData::PIXEL_RATIO = 1.0f / ValueData::PIXEL_SCALE;
		m_Render = GetActor()->CreateCom<GameSpriteRenderer>((UINT)RENDER_ORDER::RO_UI);
		m_Render->SetLScale({ 20.0f * ValueData::PIXEL_SCALE , 36.0f * ValueData::PIXEL_SCALE , 1.0f });
		m_Anim = GetActor()->CreateCom<GameAnimation>(m_Render);
	}

	m_Anim->CreateAni(L"HUD_IDLE", _Name, 0, 0, 0.1f, true);
	m_Anim->CreateAni(L"HUD_ON", _Name, 0, 0, 0.1f, false);
	m_Anim->CreateAni(L"HUD_OFF", _Name, 0, 0, 0.1f, false);
	m_Anim->CreateAni(L"HUD_RUN", _Name, 0, 1, 0.1f, true);

	m_Render->SetAlpha(m_Alpha);
	m_Render->Off();
	ChangeState(HUDTRIGGERSTATE::HUD_IDLE);
}

void HudTrigger::Update()
{
	switch (m_State)
	{
	case HUDTRIGGERSTATE::HUD_IDLE: Idle();
		break;	
	case HUDTRIGGERSTATE::HUD_ON: On();
		break;	
	case HUDTRIGGERSTATE::HUD_OFF: Off();
		break;
	case HUDTRIGGERSTATE::HUD_RUN: Run();
		break;
	case HUDTRIGGERSTATE::MAX:
		break;
	default:
		break;
	}
}

HudTrigger::HudTrigger() 
	: m_Delay(HUD_DELAY_TIME_DEFAULT)
	, m_Alpha(HUD_ALPHA_MIN)
{
}

HudTrigger::~HudTrigger()
{
}
