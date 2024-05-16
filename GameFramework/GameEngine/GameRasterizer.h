#pragma once
#include "GameDevice.h"
#include <GameObjTFuncMgr.h>

class GameRasterizer : public GameObjTFuncMgr<GameRasterizer>
{
public:
	static void Create(const GameString& _Name, const D3D11_RASTERIZER_DESC& Desc)
	{
		CreateAndInsert(_Name, Desc);
	}

private:
	D3D11_RASTERIZER_DESC	m_Desc;
	ID3D11RasterizerState*  m_State;

public:
	void Create();
	void Setting();

public:
	GameRasterizer(const D3D11_RASTERIZER_DESC& _Desc);
	~GameRasterizer();
};