#include "GameTransform.h"
#include "GameActor.h"
#include "GameScene.h"
#include "GameCamera.h"
//#include <GameString.h>
#include "GameSprite.h"
#include <GameDebug.h>
///////////////////////////////////////////////
#include "GameDebugPlus.h"
#include "GameLight.h"
#include "GameCol.h" // �̰�Ȯ���غ��� 

/* ���������� �Լ� �ȿ��� �� Ȯ���Ѵ�. */

#pragma region �Լ������� 
	/*
	*/
#pragma endregion
bool (*GameTransform::COLFUNC[(int)COLTYPE::MAX][(int)COLTYPE::MAX])(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right) = { nullptr, };

GameTransform::GameColStarter GameTransform::Starter;

GameTransform::GameColStarter::GameColStarter()
{
	GameTransform::COLFUNC[(int)COLTYPE::AABB2D][(int)COLTYPE::AABB2D] = AABB2DCOLAABB2D;
	GameTransform::COLFUNC[(int)COLTYPE::AABB2D][(int)COLTYPE::SPHERE2D] = AABB2DCOLSPHERE2D;
	GameTransform::COLFUNC[(int)COLTYPE::AABB2D][(int)COLTYPE::OBB2D] = AABB2DCOLOBB2D;

	GameTransform::COLFUNC[(int)COLTYPE::OBB2D][(int)COLTYPE::AABB2D] = OBB2DCOLAABB2D;
	GameTransform::COLFUNC[(int)COLTYPE::OBB2D][(int)COLTYPE::SPHERE2D] = OBB2DCOLSPHERE2D;
	GameTransform::COLFUNC[(int)COLTYPE::OBB2D][(int)COLTYPE::OBB2D] = OBB2DCOLOBB2D;

	GameTransform::COLFUNC[(int)COLTYPE::SPHERE2D][(int)COLTYPE::AABB2D] = SPHERE2DCOLAABB2D;
	GameTransform::COLFUNC[(int)COLTYPE::SPHERE2D][(int)COLTYPE::SPHERE2D] = SPHERE2DCOLSPHERE2D;
	GameTransform::COLFUNC[(int)COLTYPE::SPHERE2D][(int)COLTYPE::OBB2D] = SPHERE2DCOLOBB2D;

	GameTransform::COLFUNC[(int)COLTYPE::RAY3D][(int)COLTYPE::AABB2D] = RAYCOLAABB2D;
	GameTransform::COLFUNC[(int)COLTYPE::RAY3D][(int)COLTYPE::OBB2D] = RAYCOLOBB2D;
	GameTransform::COLFUNC[(int)COLTYPE::RAY3D][(int)COLTYPE::SPHERE2D] = RAYCOLSPHERE2D;
	GameTransform::COLFUNC[(int)COLTYPE::RAY3D][(int)COLTYPE::RAY3D] = RAYCOLRAY;
}

// ���ͷ��ʱ�ȭ����(==����ʱ�ȭ) -> ��������� �������ڸ��� �ʱ�ȭ �Ǵ°� 
// m_LPos(CVector::ZERO)
GameTransform::GameTransform()
	: m_LPos(CVector::ZERO), m_LScale(CVector::ONE), m_LRot(CVector::ZERO)
	, m_WPos(CVector::ZERO), m_WScale(CVector::ONE), m_WRot(CVector::ZERO)
	, m_TD(), CalMatrixCheck{ true, }, m_Parent(nullptr), m_TD_Plus() //, TransDataNeeds
{
	memset(&CalMatrixCheck, 1, sizeof(CalMatrixCheck));
	m_TD.CalUnitMatrix();
	m_TD_Plus.CalUnitMat(); // �߰� 
	m_TD_Plus.FloatSetting(10.0f, 50.0f, 0.05f, 0.1f); // �߰� 
}


#pragma region SetParent()�Լ��� �ǹ� 
/*
	������ �θ� �Ǿ��ش�.
	== ���� �θ��� SceneList -> �� �θ��� ChildList�� ����.
	== ������ �θ� ����� ���� m_AllTrans(Ʈ����������Ʈ)���� �����°Ŵ�.
	�θ� ����� �ѹ� CalMatrixCheck(����) �Ѵ�.
*/
#pragma endregion

#pragma region remove�Լ�
/* remove�Լ� : �Ȱ��� ���� ������ list �ȿ��� ������ erase() ��� ���°�. -> iterator */
#pragma endregion

