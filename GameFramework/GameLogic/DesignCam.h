#pragma once
#include "GameUnity.h"

#pragma comment(lib, "GameBase.lib")
#pragma comment(lib, "GameEngine.lib")

class DesignCam : public ActorComponent
{
	CPtr<GameCamera> m_Cam;
	float m_Speed;
	float m_RotSpeed;
	float m_AccSpeed;
	bool m_bCheck;

public:
	static CPtr<GameActor> CamActor;

public:
	CVector GetCamSize()
	{
		return m_Cam->GetCamSize();
	}

public:
	void Move(const CVector& _Dir, float _Speed);
	void Join(CPtr<GameTransform> _Parent);
	void Withdraw();

	CVector ScreenPos3DToWorldPos(const CVector& _ScreenPos);

public:
	void Init() override;
	void Update() override;

public:
	DesignCam();
	~DesignCam();
};

#define D_CAM_SPEED 1.0f	
#define D_CAM_ROT_SPEED 2.f
#define D_CAM_ACCEL_SPEED 100.f