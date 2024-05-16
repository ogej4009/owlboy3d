#pragma once
#include <GameObjTFuncMgr.h>
#include "GameVtxBuffer.h"
#include "GameIdxBuffer.h"

class GameMesh : public GameObjTFuncMgr<GameMesh>
{
private:
	unsigned int m_InstancedRenderCount;
	D3D_PRIMITIVE_TOPOLOGY m_DrawType;

public:
	void InstancedRenderCount(unsigned int _InstancedRenderCount)
	{
		m_InstancedRenderCount = _InstancedRenderCount;
	}

	void DrawType(D3D_PRIMITIVE_TOPOLOGY _DrawType)
	{
		m_DrawType = _DrawType;
	}

public:
	static CPtr<GameMesh> Create(const GameString& _Name)
	{
		CPtr<GameMesh> Mesh = CreateAndInsert(_Name);
		Mesh->SetVtxBuffer(_Name);
		Mesh->SetIdxBuffer(_Name);

		return Mesh;
	}

	static CPtr<GameMesh> Create(const GameString& _Name, const GameString& _VB, const GameString& _IB)
	{
		CPtr<GameMesh> Mesh = CreateAndInsert(_Name);
		Mesh->SetVtxBuffer(_VB);
		Mesh->SetIdxBuffer(_IB);
		return Mesh;
	}

private:
	CPtr<GameVtxBuffer> m_VtxBuffer;
	CPtr<GameIdxBuffer> m_IdxBuffer;

public:
	CPtr<GameVtxBuffer> GetVtxBuffer() { return m_VtxBuffer; }
	CPtr<GameIdxBuffer> GetIdxBuffer() { return m_IdxBuffer; }

public:
	void SetVtxBuffer(CPtr<GameVtxBuffer> _Buffer);
	void SetIdxBuffer(CPtr<GameIdxBuffer> _Buffer);

public:
	void SetVtxBuffer(const GameString& _Name);
	void SetIdxBuffer(const GameString& _Name);

public:
	void Render();

public:
	GameMesh();
	~GameMesh();
};
