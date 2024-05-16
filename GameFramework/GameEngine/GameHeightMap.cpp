#include "GameHeightMap.h"
#include "GameActor.h"
#include "Vtx.h"


void GameHeightMap::Init(int& _X, int& _Z, const GameString _MapHeightTex, int _Order)
{

	Min = 0.0f;
	X = _X;
	Z = _Z;

	MapOption.XCount = (float)X;
	MapOption.ZCount = (float)Z;
	MapOption.YRatio = (float)1.0f;
	MapOption.YRatio = (float)10.0f;
	MapOption.YScale = GetTrans()->GetWScale().Y;

	m_Render = GetActor()->CreateCom<GameRenderer>(_Order);

	m_Mesh = new GameMesh();

	m_HTex = GameTexture::Find(_MapHeightTex);

	MapOption.PixelUv = CVector(1.0f / m_HTex->Size().X, 1.0f / m_HTex->Size().Y);
	MapOption.PixelScale = CVector(
		GetTrans()->GetWScale().X / m_HTex->Size().X
		, GetTrans()->GetWScale().Z / m_HTex->Size().Y
	);
	CPtr<GameVtxBuffer> VB = new GameVtxBuffer();
	CPtr<GameIdxBuffer> IB = new GameIdxBuffer();

	m_VecVtx.resize((X + 1) * (Z + 1));

	float StartX = -0.5f;
	float StartZ = 0.5f;

	for (int z = 0; z < Z + 1; z++)
	{
		for (int x = 0; x < X + 1; x++)
		{
			float PosZ = StartZ - (z * ((float)1 / Z));
			float PosX = StartX + (x * ((float)1 / X));

			int Index = z * (X + 1) + x;

			m_VecVtx[Index].Pos.X = PosX;
			m_VecVtx[Index].Pos.Y = 0.0f;
			m_VecVtx[Index].Pos.Z = PosZ;

			m_VecVtx[Index].Uv.X = (float)x;
			m_VecVtx[Index].Uv.Y = (float)z;
			m_VecVtx[Index].Normal = CVector::UP;
		}
	}

	VB->Create(m_VecVtx.size(), sizeof(Vtx3D), &m_VecVtx[0]);



	std::vector<UINT> m_MapIdx;


	for (int z = 0; z < Z; z++)
	{
		for (int x = 0; x < X; x++)
		{
			int Pivot = z * (X + 1) + x;
			m_MapIdx.push_back(Pivot);
			m_MapIdx.push_back(Pivot + 1);
			m_MapIdx.push_back(Pivot + (X + 1) + 1);

			m_MapIdx.push_back(Pivot);
			m_MapIdx.push_back(Pivot + (X + 1) + 1);
			m_MapIdx.push_back(Pivot + (X + 1));
		}
	}

	IB->Create(m_MapIdx.size(), sizeof(UINT), &m_MapIdx[0], DXGI_FORMAT::DXGI_FORMAT_R32_UINT);
	m_Mesh->SetVB(VB);
	m_Mesh->SetIB(IB);

	m_Render->CreateRenderPlayer(m_Mesh, L"HeightMap");
	WTex(_MapHeightTex);
	m_Render->SetCBuffer(L"MapOption", &MapOption, CBUFMODE::CB_LINK);
}

void GameHeightMap::BaseTexture(const GameString _TextureName)
{
	m_Render->SetTexture(L"BaseTex", _TextureName);
}

CVector GameHeightMap::CalTexelPos(const CVector& _Pos)
{
	CVector Size = m_HTex->Size();
	CVector Vec;

	Vec.X = _Pos.X + 0.5f;
	Vec.Y = (_Pos.Z * -1.0f) + 0.5f;

	Vec.X *= Size.X;
	Vec.Y *= Size.Y;
	return Vec;
}

