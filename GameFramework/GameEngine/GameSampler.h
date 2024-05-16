#pragma once
#include "GameShader.h"
#include <GameObjTFuncMgr.h>

class GameSampler : public GameObjTFuncMgr<GameSampler>
{
public:
	static void Create(const GameString& _Name, const D3D11_SAMPLER_DESC& Desc)
	{
		CreateAndInsert(_Name, Desc);
	}

private:
	D3D11_SAMPLER_DESC m_Desc;
	ID3D11SamplerState* m_State;

public:
	void Create();
	void Setting(SHADERTYPE _Type, unsigned int _Reg);

public:
	GameSampler(const D3D11_SAMPLER_DESC& _Desc);
	~GameSampler();
};