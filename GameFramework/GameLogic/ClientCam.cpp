#include "ClientCam.h"
#include "ValueData.h"
#include "EnumData.h"
#include "Hero.h"

CPtr<GameActor> ClientCam::CamActor = nullptr;

void ClientCam::Move(const CVector& _Dir, float _Speed)
{
	GetTrans()->WMove(_Dir * GameTime::DeltaTime(_Speed));
}

void ClientCam::Join(CPtr<GameTransform> _Parent)
{
	GetActor()->GetTrans()->SetParent(_Parent);
}

void ClientCam::Withdraw()
{
	GetActor()->GetTrans()->SetParent(nullptr);
}

void ClientCam::Init()
{
	m_Cam = GetActor()->FindComType<GameCamera>();
	m_Cam = GetScene()->MainCam();
	if (nullptr == m_Cam)
	{
		MSG_ASSERT_CODE(L"�� component�� actor�� null�Դϴ�.");
	}

}

void ClientCam::Update()
{
}

ClientCam::ClientCam()	{}
ClientCam::~ClientCam() {}