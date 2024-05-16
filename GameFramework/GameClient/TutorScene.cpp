#include "TutorScene.h"
#include <ValueData.h>
#include <EnumData.h>
#include <GameTexture.h>
#include <GameSprite.h>
#include <GameSpriteRenderer.h>
#include <GameDebugPlus.h>
#include "TutorSceneObjUnity.h"

void TutorScene::Init()
{
	GetScene()->ColLink((UINT)COLLISION_ORDER::CO_PLAYER, (int)COLLISION_ORDER::CO_ENEMIES);
}

void TutorScene::Update()
{
	SceneDebugDisplay();

	// ���� 
	if (TRUE == GameInput::Down(L"NEXTPAGE"))
	{
		GameScene::ChangeScene(L"STAGE1");
	}
}

void TutorScene::SceneChangeStart()
{
	// �ʼ� ������ �ʱ�ȭ 
	SceneValueDataInit();

	// ���ϱ���
	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Local");
		Dic.Move(L"TutorScene");
		auto FileList = Dic.DirAllFile();
		for (auto& _File : FileList)
		{
			GameTexture::Load(_File);
		}
		for (auto& _File : FileList)
		{
			GameSprite::Create(_File.FileName(), 1, 1);
		}
	}

	// ī�޶� 
	{
		// ����
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos(ValueData::CAM_DEF_POS);
		// ��Ϻ�
		CPtr<GameCamera> NewCam = NewActor->CreateCom<GameCamera>(0, (UINT)RENDER_ORDER::RO_ACTOR, (UINT)RENDER_ORDER::RO_COL_LEVEL);
		NewCam->SetCamSize({ 6.4f, 3.6f });
		NewCam->SetMode(CAMMODE::PERS);
		// ������Ʈ 
		CPtr<ClientCam> CCam = NewActor->CreateCom<ClientCam>(); // <<< ��� 
 	}

	{
		// ����
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos(ValueData::CAM_DEF_POS);
		// ��Ϻ�
		CPtr<GameCamera> NewCam = NewActor->CreateCom<GameCamera>(1, (UINT)RENDER_ORDER::RO_UI);
		NewCam->SetCamSize({ 6.4f, 3.6f });
		NewCam->SetMode(CAMMODE::ORTH);
		// ������Ʈ 
		// CPtr<UICam> UICam = NewActor->CreateCom<UICam>(); // <<< ���
	}

	// UI 
	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->CreateCom<Cursor>();
	}

	// �ȼ��浹
	{
		CVector Coord;
		Coord.X = ValueData::STAGE_SCALE.X * 0.5f;
		Coord.Y = ValueData::STAGE_SCALE.Y * -0.5f;
		Coord.Z = ValueData::DEBUG_DEFAULT_Z_ORDER;

		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWScale(ValueData::STAGE_SCALE);
		NewActor->GetTrans()->SetWPos(Coord);

		CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>((UINT)RENDER_ORDER::RO_COL_LEVEL);
		NewRender->SetSprite(ValueData::STAGE_NAME);
		NewRender->Off();
	}

	// �÷��̾�
	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos(ValueData::PLAYER_DEFAULT_POS_INSTAGE);
		NewActor->CreateCom<Hero>();
	}

	// 
}

void TutorScene::SceneChangeEnd()
{
	// �����
	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Local");
		Dic.Move(L"TutorScene");
		auto FileList = Dic.DirAllFile();
		for (auto& _File : FileList)
		{
			GameTexture::Delete(_File.FileName());
		}
		for (auto& _File : FileList)
		{
			GameSprite::Delete(_File.FileName());
		}
	}
	GetScene()->ActorClear();

}

void TutorScene::SceneDebugDisplay()
{
	// ����� ON/OFF
	if (true == GameInput::Down(L"DEBUG"))
	{
		if (false == m_Debug->IsUpdateObj())
		{
			m_Debug->On();
		}
		else
		{
			m_Debug->Off();
		}
	}

	// FPS ���
	wchar_t Arr[256] = { 0, };
	m_FpsTime -= GameTime::DeltaTime();

	if (0 >= m_FpsTime)
	{
		m_FpsResult = 1.0f / GameTime::DeltaTime();
		m_FpsTime = 1.0f;
	}

	swprintf_s(Arr, L" FPS : %f", m_FpsResult);
	GameDebugPlus::DrawDebugText(Arr, 30.0f, CVector(0.0f, 0.0f, -9.0f), CVector::WHITE);

	//swprintf_s(Arr, L" LEVEL : %s", ValueData::STAGE_NAME);
	//GameDebugPlus::DrawDebugText(Arr, 30.0f, CVector(0.0f, 30.0f, -9.0f), CVector::WHITE);

	// ����� HUD �߰� 
	// add ..
	// add ..
}

void TutorScene::SceneValueDataInit()
{
	ValueData::STAGE_NAME = L""; // �̸� 
	ValueData::STAGE_SCALE = { 1.0f, 1.0f }; // TEX -> GET ũ�� 
	ValueData::PLAYER_DEFAULT_POS_INSTAGE = { 0.0f, 0.0f, ValueData::PLAYER_DEFAULT_Z_ORDER }; // ��ġ 
}

TutorScene::TutorScene()
{
}

TutorScene::~TutorScene()
{
}
