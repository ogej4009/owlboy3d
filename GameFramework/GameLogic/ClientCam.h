#pragma once
#include "GameUnity.h"
class ClientCam : public ActorComponent
{
	CPtr<GameCamera> m_Cam;
	float m_Speed;

public:
	static CPtr<GameActor> CamActor;

public:
	void Move(const CVector& _Dir, float _Speed);
	void Join(CPtr<GameTransform> _Parent);
	void Withdraw();

public:
	void Init() override;
	void Update() override;

public:
	ClientCam();
	~ClientCam();
};