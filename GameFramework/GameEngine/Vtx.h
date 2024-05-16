#pragma once
#include <GameMath.h>

class Vtx2D
{
public:
	CVector Pos;
	CVector Uv;
	CVector Color;

	//Vtx2D& operator=(const CVector& _Value)
	//{
	//	Pos.X = _Value.X;
	//	Pos.Y = _Value.Y;
	//	Pos.Z = _Value.Z;
	//	return *this;
	//}
};

class TargetVtx
{
public:
	CVector Pos;
	CVector Uv;
};

class Vtx3D
{
public:
	CVector Pos;
	CVector Uv;
	CVector Color;
	CVector Normal;
	CVector BiNormal;
	CVector Tangent;
	CVector Weight;
	int		Index[4];
};