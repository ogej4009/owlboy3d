#include "GameBlend.h"

GameBlend::GameBlend(const D3D11_BLEND_DESC& _Desc) : m_Desc(_Desc)
{
	Create();
}

GameBlend::~GameBlend()
{
	if (nullptr != m_State)
	{
		m_State->Release();
	}
}

void GameBlend::Create()
{
	if (S_OK != GameDevice::MainObj()->Device()->CreateBlendState(&m_Desc, &m_State))
	{
		// const wchar_t* PTR;
		// PTR + 1;
		MSG_ASSERT_CODE(L"레스터라이저 스테이트 생성에 실패했습니다.");
	}
}

void GameBlend::Setting()
{
	GameDevice::MainObj()->Context()->OMSetBlendState(m_State, nullptr, 0xffffffff); //기본값0xffffffff
}