#include "GameParticle.h"

#include <GameTime.h>
#include "GameActor.h"

void GameParticle::Init()
{
	{
		PData.resize(PaticleCount);

		for (size_t i = 0; i < PaticleCount; i++)
		{
			PData[i].iAlive = 1;
			PData[i].vWorldPos = float4((float)i * 0.5f, 0, 0, 0);
		}

		m_pParticleBuffer = new GameStructuredBuffer();
		// m_pParticleBuffer->Create(sizeof(Particle), 1000, nullptr);
		m_pParticleBuffer->Create(sizeof(Particle), PaticleCount, &PData[0], D3D11_USAGE_DYNAMIC);
	}

	{
		SData.resize(PaticleCount);

		for (size_t i = 0; i < PaticleCount; i++)
		{
			SData[i].vStartScale = float4(GameMath::RandomFloat(0.0f, 1.0f), GameMath::RandomFloat(0.0f, 1.0f), 1.0f);
			SData[i].vEndScale = float4(GameMath::RandomFloat(0.0f, 1.0f), GameMath::RandomFloat(0.0f, 1.0f), 1.0f);
			SData[i].vStartColor = float4(GameMath::RandomFloat(0.0f, 1.0f), GameMath::RandomFloat(0.0f, 1.0f), GameMath::RandomFloat(0.0f, 1.0f));
			SData[i].vEndColor = float4(GameMath::RandomFloat(0.0f, 1.0f), GameMath::RandomFloat(0.0f, 1.0f), GameMath::RandomFloat(0.0f, 1.0f));
			SData[i].iCurCount = 1;
			SData[i].iSpawnCount = 3;
			SData[i].Temp0 = 1;
			SData[i].Temp1 = 1;
		}

		m_pSharedBuffer = new GameStructuredBuffer();
		// m_pSharedBuffer->Create(sizeof(ParticleShared), 1, nullptr);
		m_pSharedBuffer->Create(sizeof(ParticleShared), PaticleCount, &SData[0]);
	}

	//////////////////
	{
		m_Mesh = new GameMath();
		m_Mesh->DrawType(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);


		std::vector<POINTVTX> m_VTX;
		m_VTX.resize(1);
		m_VTX[0].Pos = float4::ZERO;
		m_VTX[0].UV = float4::ZERO;
		m_VTX[0].Color = float4::BLACK;

		CPtr<GameVtxBuffer> VB = new GameVtxBuffer();
		VB->Create(m_VTX.size(), sizeof(POINTVTX), &m_VTX[0]);


		std::vector<UINT> m_IDX;
		CPtr<GameIdxBuffer> IB = new GameIdxBuffer();
		m_IDX.resize(1);
		m_IDX[0] = 0;
		IB->Create(m_IDX.size(), sizeof(UINT), &m_IDX[0], DXGI_FORMAT::DXGI_FORMAT_R32_UINT);

		m_Mesh->SetVtxBuffer(VB);
		m_Mesh->SetIdxBuffer(IB);
	}

	m_Render = GetActor()->CreateCom<GameRenderer>();
	m_RenderPlayer = m_Render->CreateRenderPlayer(m_Mesh, "Particle");

	m_RenderPlayer->SetTexture(L"Tex", L"T_fire_trail_bluredori.tga");

	m_Mesh->InstancedRenderCount(PaticleCount);

	m_RenderPlayer->m_IsDebug = true;
	m_RenderPlayer->SetStructuredBuffer("arrParticle", m_pParticleBuffer);
	m_RenderPlayer->SetStructuredBuffer("ParticleShared", m_pSharedBuffer);
}

void GameParticle::Update()
{
	{
		for (size_t i = 0; i < PaticleCount; i++)
		{
			PData[i].vWorldPos += float4(-1.0f, 0, 0, 0) * GameTime::DeltaTime();
			PData[i].fCurLifeTime = GameTime::DeltaTime();
		}

		m_pParticleBuffer->SetData(&PData[0], sizeof(Particle) * PaticleCount);
	}
}

void GameParticle::UpdateNext()
{
}
