#pragma once
#include "GameDevice.h"

class GameDevBuffer
{
protected:
	D3D11_BUFFER_DESC m_BufferDesc;
	ID3D11Buffer* m_pBuffer;
	ID3D11Buffer* m_instanceBuffer;

public:
	GameDevBuffer() : m_instanceBuffer(nullptr), m_pBuffer(nullptr), m_BufferDesc({ 0, })  // ����̴ϼȶ���������
	{
	}

	~GameDevBuffer()
	{
		if (nullptr != m_pBuffer)
		{
			m_pBuffer->Release();
		}

		if (nullptr != m_instanceBuffer)
		{
			m_instanceBuffer->Release();
		}
	}
};

// ����̽� ���� 
// �׷���ī�忡 ����̽��� ���ϴ� ������ ���� ������ Ȯ���ش޶�� ��û�� ������. 
// ���α׷� -(��û)-> ����̽� -> �׷���ī�� : ����  
// ���α׷� -(��û)-> CPU					 : ����

// �׷���ī�� -> �޸� ��� 
// �޸� ���� ��û�� �ϸ�, �׷��� ī�尡 �������̴� �׸��� �׸��� ������ ���߰�(�ϰ� �ִٸ�...) 
// RUN �ϴ� �޸𸮸� Ȱ���� �ߴ� ����ϰ�, ��û�� �޴´�. 