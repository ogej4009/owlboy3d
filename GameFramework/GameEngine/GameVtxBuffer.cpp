#include "GameVtxBuffer.h"

GameVtxBuffer::GameVtxBuffer() : m_Offset(0)
{
}

GameVtxBuffer::~GameVtxBuffer()
{
}

void GameVtxBuffer::Create(size_t _Count, size_t _Size, const void* _Data, D3D11_USAGE _USAGE)
{

	m_Size = (unsigned int)_Size; // �� �ϳ��� ������
	m_Count = (unsigned int)_Count; //  ����ü�� �޸� ũ��

	//										 4         32
	m_BufferDesc.ByteWidth = (unsigned int)(_Count * _Size);
	m_BufferDesc.Usage = _USAGE; // ��� ������ �޶�. ���� = �׷���ī�忡 ����

	// �̳༮�� cpu���� �����ҰŴ� ���ҰŴ�.
	// D3D11_USAGE::D3D11_USAGE_DEFAULT �׷��� ī�忡 ����Ǵµ� ���� ���Ѵ�.
	// D3D11_USAGE::D3D11_USAGE_DYNAMIC �׷��� ī�忡 ����Ǵµ� ���� �Ѵ�.
	// ����Ʈ�� ������ �� ���ٴ� �ǹ�  

	if (m_BufferDesc.Usage == D3D11_USAGE::D3D11_USAGE_DYNAMIC)
	{
		m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	// �׷���ī�忡 �޸𸮰����� ��û
	// �� ���� �̴�. 
	// BindFlags(�뵵���ÿ�) : �����Ѵ�. ���ؽ�, �ε���, ����̽� ���� ��� �߿��� �ϳ���.... 
	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA DS = {};
	DS.pSysMem = _Data;

	if (S_OK != GameDevice::MainObj()->Device()->CreateBuffer(&m_BufferDesc, &DS, &m_pBuffer))
	{
		MSG_ASSERT_CODE(L"���ؽ� ���� ������ �����߽��ϴ�");
	}
}

void GameVtxBuffer::Setting()
{
	// ������ 16�� �ε�.
	// 0, 1 1���� �����ϰڴ�.
	// m_pBuffer �� ���ؽ� ���۸�
	// �� ���ؽ� ������ ���ؽ� 1���� ũ��� m_Size
	// �� ���ؽ��� ������ 0������ �����ϰڴ�.
	// 100
	// 50��°���͵� ���� ����.
	GameDevice::MainObj()->Context()->IASetVertexBuffers(0, 1, &m_pBuffer, &m_Size, &m_Offset);
}

#pragma region ����
/*
	� �ڷ����� �ּҰ��� �����Ҽ� ����
	� �ڷ����� �ּҰ��� �����Ҽ� ���� �������� �ּҰ��� ������ ���� ������ �ּҰ�.
	int* const* const* const Ptr = nullptr;
*/
#pragma endregion