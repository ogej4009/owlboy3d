#pragma once
#include <GameMath.h>
#include <vector>
#include "GameRenderer.h"

struct YTri
{
	CVector Arr[3];
};

struct YTile
{
	YTri Up;
	YTri Down;
};

struct MAPOPTION
{
	float XCount;
	float ZCount;
	float YRatio;
	float YScale;
	CVector PixelUv;
	CVector PixelScale;
};

class GameHeightMap : public ActorComponent
{
private:
	int X;
	int Z;

	MAPOPTION MapOption;

	// std::vector<NaviTri> m_NTri;
	CPtr<GameMesh> m_Mesh;
	CPtr<GameRenderer> m_Render;
	CPtr<GameRenderPlayer> m_RenderPlayer;
	std::vector<Vtx3D> m_VecVtx;
	std::map<__int64, YTile> m_YTileMap;
	CPtr<GameTexture> m_HTex;

	float Min;

public:
	CPtr<GameRenderer> Render()
	{
		return m_Render;
	}

public:
	float GetMin();
	int2 Index(float4 _Pos);
	float YHeight(float4 _Pos);
	CVector CalTexelPos(const CVector& _Pos);
	CVector CalPosToWorld(const CVector& _Pos);

public:
	void Init(int& _X, int& _Z, const GameString _MapHeightTex, int _Order = 0);
	void BaseTexture(const GameString _TextureName);
	void WTex(const GameString _TextureName);;
};

