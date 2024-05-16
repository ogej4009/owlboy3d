#include "GameConstantBuffer.h"

void GameConstantBuffer::Setting(SHADERTYPE _Type, unsigned int _Reg)
{
	switch (_Type)
	{
	case SHADERTYPE::SHADER_VS:
		GameDevice::MainObj()->Context()->VSSetConstantBuffers(_Reg, 1, &m_pBuffer);
		break;
	case SHADERTYPE::SHADER_HS:
		GameDevice::MainObj()->Context()->HSSetConstantBuffers(_Reg, 1, &m_pBuffer);
		break;
	case SHADERTYPE::SHADER_DS:
		GameDevice::MainObj()->Context()->DSSetConstantBuffers(_Reg, 1, &m_pBuffer);
		break;
	case SHADERTYPE::SHADER_GS:
		GameDevice::MainObj()->Context()->GSSetConstantBuffers(_Reg, 1, &m_pBuffer);
		break;
	case SHADERTYPE::SHADER_PS:
		GameDevice::MainObj()->Context()->PSSetConstantBuffers(_Reg, 1, &m_pBuffer);
		break;
	case SHADERTYPE::SHADER_END:
		break;
	default:
		break;
	}
}

#pragma region ����ü�м�
/*
	ByteWidth		: ���� ���� �� �ش� ����ü/Ŭ���� ������
	Usage			: ���� ��� �����Ǵ� D3D11_USAGE_DYNAMIC �Դϴ�.
	CPUAccessFlags	: ������ CPU�� ACCESS�ϵ��� ����
	BindFlags		: ���������ο� ���ε��Ǵ� �������

	�׷��ȵ���̽��� �Ѱ��ִ� �۾�(�׷���ī�忡����)
	DEVICE	: �޸� �Ҵ�
	CONTEXT : �����ϰ� ���
*/
#pragma endregion

void GameConstantBuffer::Create(unsigned int _Size)
{
	m_BufferDesc.ByteWidth = _Size;
	m_BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if (S_OK != GameDevice::MainObj()->Device()->CreateBuffer(&m_BufferDesc, nullptr, &m_pBuffer))
	{
		MSG_ASSERT_CODE(L"������� ���ÿ� �����߽��ϴ�");
	}
}

void GameConstantBuffer::DataChange(void* _Data, unsigned int _Size)
{
	if (m_BufferDesc.ByteWidth != _Size)
	{
		MSG_ASSERT_CODE(Name() + L" ��������� ũ�Ⱑ �ٸ��ϴ�.");
	}

	GameDevice::MainObj()->Context()->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_SubData);
	memcpy_s(m_SubData.pData, m_BufferDesc.ByteWidth, _Data, m_BufferDesc.ByteWidth);
	GameDevice::MainObj()->Context()->Unmap(m_pBuffer, 0);
}


#pragma region Context->Map�Ǿ���, DataChange���ǹ�
/*
	"�������Ǽ���"�� ���� ����
	m_pBuffer�� ������ �����ϱ� ���� �׷���ī�忡 �����ߴ�.

	���ؽ��� ������ �� �ִ�.
	���� ������ �����Ѵ�. ������� 4��->6��(��ȿ�����̱� �ϴ�)

	�׷���ī��� �ý����� �������� ����, ��Ƽ������ ȯ���� ��츦 ����ؼ�
	� ��ġ�� ������� ���ϰ� ���´�. ��ġ ���� �����ó�� �����Ѵ�.
	(���α׷������߿� �ܺο��� ������ ���� �ٸ� ������ ������� �ʴ� ��ó��)

	�����Ͷ��������� ���� �ȼ��� �����Ϸ��� ������ �־�� �Ѵ�.
	MAP�̶�� ���� ���� ���� ������ �������� ���ϰ� ���´�.

	GameDevice::MainObj()->Context()->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_SubData);
	���⼭ &m_SubData -> const�� �Ⱥپ����� �����Ǽ� �Ѿ�ð�

	memcpy_s(m_SubData.pData, m_BufferDesc.ByteWidth, _Data, m_BufferDesc.ByteWidth);
	���� �������� ������ �ϴ� ���̴�. ����Ʈ�� �ٲٰų� �ϴ� ���� �� �� ����.

	GameDevice::MainObj()->Context()->Unmap(m_pBuffer, 0);
	������ ��ȯ���ش�. �ٸ� ��ġ�� �����ְ� �ٛ��ٰ� �˷��ش�.

*/
#pragma endregion 