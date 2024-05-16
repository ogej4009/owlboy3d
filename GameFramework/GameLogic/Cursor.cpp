#include "Cursor.h"
#include "ValueData.h"
#include "EnumData.h"
#include <GameCol.h>
#include "Hero.h"

void Cursor::CheckState()
{
	// �÷��̾��� ���¸� �׻�Ȯ���Ѵ�. 
	// m_bPickUp / m_bShot
}

void Cursor::Fit()
{
	// �� �� ���� ũ�⸦ ���ߴ� ȿ���� �����ش�.
	m_Time -= GameTime::DeltaTime();
	m_Scale.X -= GameTime::DeltaTime();
	m_Scale.Y -= GameTime::DeltaTime();
	m_Render->SetLScale(m_Scale);

	if (m_Time <= 0.0f)
	{
		return;
	}
}

void Cursor::ChangeState(CURSORSTATE _State)
{
	m_State = _State;
	m_Anim->ChangeAni(m_StateName[(UINT)_State]);
}

void Cursor::Idle()
{
	// �׻� ���� ������ �ʱ�ȭ �Ѵ�. 
	//m_Scale = { CURSOR_IMG_SIZE_MAX, CURSOR_IMG_SIZE_MAX };
	//m_Time = CURSOR_DEFAULT_TIME_LIMIT;
}

void Cursor::PickUpAiming()
{
	// Fit(); // �ѹ��� ���δ�. 
	// m_bPickUp�� ���� üũ > Idle()
	// m_bShot�� ���� üũ > Shooting()
}

void Cursor::Shooting()
{
	// DownŬ�� > PickUpAiming()
}

void Cursor::Init()
{

	m_StateName[(unsigned int)CURSORSTATE::IDLE] = L"IDLE";
	m_StateName[(unsigned int)CURSORSTATE::PICKUP_AIMING] = L"PICKUP_AIMING";
	m_StateName[(unsigned int)CURSORSTATE::SHOOTING] = L"SHOOTING";
	
	{
		m_Render = GetActor()->CreateCom<GameSpriteRenderer>((UINT)RENDER_ORDER::RO_UI);
		m_Render->SetLScale({ 0.36f, 0.36f, 1.0f });
	}
	
	{
		m_ColRender = GetActor()->CreateCom<GameSpriteRenderer>((int)RENDER_ORDER::RO_ACTOR);
		m_ColRender->SetLScale({ 0.36f, 0.36f, 1.0f });
		m_ColRender->SetSprite(L"sprRect_100x100.png");
	}

	{
		m_Col = GetActor()->CreateCom<GameCol>((int)COLLISION_ORDER::CO_CURSOR);
		m_Col->SetLScale({ 0.36f, 0.36f, 1.0f });
		m_Col->ColType(COLTYPE::AABB2D);
	}

	{
		m_Anim = GetActor()->CreateCom<GameAnimation>(m_Render);
		m_Anim->CreateAni(L"IDLE", L"sprCursor_36x36_6x3.png", 0, 0, 0.1f, false);
		m_Anim->CreateAni(L"PICKUP_AIMING", L"sprCursor_36x36_6x3.png", 6, 11, 0.1f, true);
		m_Anim->CreateAni(L"SHOOTING", L"sprCursor_36x36_6x3.png", 12, 17, 0.1f, true);
	}

	ChangeState(CURSORSTATE::IDLE);
}

void Cursor::Update()
{
	m_Pos = GetActor()->GetScene()->MainCam()->OrthWorldMousePos2d();
	m_Render->SetLPos(m_Pos + ValueData::CAM_DEF_POS); // SetLPos()?
	m_ColRender->SetLPos(m_Pos + ValueData::CAM_DEF_POS);

	switch (m_State)
	{
	case CURSORSTATE::IDLE:
		Idle();
		break;
	case CURSORSTATE::PICKUP_AIMING:
		PickUpAiming();
		break;
	case CURSORSTATE::SHOOTING:
		Shooting();
		break;
	case CURSORSTATE::MAX:
		break;
	default:
		break;
	}
}

Cursor::Cursor() {}
Cursor::~Cursor() {}