void GameTransform::SetParent(CPtr<GameTransform> _Parent)
{
	GetActor()->GetScene()->m_AllTrans.remove(this);

	if (nullptr != _Parent)
	{
		// ������ �θ𰡾��°�� == ������ �ֻ���
		if (nullptr != m_Parent)
		{
			m_Parent->m_ChildList.remove(this);
		}

		_Parent->m_ChildList.push_back(this);
		CalMatrixCheck[(int)MATTYPE::MATTYPE_PARENT] = true;
		m_TD.PARENT = _Parent->m_TD.WWORLD;
		m_Parent = _Parent;

		// ���� : ũ��->ȸ��->�̵�
		SetLScale(GetWScale());
		SetLRot(GetWRot());
		SetLPos(GetWPos());

	}
	else
	{
		if (nullptr != m_Parent)
		{
			m_Parent->m_ChildList.remove(this);
		}

		GetActor()->GetScene()->m_AllTrans.push_back(this);

		// ���� �߿��ϴ�. 
		CalWPos();
		CalWScale();
		CalWRot();

		m_Parent = nullptr;
		m_TD.PARENT.UnitMat();
		// �� ���� LPos�� �� w�̴� 

		// ���� �߿��ϴ�. 
		SetLPos(GetWPos());
		SetLScale(GetWScale());
		SetLRot(GetWRot());


	}

	// ȯ���� �������Ƿ� ����� (���������) �����Ѵ�. 
	TransformUpdate();
}



void GameTransform::Init()
{
	m_bDebug = false;
	/////////////////////////////////////////////////
	if (nullptr != GetActor()->m_Trans)
	{
		MSG_ASSERT_CODE(L"�� ���Ϳ� Ʈ�������� 2���� ������ �����ϴ�.");
	}

	GetActor()->m_Trans = this;

	GetActor()->GetScene()->m_AllTrans.push_back(this);
	// �ؼ� : �� ���� Actor�� Scene�� transform�� ��Ƴ��� ���� �ڽ��� �־�Ӵϴ�. 
}


void GameTransform::TransformUpdate()
{
	// ���͸� Ȱ���ؼ� ����� ����� ���� ������ ���� ��� �۾��̴�. 
	// �׷��� Pos, Rot, Scale�� �����Ǿ��� ���� ����� ����ؼ� ȿ���� ���̰��� �Ѵ�. 

	if (true == CalMatrixCheck[(int)MATTYPE::MATTYPE_SCALE])
	{
		m_TD.SCALE.Scale3d(m_LScale);
		CalMatrixCheck[(int)MATTYPE::MATTYPE_LWORLD] = true;
	}

	if (true == CalMatrixCheck[(int)MATTYPE::MATTYPE_ROT])
	{
		m_TD.ROT.RotDeg(m_LRot);
		CalMatrixCheck[(int)MATTYPE::MATTYPE_LWORLD] = true;
	}

	if (true == CalMatrixCheck[(int)MATTYPE::MATTYPE_POS])
	{
		m_TD.POS.Pos3d(m_LPos);
		CalMatrixCheck[(int)MATTYPE::MATTYPE_LWORLD] = true;
	}

	// ũ�� ���� �̵� ����		-> ����(LWORLD)
	// ũ�� ���� �̵� ���� �θ� -> ����(WWORLD)
	if (true == CalMatrixCheck[(int)MATTYPE::MATTYPE_LWORLD] ||
		true == CalMatrixCheck[(int)MATTYPE::MATTYPE_PARENT])
	{
		m_TD.CalLWorld();
		m_TD.CalWWorld();

		// CalLWorld()�� ����ϴ� ���, Wpos�� ����Ǵ°�
		// ���� WWorld�� ����Ǿ��ٴ� �ǹ̷� ���� TRUE�� ����

		CalMatrixCheck[(int)MATTYPE::MATTYPE_WWORLD] = true;

		if (nullptr != m_Parent)
		{
			CalWScale();
			CalWRot();
			CalWPos();
		}
	}

	for (auto& _Child : m_ChildList)
	{
		// == �̹� �������� ����� ������ �־���
		// ���� ����������, �θ������ ���ߴٸ� ���� ����� �ٽ� ����ؾ� �Ѵ�. 
		if (true == CalMatrixCheck[(int)MATTYPE::MATTYPE_WWORLD])
		{
			_Child->CalMatrixCheck[(int)MATTYPE::MATTYPE_PARENT] = true;
			_Child->m_TD.PARENT = m_TD.WWORLD;
		}

		// �θ������ ����� �ݵ�� ���� �Ѵ�. 
		_Child->TransformUpdate();
	}

	memset(&CalMatrixCheck, 0, sizeof(CalMatrixCheck));
}