void GameHeightMap::WTex(const GameString _TextureName)
{
	m_Render->SetTexture(L"WTex", _TextureName);

	m_YTileMap.clear();

	int HX = (X / 2);
	int HZ = (Z / 2);

	float InterX = (1.0f / (float)X);
	float InterZ = (1.0f / (float)Z);
	float HInterX = InterX * 0.5F;
	float HInterZ = InterZ * 0.5F;

	for (int z = -HZ; z < (HZ + 1); z++)
	{
		for (int x = -HX; x < (HX + 1); x++)
		{
			int2 Index;
			Index.x = x;
			Index.y = z;

			if (Index.x == 0 && Index.y == -10)
			{
				int a = 0;
			}

			float CenterX = (x * InterX);
			float CenterZ = (z * InterZ);

			m_YTileMap[Index.Key].Up.Arr[0] = { CenterX + -HInterX, 0.0f, CenterZ + HInterZ };
			m_YTileMap[Index.Key].Up.Arr[1] = { CenterX + HInterX, 0.0f, CenterZ + HInterZ };
			m_YTileMap[Index.Key].Up.Arr[2] = { CenterX + HInterX, 0.0f, CenterZ + -HInterZ };


			m_YTileMap[Index.Key].Down.Arr[0] = m_YTileMap[Index.Key].Up.Arr[0];
			m_YTileMap[Index.Key].Down.Arr[1] = m_YTileMap[Index.Key].Up.Arr[2];
			m_YTileMap[Index.Key].Down.Arr[2] = { CenterX + -HInterX, 0.0f, CenterZ + -HInterZ };

			CVector Pos;
			Pos = CalTexelPos(m_YTileMap[Index.Key].Up.Arr[0]);
			m_YTileMap[Index.Key].Up.Arr[0].Y = m_HTex->GetPixel({ (int)Pos.X, (int)Pos.Y }).x * GetTrans()->GetWScale().Y;
			Pos = CalTexelPos(m_YTileMap[Index.Key].Up.Arr[1]);
			m_YTileMap[Index.Key].Up.Arr[1].Y = m_HTex->GetPixel({ (int)Pos.X, (int)Pos.Y }).x * GetTrans()->GetWScale().Y;
			Pos = CalTexelPos(m_YTileMap[Index.Key].Up.Arr[2]);
			m_YTileMap[Index.Key].Up.Arr[2].Y = m_HTex->GetPixel({ (int)Pos.X, (int)Pos.Y }).x * GetTrans()->GetWScale().Y;

			Pos = CalTexelPos(m_YTileMap[Index.Key].Down.Arr[0]);
			m_YTileMap[Index.Key].Down.Arr[0].Y = m_HTex->GetPixel({ (int)Pos.X, (int)Pos.Y }).x * GetTrans()->GetWScale().Y;
			Pos = CalTexelPos(m_YTileMap[Index.Key].Down.Arr[1]);
			m_YTileMap[Index.Key].Down.Arr[1].Y = m_HTex->GetPixel({ (int)Pos.X, (int)Pos.Y }).x * GetTrans()->GetWScale().Y;
			Pos = CalTexelPos(m_YTileMap[Index.Key].Down.Arr[2]);
			m_YTileMap[Index.Key].Down.Arr[2].Y = m_HTex->GetPixel({ (int)Pos.X, (int)Pos.Y }).x * GetTrans()->GetWScale().Y;

			for (size_t i = 0; i < 3; i++)
			{
				if (Min > m_YTileMap[Index.Key].Up.Arr[i].Y)
				{
					Min = m_YTileMap[Index.Key].Up.Arr[i].Y;
				}
			}

			for (size_t i = 0; i < 3; i++)
			{
				if (Min > m_YTileMap[Index.Key].Down.Arr[i].Y)
				{
					Min = m_YTileMap[Index.Key].Down.Arr[i].Y;
				}
			}
		}
	}


}

int2 GameHeightMap::Index(float4 _Pos)
{
	float4 Scale = GetTrans()->GetWScale();

	float XSize = Scale.X / (float)X;
	float ZSize = Scale.Z / (float)Z;

	int2 ReturnIndex;

	float IndexX = _Pos.X / XSize;
	float IndexZ = _Pos.Z / ZSize;

	IndexX = roundf(IndexX);
	IndexZ = roundf(IndexZ);

	ReturnIndex.x = (int)IndexX;
	ReturnIndex.y = (int)IndexZ;

	return ReturnIndex;
}

CVector GameHeightMap::CalPosToWorld(const CVector& _Pos)
{
	CVector ReturnX;
	CVector Scale;
	Scale = GetTrans()->GetWScale();

	ReturnX.X = _Pos.X * Scale.X;
	ReturnX.Z = _Pos.Z * Scale.Z;
	ReturnX.Y = _Pos.Y;

	return ReturnX;
}

float GameHeightMap::YHeight(float4 _Pos)
{
	float4 Scale = GetTrans()->GetWScale();

	Scale = Scale.HalfVec();

	if (
		_Pos.Z > Scale.Z ||
		_Pos.Z < -Scale.Z ||
		_Pos.X > Scale.X ||
		_Pos.X < -Scale.X
		)
	{
		return Min;
	}

	CVector Ori = _Pos;
	Ori.Y = 0.0f;
	CVector Dir = CVector::UP;


	int2 Key = Index(_Pos);
	float YDis = Min;

	CVector UpTri0 = CalPosToWorld(m_YTileMap[Key.Key].Up.Arr[0]);
	CVector UpTri1 = CalPosToWorld(m_YTileMap[Key.Key].Up.Arr[1]);
	CVector UpTri2 = CalPosToWorld(m_YTileMap[Key.Key].Up.Arr[2]);
	DirectX::TriangleTests::Intersects(Ori, Dir, UpTri0, UpTri1, UpTri2, YDis);
	if (YDis != Min)
	{
		return YDis;
	}

	CVector DownTri0 = CalPosToWorld(m_YTileMap[Key.Key].Down.Arr[0]);
	CVector DownTri1 = CalPosToWorld(m_YTileMap[Key.Key].Down.Arr[1]);
	CVector DownTri2 = CalPosToWorld(m_YTileMap[Key.Key].Down.Arr[2]);
	DirectX::TriangleTests::Intersects(Ori, Dir, DownTri0, DownTri1, DownTri2, YDis);
	if (YDis != Min)
	{
		return YDis;
	}

	return Min;

}

float GameHeightMap::GetMin()
{
	return Min;
}