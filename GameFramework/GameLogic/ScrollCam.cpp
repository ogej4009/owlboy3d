#include "ScrollCam.h"
#include "ValueData.h"
#include "EnumData.h"
#include "Hero.h"

void ScrollCam::Move(const CVector& _Dir, float _Speed)
{
	GetTrans()->WMove(_Dir * GameTime::DeltaTime(_Speed));
}

void ScrollCam::Join(CPtr<GameTransform> _Parent)
{
	GetActor()->GetTrans()->SetParent(_Parent);
}

void ScrollCam::Withdraw()
{
	GetActor()->GetTrans()->SetParent(nullptr);
}

void ScrollCam::Init()
{
	m_Cam = GetActor()->FindComType<GameCamera>();
	m_Cam = GetScene()->MainCam();
	if (nullptr == m_Cam)
	{
		MSG_ASSERT_CODE(L"이 component는 actor가 null입니다.");
	}
}

void ScrollCam::Update()
{

}

ScrollCam::ScrollCam() {}
ScrollCam::~ScrollCam() {}