#pragma region ���̰����ִ°�==CamUpdate
/*
	�÷��̾�� �����δ�. (����� ��������)
	������� ���ߴ�. �ȿ����ΰ�ó�� �Ǿ���.
	�����θ�ŭ ��Ŀ��� ���־�� ���������� ǥ���� ���̴�. CalWVP()
	���⼭ �����ش�.
*/
#pragma endregion

void GameTransform::CamUpdate(CPtr<GameCamera> _Cam)
{
	m_TD.PROJ = _Cam->m_Proj;
	m_TD.VIEW = _Cam->m_View;
	m_TD.CalWVP();
	///////////////////////////////////////////////////////
	m_TD_Plus.Pos = _Cam->GetTrans()->GetWPos();
	m_TD_Plus.Pos.Y = 0.0f;
}

void GameTransform::ColCheck()
{
	{
		std::map<int, std::list<CPtr<GameCol>>>::iterator Start = GetScene()->m_AllCol.begin();
		std::map<int, std::list<CPtr<GameCol>>>::iterator End = GetScene()->m_AllCol.end();

		for (; Start != End; ++Start)
		{
			std::list<CPtr<GameCol>>::iterator StartCol = Start->second.begin();
			std::list<CPtr<GameCol>>::iterator EndCol = Start->second.end();

			for (; StartCol != EndCol; )
			{
				if (true == (*StartCol)->IsDeathObj())
				{
					StartCol = Start->second.erase(StartCol);
				}
				else
				{
					++StartCol;
				}

			}

		}
	}
}


bool GameTransform::Col(COLTYPE _ThisType, CPtr<GameTransform> _Trans, COLTYPE _OtherType)
{
	if (nullptr == COLFUNC[(int)(_ThisType)][(int)(_OtherType)])
	{
		MSG_ASSERT_CODE(L"�浹 �Լ��� �������� ���� �浹�� �Ϸ��� �߽��ϴ�.");
	}

	return COLFUNC[(int)(_ThisType)][(int)(_OtherType)](this, _Trans);


}

#pragma region �پ������̽��浹
/*
	AABB ȸ������ ���� �ڽ�
	ex)
		DirectX::BoundingOrientedBox	ColThis;
		DirectX::BoundingBox			ColOther;

	ex)
		XMFLOAT3   CVector
		ColThis.Center = GetWPos();(���Ϸ���)

	���Ϸ����� �־��ָ� ȸ���� �ν����� ���Ѵ�.
	Orientation������� �־���� �ѹ��� ȸ������� ���� ȸ���� �νĵȴ�.
	������� ���� == �����ϱ� ����� ���Ҽ�, ��� ����� ���յ� ����� ����Ѵ�.


	ȸ������ ��׸��� �������� �ٲ��, �ٽ� ���ʹϿ��� �ؼ� ȸ���ϴµ�. WROT() ��ü�� �׳� ��׸��� ���̴�.
	ColThis.Orientation = WROT();
	DirectX::XMQuaternionRotationRollPitchYaw()

	//ColThis.Extents = GetWScale().HalfVec();
	//ColOther.Center = _Trans->GetWPos();
	//ColOther.Extents = _Trans->GetWScale().HalfVec();

	if ((int)_ThisType < (int)COLTYPE::SPHERE3D)
	{
		ColThis.Center.z = 0.0f;
	}

	if ((int)_OtherType < (int)COLTYPE::SPHERE3D)
	{
		ColOther.Center.z = 0.0f;
	}

	Intersects �� �Լ��� �߿��ϴ�.
	//return ColThis.Intersects(ColOther);

	// ��
	DirectX::BoundingSphere m_Sphere1;
	DirectX::BoundingSphere m_Sphere2;

	// OBB ȸ���� �ڽ�
	DirectX::BoundingOrientedBox m_OBBox1;
	DirectX::BoundingOrientedBox m_OBBox2;
	m_AABBBox1.Intersects(m_Sphere2);

	�⺻ ���� �浹�� üũ�Ҽ� �ִ�.
	�Ž��浹�� �� �� �ִ�.
	A�Ž��� �ﰢ���� 2000��
	B�Ž��� �ﰢ���� 1200��
	���ο���	�ﰢ�� VS �ﰢ��
				�ﰢ�� VS ���
				�ﰢ�� VS ����
	DirectX::TriangleTests::Intersects()
*/
#pragma endregion


DirectX::BoundingBox GameTransform::AABB2D()
{
	return DirectX::BoundingBox(GetWPos2d(), GetWScale().HalfVec().AbsVector()); //�� �����
}


DirectX::BoundingSphere GameTransform::SPHERE2D()
{
	return DirectX::BoundingSphere(GetWPos2d(), abs(GetWScale().HalfVec().X));
}


