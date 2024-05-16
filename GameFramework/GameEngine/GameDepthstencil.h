#pragma once
#include "GameDevice.h"
#include <GameObjTFuncMgr.h>

class GameDepthstencil : public GameObjTFuncMgr<GameDepthstencil>
{
public:
	static void Create(const GameString& _Name, const D3D11_DEPTH_STENCIL_DESC& Desc)
	{
		CreateAndInsert(_Name, Desc);
	}

private:
	D3D11_DEPTH_STENCIL_DESC m_Desc;
	ID3D11DepthStencilState* m_State;

public:
	void Create();
	void Setting();

public:
	GameDepthstencil(const D3D11_DEPTH_STENCIL_DESC& _Desc);
	~GameDepthstencil();
};