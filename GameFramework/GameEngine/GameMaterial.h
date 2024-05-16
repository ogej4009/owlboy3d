#pragma once
#include <GameObjTFuncMgr.h>
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "GameGeometryShader.h"
#include "GameRasterizer.h"
#include "GameDepthstencil.h"
#include "GameBlend.h"

class GameRenderPlayer;
class GameMaterial : public GameObjTFuncMgr<GameMaterial>
{
public:
	friend GameRenderPlayer;

public:
	static CPtr<GameMaterial> Create(const GameString& _Name)
	{
		return CreateAndInsert(_Name);
	}

private:
	bool m_IsClone;

	bool m_AllCheck;
	CPtr<GameVtxShader>			m_VtxShader;
	CPtr<GamePixShader>			m_PixShader;
	CPtr<GameGeometryShader>	m_GeoShader;
	std::vector<GameShader*>	m_AllShader;

	CPtr<GameRasterizer>	m_Rasterizer;
	CPtr<GameDepthstencil>	m_DepthStencil;
	CPtr<GameBlend>			m_Blend;

public:
	CPtr<GameVtxShader>			GetVtxShader() { return m_VtxShader; }
	CPtr<GamePixShader>			GetPixShader() { return m_PixShader; }
	CPtr<GameGeometryShader>	GetGeoShader() { return m_GeoShader; }
	CPtr<GameRasterizer>		GetRasterizer() { return m_Rasterizer; }
	CPtr<GameDepthstencil>		GetDepthStencil() { return m_DepthStencil; }
	CPtr<GameBlend>				GetBlend() { return m_Blend; }

	void SetVtxShader(const GameString& _Name);
	void SetPixShader(const GameString& _Name);
	void SetGeoShader(const GameString& _Name);
	void SetRasterizer(const GameString& _Name);
	void SetDepthStencil(const GameString& _Name);
	void SetBlend(const GameString& _Name);

	MATERIAL_TYPE MType();

public:
	bool IsClone()
	{
		return m_IsClone;
	}

	CPtr<GameMaterial> MaterialClone();

public:
	void Setting();

public:
	GameMaterial();
	~GameMaterial();

};

