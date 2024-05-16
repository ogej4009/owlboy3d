#include "GameRasterizer.h"

GameRasterizer::GameRasterizer(const D3D11_RASTERIZER_DESC& _Desc) : m_Desc(_Desc)
{
	Create();
}

GameRasterizer::~GameRasterizer()
{
	if (nullptr != m_State)
	{
		m_State->Release();
	}
}

void GameRasterizer::Create()
{
	if (S_OK != GameDevice::MainObj()->Device()->CreateRasterizerState(&m_Desc, &m_State))
	{
		MSG_ASSERT_CODE(L"레스터라이저 스테이트 생성에 실패했습니다.");
	}
}

void GameRasterizer::Setting()
{
	GameDevice::MainObj()->Context()->RSSetState(m_State);
}

#pragma region 포인터
/*
	ID3D11Device::CreateRasterizerState(const	D3D11_RASTERIZER_DESC *pRasterizerDesc = &m_Desc, --> 이렇게 포인터를 넣어주면
												ID3D11RasterizerState **ppRasterizerState = &m_State )

	왜 값으로 넣어주는 것이 아니라 포인터로 넣어줄까?
	그 이유는 포인터로 인자를 넘겨줘야 메모리를 포인터메모리(8BYTE)만을 쓰고 처리할 수 있기 때문이다.

	왜 인자에 const인가? 그리고 &인가?
	1. 위험한 NULL 을 넣을 수 없고,
	2. 반드시 인자로 값을 넣을 수 있게 강제할 수 있다.
*/
#pragma endregion


#pragma region 많이하는 실수
/*
	const wchar_t* PTR;		포인터이다.
	PTR + 1;				가능하다. 그러나 이것은 주소를 바꾸는 행위이다. 하면안되는 것이다.
*/
#pragma endregion