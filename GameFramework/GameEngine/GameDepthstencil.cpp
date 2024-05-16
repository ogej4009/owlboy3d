#include "GameDepthstencil.h"

GameDepthstencil::GameDepthstencil(const D3D11_DEPTH_STENCIL_DESC& _Desc) : m_Desc(_Desc)
{
	Create();
}

GameDepthstencil::~GameDepthstencil()
{
	if (nullptr != m_State)
	{
		m_State->Release();
	}
}

void GameDepthstencil::Create()
{
	if (S_OK != GameDevice::MainObj()->Device()->CreateDepthStencilState(&m_Desc, &m_State))
	{
		MSG_ASSERT_CODE(L"레스터라이저 스테이트 생성에 실패했습니다.");
	}
}

void GameDepthstencil::Setting()
{
	GameDevice::MainObj()->Context()->OMSetDepthStencilState(m_State, 0);
}