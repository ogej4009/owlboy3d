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
		MSG_ASSERT_CODE(L"�����Ͷ����� ������Ʈ ������ �����߽��ϴ�.");
	}
}

void GameRasterizer::Setting()
{
	GameDevice::MainObj()->Context()->RSSetState(m_State);
}

#pragma region ������
/*
	ID3D11Device::CreateRasterizerState(const	D3D11_RASTERIZER_DESC *pRasterizerDesc = &m_Desc, --> �̷��� �����͸� �־��ָ�
												ID3D11RasterizerState **ppRasterizerState = &m_State )

	�� ������ �־��ִ� ���� �ƴ϶� �����ͷ� �־��ٱ�?
	�� ������ �����ͷ� ���ڸ� �Ѱ���� �޸𸮸� �����͸޸�(8BYTE)���� ���� ó���� �� �ֱ� �����̴�.

	�� ���ڿ� const�ΰ�? �׸��� &�ΰ�?
	1. ������ NULL �� ���� �� ����,
	2. �ݵ�� ���ڷ� ���� ���� �� �ְ� ������ �� �ִ�.
*/
#pragma endregion


#pragma region �����ϴ� �Ǽ�
/*
	const wchar_t* PTR;		�������̴�.
	PTR + 1;				�����ϴ�. �׷��� �̰��� �ּҸ� �ٲٴ� �����̴�. �ϸ�ȵǴ� ���̴�.
*/
#pragma endregion