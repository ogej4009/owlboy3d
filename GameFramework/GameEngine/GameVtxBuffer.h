#pragma once
#include <vector>
#include <GameObjTFuncMgr.h>
#include "GameDevBuffer.h"
#include <CPtr.h>

class GameVtxBuffer : public GameObjTFuncMgr<GameVtxBuffer>, public GameDevBuffer
{
public:
	template<typename T>
	static void Create(const GameString& _Name, std::vector<T> _Vtx, D3D11_USAGE _USAGE = D3D11_USAGE::D3D11_USAGE_DEFAULT)
	{
		CPtr<GameVtxBuffer> Res = CreateAndInsert(_Name);
		Res->Create(_Vtx.size(), sizeof(T), &_Vtx[0], _USAGE);
	}

public:
	unsigned int m_Size;
	unsigned int m_Count;
	unsigned int m_Offset;

	void Create(size_t _Count,
		size_t _Size,
		const void* _Data,
		D3D11_USAGE _USAGE = D3D11_USAGE::D3D11_USAGE_DEFAULT);

public:
	void Setting();

public:
	GameVtxBuffer();
	~GameVtxBuffer();
};