#pragma once
#include <vector>
#include <GameObjTFuncMgr.h>
#include "GameDevBuffer.h"
#include <CPtr.h>

class GameIdxBuffer : public GameObjTFuncMgr<GameIdxBuffer>, public GameDevBuffer
{
public:
	template<typename T>
	static void Create(const GameString& _Name, std::vector<T> _Idx, D3D11_USAGE _USAGE = D3D11_USAGE::D3D11_USAGE_DEFAULT)
	{
		CPtr<GameIdxBuffer> Res = CreateAndInsert(_Name);

		DXGI_FORMAT Fmt;

		if (2 == sizeof(T))
		{
			Fmt = DXGI_FORMAT::DXGI_FORMAT_R16_UINT;
		}
		else if (4 == sizeof(T))
		{
			Fmt = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
		}

		Res->Create(_Idx.size(), sizeof(T), &_Idx[0], Fmt, _USAGE);
	}

private:
	DXGI_FORMAT m_Fmt;
	unsigned int m_Size;
	unsigned int m_Count;
	unsigned int m_Offset;

public:
	unsigned int Count()
	{
		return m_Count;
	}

public:
	void Create(size_t _Count, size_t _Size, const void* _Data, DXGI_FORMAT _Fmt, D3D11_USAGE _USAGE = D3D11_USAGE::D3D11_USAGE_DEFAULT);

public:
	void Setting();

public:
	GameIdxBuffer();
	~GameIdxBuffer();
};