DirectX::BoundingOrientedBox GameTransform::OBB2D()
{
	return DirectX::BoundingOrientedBox(GetWPos2d(), GetWScale().HalfVec().AbsVector(), GetWRot().DegToQ());
}

DirectX::BoundingBox GameTransform::AABB3D()
{
	return DirectX::BoundingBox(GetWPos(), GetWScale().HalfVec().AbsVector());
}

DirectX::BoundingSphere GameTransform::SPHERE3D()
{
	return DirectX::BoundingSphere(GetWPos(), abs(GetWScale().HalfVec().X));
}

DirectX::BoundingOrientedBox GameTransform::OBB3D()
{
	CVector Pos = GetWPos();
	CVector Scale = GetWScale();
	CVector Rot = GetWRot();
	return DirectX::BoundingOrientedBox(GetWPos(), GetWScale().HalfVec().AbsVector(), GetWRot().DegToQ());
}


DirectX::SimpleMath::Ray GameTransform::RAY3D()
{
	/*HVECTOR Pos = WPOS2D();
	HVECTOR Scale = WSCALE();
	HVECTOR Rot = WROT();*/

	// DirectX::SimpleMath::Ray(WPOS().DXVEC, WFORWARD().DXVEC).Intersects()

	return DirectX::SimpleMath::Ray(GetWPos().DXVEC, WForward().DXVEC);
}


CVector GameTransform::Convert(CVector Pos, int ScreenWidth, int ScreenHeight)
{
	CMatrix PV = m_TD.PROJ * m_TD.VIEW;
	Pos = Pos * PV;
	/*pos.x = ScreenWidth * (pos.x + 1.0) / 2.0;
	pos.y = ScreenHeight * (1.0 - ((pos.y + 1.0) / 2.0));*/

	return Pos;
}



float GameTransform::MouseRot(CVector _MousePos)
{


	CMatrix CamView = GetScene()->MainCam()->m_View;
	CMatrix CamProj = GetScene()->MainCam()->m_Proj;

	CVector asd = (GetWPos() * CamView * CamProj) * 0.5f;

	asd.X = (asd.X / asd.Z) * 12.8f * 0.5f;
	asd.Y = (asd.Y / asd.Z) * 7.2f * 0.5f;


	if (true == m_bDebug)
	{
		GameDebugPlus::DrawDebugText(L"x : %f, y : %f", asd.X, asd.Y);
	}


	_MousePos = asd - _MousePos * 0.01f;

	_MousePos.Normal3dVecReturn();

	return CVector::DirToDirAngle2D(_MousePos, CVector::RIGHT);

}

float GameTransform::NpcRot(CVector _PlayerPos)
{


	CMatrix CamView = GetScene()->MainCam()->m_View;
	CMatrix CamProj = GetScene()->MainCam()->m_Proj;

	CVector asd = (GetWPos() * CamView * CamProj) * 0.5f;

	asd.X = (asd.X / asd.Z) * 12.8f * 0.5f;
	asd.Y = (asd.Y / asd.Z) * 7.2f * 0.5f;


	if (true == m_bDebug)
	{
		GameDebugPlus::DrawDebugText(L"Cam_x : %f, Cam_y : %f", asd.X, asd.Y);
	}


	_PlayerPos = asd - _PlayerPos * 0.01f;

	_PlayerPos.Normal3dVecReturn();

	return CVector::DirToDirAngle2D(_PlayerPos, CVector::RIGHT);

}


void GameTransform::LightUpdate(const LightData& _Light)
{
	m_TD.PROJ = _Light.m_Proj;
	m_TD.VIEW = _Light.m_View;
	m_TD.CalWVP();
}

CVector GameTransform::WinPosToSceenRatio(CVector _WinPos)
{
	CVector Return = CVector();

	float Ratio = GameWin::MainObj()->Size().X / GetScene()->MainCam()->GetCamSize().X;

	Return = _WinPos / Ratio;

	return Return;

}


CVector GameTransform::WinPosToSceenRatioStatic(CVector _WinPos)
{
	CVector Return = CVector();

	Return = _WinPos * 0.01f;

	return Return;
}


void GameTransform::SetSrcSizeOfTexture(const GameString& _Name) // Get Source texture Size 
{
	CPtr<GameSprite> _Sprite = GameSprite::Find(_Name);

	if (nullptr == _Sprite)
	{
		MSG_ASSERT_CODE(_Name + L"�� �ؽ�ó�� ã�� ���߽��ϴ�.");
	}

	SetWScale({ _Sprite->Tex()->Size().X * 0.01f / (int)_Sprite->Count(), _Sprite->Tex()->Size().Y * 0.01f , 1.0f});

}

