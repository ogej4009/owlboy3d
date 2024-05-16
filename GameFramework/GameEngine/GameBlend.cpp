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
		MSG_ASSERT_CODE(L"�����Ͷ����� ������Ʈ ������ �����߽��ϴ�.");
	}
}

void GameBlend::Setting()
{
	GameDevice::MainObj()->Context()->OMSetBlendState(m_State, nullptr, 0xffffffff); //�⺻��0xffffffff
}