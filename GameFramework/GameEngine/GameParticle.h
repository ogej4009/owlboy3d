#pragma once
#include "GameComponent.h"
#include "GameMesh.h"
#include "GameRenderer.h"
#include "GameStructuredBuffer.h"

#define PaticleCount 100

class Particle
{
public:
	float4	vWorldPos;
	float4	vDir;
	float   fSpeed;
	float   fAddSpeed;
	float	fMaxLifeTime;
	float	fCurLifeTime;
	float4	vPad;
	int		iAlive;
	int		Temp0;
	int		Temp1;
	int		Temp2;
};

class ParticleShared
{
public:

	float4	vStartScale;
	float4	vEndScale;
	float4	vStartColor;
	float4	vEndColor;
	UINT	iSpawnCount;
	UINT	iCurCount;
	UINT	Temp0;
	UINT	Temp1;
};

class POINTVTX
{
public:
	float4	Pos;
	float4	Color;
	float4	UV;
};

class GameParticle : public ActorComponent
{
private:
	std::vector<Particle> PData;
	std::vector<ParticleShared> SData;

	CPtr<GameStructuredBuffer> m_pParticleBuffer;
	CPtr<GameStructuredBuffer> m_pSharedBuffer;
	
	CPtr<GameMesh> m_Mesh;
	CPtr<GameRenderer> m_Render;
	CPtr<GameRenderPlayer> m_RenderPlayer;

public:
	void Init() override;
	void Update() override;
	void UpdateNext() override;
};

