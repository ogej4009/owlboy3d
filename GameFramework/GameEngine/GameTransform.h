#pragma once
#include "GameComponent.h"

enum class COLTYPE
{
	SPHERE2D,
	AABB2D,
	OBB2D,
	SPHERE3D,
	AABB3D,
	OBB3D,
	RAY3D,
	MAX,
};

struct RayData
{
	float4 Src;
	float4 Dir;
};

struct LightData;
class GameCamera;
class GameTransform : public ActorComponent
{
private:
	class GameColStarter
	{
	public:
		GameColStarter();
		~GameColStarter() {}
	};
	friend GameColStarter; // �̰͸� ����ϱ�
	static GameColStarter Starter;

public:
	static bool __stdcall SPHERE2DCOLOBB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall SPHERE2DCOLAABB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall SPHERE2DCOLSPHERE2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall SPHERE2DCOLRAY(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall AABB2DCOLOBB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall AABB2DCOLAABB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall AABB2DCOLSPHERE2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall AABB2DCOLRAY(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall OBB2DCOLOBB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall OBB2DCOLAABB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall OBB2DCOLSPHERE2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall OBB2DCOLRAY(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall RAYCOLSPHERE2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall RAYCOLAABB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall RAYCOLOBB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall RAYCOLRAY(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);

	static bool(__stdcall* COLFUNC[(int)COLTYPE::MAX][(int)COLTYPE::MAX])
		(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);

public:
	bool m_bDebug;

protected:
	CVector m_LPos;
	CVector m_LScale;
	CVector m_LRot;
	CVector m_WPos;
	CVector m_WScale;
	CVector m_WRot;

	bool CalMatrixCheck[(int)MATTYPE::MATTYPE_MAX]; // �����üũ

	CTransformData m_TD;
	CTransDataPlus m_TD_Plus;

	GameTransform* m_Parent;
	std::list<GameTransform*> m_ChildList;

public:	
	CTransformData GetTransData()
	{
		return m_TD;
	}
	
	const CTransformData& GetCTransData()
	{
		return m_TD;
	}

	CTransformData* GetPTransData() 
	{
		return &m_TD;
	}

public:
	GameTransform* GetParent()
	{
		return m_Parent;
	}

	void SetParent(CPtr<GameTransform> _Parent);

public:
	CTransDataPlus GetTransDataPlus()
	{
		return m_TD_Plus;
	}

	const CTransDataPlus& CRTransDataPlus()
	{
		return m_TD_Plus;
	}

	CTransDataPlus* PTransDataPlus()
	{
		return &m_TD_Plus;
	}

public:
	GameTransform();

public:
	// ũ�� ���� �̵� ����		-> ����(LWORLD)
	// ũ�� ���� �̵� ���� �θ� -> ����(WWORLD)
	CVector GetLPos() { return m_LPos; }
	CVector GetLScale() { return m_LScale; }
	CVector GetLRot() { return m_LRot; }
	CVector GetWPos() { return m_WPos; }
	CVector GetWScale() { return m_WScale; }
	CVector GetWRot() { return m_WRot; }
	CVector GetWPos2d() { return CVector(m_WPos.X, m_WPos.Y, 0.0f, m_WPos.W); }

	const CVector& CRWPOS()
	{
		return m_WPos;
	}

	CVector WinPosToSceenRatio(CVector _WinPos);
	static CVector WinPosToSceenRatioStatic(CVector _WinPos);

public:
	void CalWPos()
	{
		DEBUG_CHECK;
		// m_LPos�� ������ �ִ� ���¸� ����� �����ϴ�.(����)
		// ���� �������� ����ϴ� ���̴�.(����)
														// <�׽�Ʈ> 
		CVector POS = m_LPos * m_Parent->GetWScale(); // [������ ������] �� [�θ��� ������] �� ���Ѵ�. 
		CVector ROT = GetWRot();						// [������ ȸ��]
		CVector RESULTQ = POS.RotDegReturn(ROT);		// [����� ����� �Լ�] 

		/* 
		if (IsDebug())
		{
			CVector Scale = m_PARENT->WSCALE();
			CVector Pos = m_LPOS * m_PARENT->WSCALE();
			Pos = Pos.RotDegReturn(m_PARENT->WROT());
			Pos = m_PARENT->WPOS() + Pos;
		}	
		*/



		// �����ڵ��� �߸��� �� [1] 
		// m_WPos = m_Parent->GetWPos() + ((m_LPos * m_Parent->GetWScale()).RotDegReturn(GetWRot()));
		// �θ��� WRot������ ��ģ��. 
		// WRot()�� ������ ����� ���̴�. �̰��� ���� Pos�� ������ �ְ� �־���.

		// �����ڵ��� �߸��� �� [2]
		// m_WPos = m_Parent->GetWPos() + ((m_LPos * m_Parent->GetWScale()).RotDegReturn(m_Parent->GetWRot()));
		// ������ WPos�� ���ϴ� �߿� LPos�� ȸ����Ų��.  
		// ���� ũ�⸦ Ű���. ũ�⸦ ��������ϱ⿡ -1 �����Ϸ� ������ ��ġ�� ������ ���� �ʴ´�. 
		m_WPos = m_Parent->GetWPos() + (m_LPos.RotDegReturn(m_Parent->GetWRot()) * m_Parent->GetWScale());
	}

	void CalWRot()
	{
		m_WRot = m_Parent->GetWRot() + m_LRot; // [�θ��� ����ȸ��] �� [����ȸ��] �� ���Ѵ�. 
	}

	void CalWScale()
	{
		m_WScale = m_Parent->GetWScale() * m_LScale; // [�θ��� ���彺����] �� [���ý�����] �� ���Ѵ�.  
	}

	void CalChildPos()
	{
		for (auto& _Child : m_ChildList)
		{
			_Child->CalWPos();
		}
	}

	void CalChildRot()
	{
		for (auto& _Child : m_ChildList)
		{
			_Child->CalWRot();
		}
	}

	void CalChildScale()
	{
		for (auto& _Child : m_ChildList)
		{
			_Child->CalWScale();
		}
	}

	void SetLPos(const CVector& _Value)
	{
		// �θ� ���� ���, L==W �̴�. 
		if (nullptr == m_Parent)	// �θ𰡾��°��==�ֻ���
		{
			m_LPos = m_WPos = _Value;
			CalMatrixCheck[(int)MATTYPE::MATTYPE_POS] = true;
			CalChildPos();
			return;
		}

		// �θ� �ִ� ���, LPos --> LPos, WPos --> �θ��� �������� ����� �̵������ �Ѵ�. 
		m_LPos = _Value;
		CalWPos();
		CalChildPos();
		CalMatrixCheck[(int)MATTYPE::MATTYPE_POS] = true;
	}

	void SetWPos(const CVector& _Value)
	{
		if (nullptr == m_Parent)	// �θ𰡾��°��==�ֻ���
		{
			m_LPos = m_WPos = _Value;
			CalMatrixCheck[(int)MATTYPE::MATTYPE_POS] = true;
			CalChildPos();
			return;
		}

		m_LPos = ((_Value - m_Parent->GetWPos())
			/ m_Parent->GetWScale()).RotDegReturn(-m_Parent->GetWRot()); // m_Parent->GetWRot()
		CalWPos();
		CalChildPos();
		CalMatrixCheck[(int)MATTYPE::MATTYPE_POS] = true;
	}

	void SetWPos2d(const CVector& _Value, float _Z = 0.0F)
	{
		CVector Vec = _Value;
		Vec.Z = _Z;

		if (nullptr == m_Parent)	// �θ𰡾��°��==�ֻ���
		{
			m_LPos = m_WPos = Vec;
			CalMatrixCheck[(int)MATTYPE::MATTYPE_POS] = true;
			CalChildPos();
			return;
		}

		m_LPos = ((Vec - m_Parent->GetWPos()) / m_Parent->GetWScale()).RotDegReturn(-m_Parent->GetWRot());
		CalWPos();
		CalChildPos();
		CalMatrixCheck[(int)MATTYPE::MATTYPE_POS] = true;
	}

	void SetLRot(const CVector& _Value)
	{
		if (nullptr == m_Parent)
		{
			m_LRot = m_WRot = _Value;
			CalMatrixCheck[(int)MATTYPE::MATTYPE_ROT] = true;
			CalChildRot();
			CalChildPos();
			return;
		}
		m_LRot = _Value;
		// ȸ���� �ϸ� ��ġ�� �ٲ��
		// ������ ���ϱ� 
		CalWRot();
		CalChildRot();
		CalChildPos();
		CalMatrixCheck[(int)MATTYPE::MATTYPE_ROT] = true;
	}

	void SetWRot(const CVector& _Value)
	{
		if (nullptr == m_Parent)
		{
			m_LRot = m_WRot = _Value;
			CalChildRot();
			CalChildPos();
			CalMatrixCheck[(int)MATTYPE::MATTYPE_ROT] = true;
			return;
		}

		m_LRot = _Value - m_Parent->GetWRot();
		CalWRot();
		CalChildRot();
		CalChildPos();
		CalMatrixCheck[(int)MATTYPE::MATTYPE_ROT] = true;
	}

	void SetLScale(const CVector& _Value)
	{
		if (nullptr == m_Parent)
		{
			m_LScale = m_WScale = _Value;
			CalChildScale();
			CalChildPos();
			CalMatrixCheck[(int)MATTYPE::MATTYPE_SCALE] = true;
			return;
		}

		m_LScale = _Value;
		CalWScale();
		CalChildScale();
		CalChildPos();
		CalMatrixCheck[(int)MATTYPE::MATTYPE_SCALE] = true;
	}

	void SetWScale(const CVector& _Value)
	{
		if (nullptr == m_Parent)
		{
			m_LScale = m_WScale = _Value;
			CalChildScale();
			CalChildPos();
			CalMatrixCheck[(int)MATTYPE::MATTYPE_SCALE] = true;
			return;
		}

		m_LScale = _Value / m_Parent->GetWScale();	// �������� � �Ӽ��� 0�ΰ� ������� �ʴ´�.
		CalWScale();
		CalChildScale();
		CalChildPos();
		CalMatrixCheck[(int)MATTYPE::MATTYPE_SCALE] = true;
	}

public:
	void ScaleXMinus()
	{
		if (0 < m_LScale.X)
		{
			m_LScale.X = m_LScale.X * -1.0f;
		}
	}

	void ScaleXPlus()
	{
		if (0 > m_LScale.X)
		{
			m_LScale.X = m_LScale.X * -1.0f;
		}
	}

public:
	void LMove(const CVector& _Value) { SetLPos(GetLPos() + _Value); }
	void WMove(const CVector& _Value) { SetWPos(GetWPos() + _Value); }

public:
	void LRotAddX(float _Value) { m_LRot.X += _Value;	SetLRot(m_LRot); }
	void LRotAddY(float _Value) { m_LRot.Y += _Value;	SetLRot(m_LRot); }
	void LRotAddZ(float _Value) { m_LRot.Z += _Value;	SetLRot(m_LRot); }
	void WRotAddX(float _Value) { m_WRot.X += _Value;	SetWRot(m_WRot); }
	void WRotAddY(float _Value) { m_WRot.Y += _Value;	SetWRot(m_WRot); }
	void WRotAddZ(float _Value) { m_WRot.Z += _Value;	SetWRot(m_WRot); }

public:
	CVector LForward() { return m_TD.ROT.ArrV[2]; }
	CVector LBack() { return -m_TD.ROT.ArrV[2]; }
	CVector LRight() { return m_TD.ROT.ArrV[0]; }
	CVector LLeft() { return -m_TD.ROT.ArrV[0]; }
	CVector LUp() { return m_TD.ROT.ArrV[1]; }
	CVector LDown() { return -m_TD.ROT.ArrV[1]; } // 	XVec LDOWN() { return m_TRANSDATA.ROT.ArrV[1]; }

	CVector WForward() { return m_TD.WWORLD.ArrV[2].Normal3dVecReturn(); }
	CVector WBack() { return -m_TD.WWORLD.ArrV[2].Normal3dVecReturn(); }
	CVector WRight() { return m_TD.WWORLD.ArrV[0].Normal3dVecReturn(); }
	CVector WLeft() { return -m_TD.WWORLD.ArrV[0].Normal3dVecReturn(); }
	CVector WUp() { return m_TD.WWORLD.ArrV[1].Normal3dVecReturn(); }
	CVector WDown() { return -m_TD.WWORLD.ArrV[1].Normal3dVecReturn(); }

public:
	void SinMove(float _Degree, float _Height = 1)
	{
		CVector CalPos = m_WPos;

		float Rad = _Degree * 180.0f / GameMath::PI;

		CalPos.X = Rad;

		if (CalPos.X >= 0.0f)
		{
			CalPos.Y = sin(Rad) * _Height;
		}
		else
		{
			CalPos.Y = -sin(Rad) * _Height;
		}

		m_WPos = CalPos;

		SetWPos(m_WPos);
	}

	void CosMove(float _Degree, float _Height = 1)
	{
		CVector CalPos = m_WPos;

		float Rad = _Degree * 180.0f / GameMath::PI;

		CalPos.X = Rad;

		if (CalPos.X >= 0.0f)
		{
			CalPos.Y = cos(Rad) * _Height;
		}

		m_WPos = CalPos;

		SetWPos(m_WPos);
	}

	void TanMove(float _Degree, float _Height = 1)
	{
		CVector CalPos = m_WPos;

		float Rad = _Degree * 180.0f / GameMath::PI;

		CalPos.X = Rad;

		if (CalPos.X >= 0.0f)
		{
			CalPos.Y = tan(Rad) * _Height;
		}
		else
		{
			CalPos.Y = -sin(Rad) * _Height;
		}

		m_WPos = CalPos;

		SetWPos(m_WPos);
	}


public:
	bool Col(COLTYPE _ThisType, CPtr<GameTransform> _Trans, COLTYPE _OtherType);

public:
	DirectX::BoundingBox AABB2D();
	DirectX::BoundingSphere SPHERE2D();
	DirectX::BoundingOrientedBox OBB2D();

	DirectX::BoundingBox AABB3D();
	DirectX::BoundingSphere SPHERE3D();
	DirectX::BoundingOrientedBox OBB3D();

	virtual DirectX::SimpleMath::Ray RAY3D();

	float MouseRot(CVector _MousePos);
	float NpcRot(CVector _PlayerPos);

	void LightUpdate(const LightData& _Light);

public:
	void SetSrcSizeOfTexture(const GameString& _Name);

public:
	void Init() override;
	void TransformUpdate();
	void CamUpdate(CPtr<GameCamera> _Cam);
	void ColCheck();
	CVector Convert(CVector Pos, int ScreenWidth, int ScreenHeight);
};

