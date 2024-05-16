#include "GameDevice.h"
#include "GameVtxBuffer.h"
#include "GameIdxBuffer.h"
#include "Vtx.h"
#include "GameMesh.h"


#pragma region 버퍼 
/*
	버퍼는 디바이스를 통해 만들었으므로 그래픽 카드에 저장됨
	LOAD는 -> CPU(RAM), GPU(RAM)에 영향을 줌
*/
#pragma endregion

void GameDevice::MeshInit()
{
#pragma region 리소스 
	/*
		리소스 중에 LOAD해야 하는 것은?
		로드를 하는 요소들은 경로를 내뱉어야 한다.
		따라서 경로 때문에 로드가 있는 케이스와 없는 케이스로 나눈다.
		서로 다른 방식을 처리한다.

	*/
#pragma endregion

#pragma region 점
	/*
		점의 집합은 로드를 하지 않는다.
		점이 특정한 파일로 빠져있는 경우가 있는가? 없다.
		점은 가변적인 점의 집합
		여러개 -> 자료구조로 관리
		점--> vector
		그 집합을 갯수만큼 하나하나를 그래픽카드에 전달한다.
		그것을 1대1로 매칭 시켜주는 것이 버텍스 쉐이더
		점의 정보 매쉬는 복합적이다.
		버텍스 버퍼는 오직 점에 관련된 것이다.

		기본 매쉬를 만들때는 크기를 1로 만들어 놓는 경우가 대부분이다.

		인덱스 버퍼
		시계방향으로 그린다는게 중요하다.
		뒷면은 안그리게 하는게 이 그려지는 방향에 의해서 결정된다.

	*/
	/*
								상수 -> 코드 영역
		m_Mesh[3].Pos = { -0.5f, -0.5f, 0.0f, 1.0f }; -> 이것은 스택영역
		전역 -> 데이터 영역
	*/
#pragma endregion



	{
		std::vector<Vtx2D> m_Mesh;
		m_Mesh.resize(4);
		m_Mesh[0].Pos = { -0.5f, 0.5f, 0.0f, 1.0f }; // W = 1.0f 나중에 행렬곱에서 이동 적용 (0이면 이동 안함)
		m_Mesh[1].Pos = { 0.5f, 0.5f, 0.0f, 1.0f };
		m_Mesh[2].Pos = { 0.5f, -0.5f, 0.0f, 1.0f };
		m_Mesh[3].Pos = { -0.5f, -0.5f, 0.0f, 1.0f };

		m_Mesh[0].Uv = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_Mesh[1].Uv = { 1.0f, 0.0f, 0.0f, 1.0f };
		m_Mesh[2].Uv = { 1.0f, 1.0f, 0.0f, 1.0f };
		m_Mesh[3].Uv = { 0.0f, 1.0f, 0.0f, 1.0f };

		m_Mesh[0].Color = m_Mesh[1].Color = m_Mesh[2].Color = m_Mesh[3].Color = CVector::WHITE;
		GameVtxBuffer::Create<Vtx2D>(L"FrameRect", m_Mesh);

		std::vector<UINT> m_IDX = { 0, 1, 2, 0, 2, 3 };
		GameIdxBuffer::Create<UINT>(L"FrameRect", m_IDX); // RECT2DCOLOR

		GameMesh::Create(L"FrameRect");
	}

	//////////////////////// 추가했습니다. 피라미드 
	// Square Pyramid
	{
		std::vector<Vtx3D> m_Color;
		m_Color.resize(5);
		m_Color[0].Pos = { -0.5f, 0.5f, -0.5f, 1.0f };
		m_Color[1].Pos = { 0.5f, 0.5f, -0.5f, 1.0f };
		m_Color[2].Pos = { 0.5f, -0.5f, -0.5f, 1.0f };
		m_Color[3].Pos = { -0.5f, -0.5f, -0.5f, 1.0f };
		m_Color[4].Pos = { 0.0f, 0.0f, 1.0f, 1.0f };
		m_Color[0].Normal = m_Color[0].Pos.Normal3dVecReturn();
		m_Color[1].Normal = m_Color[1].Pos.Normal3dVecReturn();
		m_Color[2].Normal = m_Color[2].Pos.Normal3dVecReturn();
		m_Color[3].Normal = m_Color[3].Pos.Normal3dVecReturn();
		m_Color[4].Normal = m_Color[4].Pos.Normal3dVecReturn();
		m_Color[0].Color = m_Color[1].Color = m_Color[2].Color = m_Color[3].Color =  CVector::WHITE;
		m_Color[4].Color = CVector::RED;
		GameVtxBuffer::Create<Vtx3D>(L"SquarePyramid", m_Color);
		std::vector<UINT> m_IDX = { 0, 1, 2, 0, 2, 3,  4, 1, 0 , 4, 2, 1, 4, 3, 2, 4, 0 , 3 };
		GameIdxBuffer::Create<UINT>(L"SquarePyramid", m_IDX);
		GameMesh::Create(L"SquarePyramid");
	}


	{
		std::vector<Vtx2D> m_Mesh;
		m_Mesh.resize(4);
		m_Mesh[0].Pos = { -0.5f, 0.5f, 0.0f, 1.0f }; // W = 1.0f 나중에 행렬곱에서 이동 적용 (0이면 이동 안함)
		m_Mesh[1].Pos = { 0.5f, 0.5f, 0.0f, 1.0f };
		m_Mesh[2].Pos = { 0.5f, -0.5f, 0.0f, 1.0f };
		m_Mesh[3].Pos = { -0.5f, -0.5f, 0.0f, 1.0f };

		m_Mesh[0].Color = m_Mesh[1].Color = m_Mesh[2].Color = m_Mesh[3].Color = CVector::WHITE;
		GameVtxBuffer::Create<Vtx2D>(L"Grid", m_Mesh);

		std::vector<UINT> m_IDX = { 0, 1, 2, 0, 2, 3 };
		GameIdxBuffer::Create<UINT>(L"Grid", m_IDX);

		GameMesh::Create(L"Grid"); // RECT_2D_TILE
	}

	/////////////////////////////////// 추가했습니다. 
	// Circle
	{
		std::vector<Vtx2D> m_Color;
		std::vector<UINT> m_IDX;
		m_Color.resize(1);
		Vtx2D center;
		center.Pos.X = 0.0f;
		center.Pos.Y = 0.0f;
		center.Pos.Z = 0.0f;
		unsigned int i = 0;
		for (double phi = 0.; phi < 2 * GameMath::PI - GameMath::PI / 50.; phi += GameMath::PI / 50.) // Azimuth [0, 2PI]
		{
			for (double theta = 0.; theta < GameMath::PI - GameMath::PI / 50.; theta += GameMath::PI / 50.) // Elevation [0, PI]
			{
				Vtx2D point;
				point.Pos.X = float(cos(phi) * sin(theta) + center.Pos.X);
				point.Pos.Y = float(sin(phi) * sin(theta) + center.Pos.Y);
				point.Pos.Z = float(cos(theta) + center.Pos.Z);
				//spherePoints.push_back(point);
				m_Color[i].Color = CVector::WHITE;
				m_Color.push_back(point);
				m_IDX.push_back(0);
				m_IDX.push_back(i + 1);
				m_IDX.push_back(i + 2);
				i++;
			}
		}
		GameVtxBuffer::Create<Vtx2D>(L"Circle", m_Color);
		GameIdxBuffer::Create<UINT>(L"Circle", m_IDX);
		GameMesh::Create(L"Circle");
	}

	// Cube
	{
		std::vector<Vtx2D> m_Vtx;
		
		m_Vtx.resize(24);
		
		m_Vtx[0].Pos = { -0.5f, 0.5f, -0.5f, 1.0f };
		m_Vtx[1].Pos = { 0.5f, 0.5f, -0.5f, 1.0f };
		m_Vtx[2].Pos = { 0.5f, 0.5f,  0.5f, 1.0f };
		m_Vtx[3].Pos = { -0.5f, 0.5f,  0.5f, 1.0f };
		m_Vtx[4].Pos = { -0.5f, -0.5f,  0.5f, 1.0f };
		m_Vtx[5].Pos = { 0.5f, -0.5f,  0.5f, 1.0f };
		m_Vtx[6].Pos = { 0.5f, -0.5f, -0.5f, 1.0f };
		m_Vtx[7].Pos = { -0.5f, -0.5f, -0.5f, 1.0f };

		m_Vtx[0].Uv = { 0.0f, 1.0f, 0.0f, 1.0f };
		m_Vtx[1].Uv = { 1.0f, 1.0f, 0.0f, 1.0f };
		m_Vtx[2].Uv = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_Vtx[3].Uv = { 0.0f, 1.0f, 1.0f, 1.0f };
		m_Vtx[4].Uv = { 0.0f, 0.0f, 1.0f, 1.0f };
		m_Vtx[5].Uv = { 1.0f, 0.0f, 1.0f, 1.0f };
		m_Vtx[6].Uv = { 1.0f, 0.0f, 0.0f, 1.0f };
		m_Vtx[7].Uv = { 0.0f, 0.0f, 0.0f, 1.0f };

		for (size_t i = 0; i < 8; i++)
		{
			m_Vtx[i].Color = CVector::WHITE;
		}

		for (size_t i = 0; i < 4; i++)
		{
			m_Vtx[i].Color = CVector::BLACK;
		}

		GameVtxBuffer::Create<Vtx2D>(L"Cube", m_Vtx);

		std::vector<UINT> m_IDX =
		{
			2, 1, 0,
			3, 2, 0,
			6, 5, 4,
			7, 6, 4,
			5, 2, 3,
			4, 5, 3,
			6, 1, 2,
			5, 6, 2,
			6, 7, 1,
			7, 0, 1,
			4, 3, 0,
			7, 4, 0
		};
		GameIdxBuffer::Create<UINT>(L"Cube", m_IDX);
		GameMesh::Create(L"Cube");
	}

	{
		std::vector<TargetVtx> m_TargetVtx;
		m_TargetVtx.resize(4);
		m_TargetVtx[0].Pos = { -1.0f, 1.0f, 0.0f, 1.0f };
		m_TargetVtx[1].Pos = { 1.0f, 1.0f, 0.0f, 1.0f };
		m_TargetVtx[2].Pos = { 1.0f, -1.0f, 0.0f, 1.0f };
		m_TargetVtx[3].Pos = { -1.0f, -1.0f, 0.0f, 1.0f };
		m_TargetVtx[0].Uv = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_TargetVtx[1].Uv = { 1.0f, 0.0f, 0.0f, 1.0f };
		m_TargetVtx[2].Uv = { 1.0f, 1.0f, 0.0f, 1.0f };
		m_TargetVtx[3].Uv = { 0.0f, 1.0f, 0.0f, 1.0f };
		GameVtxBuffer::Create<TargetVtx>(L"TargetFrameRect", m_TargetVtx);
		std::vector<UINT> m_Idx = { 0, 1, 2, 0, 2, 3 };
		GameIdxBuffer::Create<UINT>(L"TargetFrameRect", m_Idx);
		GameMesh::Create(L"TargetFrameRect");
	}


	{
		std::vector<TargetVtx> m_TVtx;
		m_TVtx.resize(4);
		m_TVtx[0].Pos = { -0.5f, 0.5f, 0.0f, 1.0f };
		m_TVtx[1].Pos = { 0.5f, 0.5f, 0.0f, 1.0f };
		m_TVtx[2].Pos = { 0.5f, -0.5f, 0.0f, 1.0f };
		m_TVtx[3].Pos = { -0.5f, -0.5f, 0.0f, 1.0f };
		m_TVtx[0].Uv = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_TVtx[1].Uv = { 1.0f, 0.0f, 0.0f, 1.0f };
		m_TVtx[2].Uv = { 1.0f, 1.0f, 0.0f, 1.0f };
		m_TVtx[3].Uv = { 0.0f, 1.0f, 0.0f, 1.0f };
		GameVtxBuffer::Create<TargetVtx>(L"TargetDebugRect", m_TVtx);
		std::vector<UINT> m_IDX = { 0, 1, 2, 0, 2, 3 };
		GameIdxBuffer::Create<UINT>(L"TargetDebugRect", m_IDX);
		GameMesh::Create(L"TargetDebugRect");
	}


	/////////////////////////////// 추가했습니다. 
	// Sphere
	{
		Vtx3D V;
		std::vector<Vtx3D> SphereVtx;
		std::vector<DWORD> SphereIdx;

		float fRadius = 0.5f;

		// 북극점
		V.Pos = CVector{ 0.0f, fRadius, 0.0f, 1.0f };
		V.Uv = CVector{ 0.5f, 0.0f };
		V.Color = CVector{ 1.0f, 1.0f, 1.0f, 1.0f };
		V.Normal = V.Pos;
		V.Normal.Normalize3d();
		V.Normal.W = 0.0f;
		V.Tangent = CVector{ 1.0f, 0.0f, 0.0f, 0.0f };
		V.BiNormal = CVector{ 0.0f, 0.0f, 1.0f, 0.0f };

		SphereVtx.push_back(V);

		UINT iStackCount = 40; // 가로 분할 개수
		UINT iSliceCount = 40; // 세로 분할 개수

		float yRotAngle = DirectX::XM_PI / (float)iStackCount;
		float zRotAngle = DirectX::XM_2PI / (float)iSliceCount;

		float yUvRatio = 1.0f / (float)iSliceCount;
		float zUvRatio = 1.0f / (float)iStackCount;

		// PointToDir

		for (UINT y = 1; y < iStackCount; ++y)
		{
			float phi = y * yRotAngle;

			for (UINT z = 0; z < iSliceCount + 1; ++z)
			{
				float theta = z * zRotAngle;

				V.Pos = CVector
				{
					fRadius * sinf(y * yRotAngle) * cosf(z * zRotAngle),
					fRadius * cosf(y * yRotAngle),
					fRadius * sinf(y * yRotAngle) * sinf(z * zRotAngle),
					1.0f
				};


				V.Pos.W = 1.0f;
				V.Uv = CVector{ yUvRatio * z, zUvRatio * y };
				V.Color = CVector{ 1.0f, 1.0f, 1.0f, 1.0f };
				V.Normal = V.Pos;
				V.Normal.Normalize3d();
				V.Normal.W = 0.0f;

				V.Tangent.X = -fRadius * sinf(phi) * sinf(theta);
				V.Tangent.Y = 0.0f;
				V.Tangent.Z = fRadius * sinf(phi) * cosf(theta);
				V.Tangent.Normalize3d();
				V.Tangent.W = 0.0f;

				V.BiNormal = CVector::Cross3d(V.Tangent, V.Normal);
				V.BiNormal.Normalize3d();
				V.BiNormal.W = 0.0f;

				SphereVtx.push_back(V);
			}
		}

		// 남극점
		V.Pos = CVector{ 0.0f, -fRadius, 0.0f, 1.0f };
		V.Uv = CVector{ 0.5f, 1.0f };
		V.Color = CVector{ 1.0f, 1.0f, 1.0f, 1.0f };
		V.Normal = V.Pos;
		V.Normal.Normalize3d();
		V.Normal.W = 0.0f;
		SphereVtx.push_back(V);

		// 인덱스 버퍼 만들기
		SphereIdx.clear();
		for (UINT i = 0; i < iSliceCount; i++)
		{
			SphereIdx.push_back(0);
			SphereIdx.push_back(i + 2);
			SphereIdx.push_back(i + 1);
		}

		for (UINT y = 0; y < iStackCount - 2; ++y)
		{
			for (UINT z = 0; z < iSliceCount; ++z)
			{
				SphereIdx.push_back((iSliceCount + 1) * y + z + 1);
				SphereIdx.push_back((iSliceCount + 1) * (y + 1) + (z + 1) + 1);
				SphereIdx.push_back((iSliceCount + 1) * (y + 1) + z + 1);

				SphereIdx.push_back((iSliceCount + 1) * y + z + 1);
				SphereIdx.push_back((iSliceCount + 1) * y + (z + 1) + 1);
				SphereIdx.push_back((iSliceCount + 1) * (y + 1) + (z + 1) + 1);
			}
		}

		// 북극점 인덱스
		UINT iBotStart = (UINT)SphereVtx.size() - 1;

		for (UINT i = 0; i < iSliceCount; ++i)
		{
			SphereIdx.push_back(iBotStart);
			SphereIdx.push_back(iBotStart - (i + 2));
			SphereIdx.push_back(iBotStart - (i + 1));
		}

		GameVtxBuffer::Create(L"Sphere", SphereVtx);
		GameIdxBuffer::Create(L"Sphere", SphereIdx);
		GameMesh::Create(L"Sphere");
	}













//
//
//
//#pragma region SpriteCircle
//	{
//		// 버텍스버퍼
//		std::vector<Vtx2D> ArrVTX;
//		ArrVTX.resize(36);
//
//		float Theta = 10.0f;
//
//		CVector Start = { 0.0f, 0.2f, 0.0f, 1.0f };
//		CMatrix RM;
//		RM.UnitMat();
//		ArrVTX[0] = Start;
//
//		for (int i = 0; i < ArrVTX.size(); ++i)
//		{
//			RM.ArrV[0] = { cosf(GameMath::DTOR * Theta * i), sinf(GameMath::DTOR * Theta * i) + 0.7f, 0.0f, 1.0f };
//			RM.ArrV[1] = { sinf(GameMath::DTOR * Theta * i), cosf(GameMath::DTOR * Theta * i) + 0.7f ,0.0f, 1.0f };
//			ArrVTX[i].Pos = Start * RM;
//			ArrVTX[i].Color = CVector::RED;
//		}
//
//		GameVtxBuffer::Create(L"2DCICLE", ArrVTX, D3D11_USAGE::D3D11_USAGE_DEFAULT);
//
//		//인덱스 버퍼
//		std::vector<UINT> ArrIdx = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
//									10,	11, 12, 13, 14, 15, 16, 17, 18, 19,
//									20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
//									30, 31, 32, 33, 34, 35, 0 };
//		GameIdxBuffer::Create(L"2DCICLE", ArrIdx, D3D11_USAGE::D3D11_USAGE_DEFAULT);
//		GameMesh::Create(L"2DCICLE", L"2DCICLE", L"2DCICLE");
//	}
#pragma endregion

}







