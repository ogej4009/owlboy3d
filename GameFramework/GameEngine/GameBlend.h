#pragma once
#include "GameDevice.h"
#include <GameObjTFuncMgr.h>

class GameBlend : public GameObjTFuncMgr<GameBlend>
{
public:
	static void Create(const GameString& _Name, const D3D11_BLEND_DESC& Desc)
	{
		CreateAndInsert(_Name, Desc);
	}

private:
	D3D11_BLEND_DESC	m_Desc;
	ID3D11BlendState*	m_State;

public:
	void Create();
	void Setting();

public:
	GameBlend(const D3D11_BLEND_DESC& _Desc);
	~GameBlend();
};