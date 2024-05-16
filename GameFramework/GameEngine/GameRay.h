#pragma once
#include "GameComponent.h"

struct RayData;
class GameRenderer;
class GameCol;
class GameCamera;
class GameTransform;

class GameRay : public ActorComponent
{
	CPtr<GameCol> m_Col;
	CPtr<GameRenderer> m_Render;
	CPtr<GameTransform> m_Trans;
	bool m_bSwitch;
	bool m_bShoot;
	bool m_bDebugSwitch;
	CVector m_Vec;

public:
	void ShootRay(RayData _ray);
	void TestCol(GameCol* This, GameCol* _ther);
	void RayInit();
	void RenderOnOff();
	void TestRay(RayData _ray);
	RayData MakeRay(CVector _WinPos);

public:
	void Init(CPtr<GameTransform> Cam);
	void Update()override;

};