///////////////// 추가했습니다. 

unsigned int stackCount = 20;
unsigned int sliceCount = 20;
UINT vertexCount = 3;
int radius = 1;

void GameDevice::SphereMeshInit()
{
	std::vector<Vtx2D> m_Color;
	std::vector<UINT> m_IDX;
	m_Color.resize(1);
	Vtx2D center;
	center.Pos.X = 0.0f;
	center.Pos.Y = 0.0f;
	center.Pos.Z = 0.0f;
	unsigned int i = 0;
	for (double phi = 0.; phi < 2 * GameMath::PI - GameMath::PI / 50.; phi += GameMath::PI / 50.) // Azimuth [0, 2PI]
	{
		for (double theta = 0.; theta < GameMath::PI - GameMath::PI / 50.; theta += GameMath::PI / 50.) // Elevation [0, PI]
		{
			Vtx2D point;
			point.Pos.X = 5.0f * float(cos(phi) * sin(theta) + center.Pos.X);
			point.Pos.Y = 5.0f * float(sin(phi) * sin(theta) + center.Pos.Y);
			point.Pos.Z = 5.0f * float(cos(theta) + center.Pos.Z);
			m_Color[i].Color = CVector::WHITE;
			m_Color.push_back(point);
			m_IDX.push_back(i);
			m_IDX.push_back(i + 1);
			m_IDX.push_back(i + 2);
			i++;
		}
	}
	// 디바이스 폴리곤 
	GameVtxBuffer::Create<Vtx2D>(L"DevPolygon", m_Color);
	GameIdxBuffer::Create<UINT>(L"DevPolygon", m_IDX);
	GameMesh::Create(L"DevPolygon");

}
