#pragma once
#include "GameComponent.h"
#include <GameDebug.h>
#include <set>
#include "GameRenderingData.h"

// 라이트를 삭제하지 않는다는 가정하에 이렇게 만든 구조이다.
// HLight가 생긴곳에 방향을 알수있는 오브젝트도 만들어주세요.
class GameLight : public ActorComponent
{
	friend class XTransform;

private:
	std::list<LightData*> DataList;

	// 나는 1 3 4 5 
	std::set<int> m_ViewRenderers;

	CVector AmbColor;
	CVector LightPower;
	CVector SpecPow;
	CVector LightDir;
	CVector LightDirInv;
	CVector DifColor;

public:

	void SetDifColor(CVector _DifColor)
	{
		DifColor = _DifColor;
	}

	CVector GetAmbColor()
	{
		return AmbColor;
	}

	void SetAmbColor(CVector _AmbColor)
	{
		AmbColor = _AmbColor;
	}

	CVector GetSpecPow()
	{
		return SpecPow;
	}

	CVector GetLightPower()
	{
		return LightPower;
	}

	void SetLightPower(CVector _Color)
	{
		LightPower.X = _Color.X;
		LightPower.Y = _Color.Y;
		LightPower.Z = _Color.Z;
		LightPower.W = _Color.W;
	}


	CVector GetLightDir()
	{
		return LightDir;
	}

	CVector GetLightDirInv()
	{
		return LightDirInv;
	}


public:
	friend GameScene;

public:

	template<typename ... REST>
	void Init(int _Order, REST ... _Arg)
	{
		AddRenderGroup(_Arg...);
		InitSetting(_Order);
	}

	void Init(int _Order, int _Index = 0)
	{
		AddRenderGroup(_Index);
		InitSetting(_Order);
	}

	template<typename ... REST>
	void AddRenderGroup(int _GroupIndex, REST ... _Arg)
	{
		if (m_ViewRenderers.end() != m_ViewRenderers.find(_GroupIndex))
		{
			ASSERTMSG(L"카메라가 같은 그룹을 두번 보려고 했습니다.");
		}

		m_ViewRenderers.insert(_GroupIndex);
		AddRenderGroup(_Arg...);
	}

	void AddRenderGroup(int _GroupIndex)
	{
		if (m_ViewRenderers.end() != m_ViewRenderers.find(_GroupIndex))
		{
			MSG_ASSERT_CODE(L"카메라가 같은 그룹을 두번 보려고 했습니다.");
		}

		m_ViewRenderers.insert(_GroupIndex);
	}
	void AddRenderGroup() {}

public:
	void InitSetting(int _Order);
	void LightUpdate();
	void madeRect();

private:
	float m_Near;
	float m_Far;
	CVector ViewSize;
	float Qulity;
	CMatrix m_VIEW;
	CMatrix m_PROJ;

	CPtr<GameRenderTarget> ShadowDepthTarget;

public:
	CPtr<GameRenderTarget> ShadowTarget()
	{
		return ShadowDepthTarget;
	}

};

