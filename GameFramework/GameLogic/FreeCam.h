#pragma once
#include <GameComponent.h>
#include <set>

#pragma comment(lib, "GameBase.lib")
#pragma comment(lib, "GameEngine.lib")

class GameCamera;
class FreeCam : public ActorComponent
{
private:
	CPtr<GameCamera> m_Cam;
	float m_Speed;
	float m_RotSpeed;
	CVector m_StartPos;
	CVector m_StartRot;
	float m_StartFov;
	CVector m_FixedPos;
	CVector m_FixedRot;
	float m_FixedFov;

public:
	void CamInitialization();
	void CamAcceleration();
	void CamSpeedInit();
	void CamZoomIn();
	void CamZoomOut();

public:
	void Init() override;
	void Init(float _Speed);
	void Update() override;

public:
	FreeCam();
	FreeCam(float _Speed);
	~FreeCam();
};
