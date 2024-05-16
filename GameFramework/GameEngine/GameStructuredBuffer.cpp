#include "GameStructuredBuffer.h"


void GameStructuredBuffer::Create(UINT _iElementSize, UINT _iElementCount, void* _pSysMem, D3D11_USAGE _eUsage)
{
	// Create �� ȣ�� ��, ���� ���� ���� �� �ٽ� ����
	m_iElementSize = _iElementSize;
	m_iElementCount = _iElementCount;

	m_BufferDesc.ByteWidth = m_iElementSize * m_iElementCount;
	m_BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	m_BufferDesc.StructureByteStride = _iElementSize;

	if (D3D11_USAGE_DYNAMIC == _eUsage)
	{
		m_BufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		m_BufferDesc.Usage = _eUsage;
		m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		m_BufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	}

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = _pSysMem;

	if (nullptr != _pSysMem)
	{
		GameDevice::MainObj()->Device()->CreateBuffer(&m_BufferDesc, &tSub, &m_pBuffer);
	}
	else
	{
		GameDevice::MainObj()->Device()->CreateBuffer(&m_BufferDesc, nullptr, &m_pBuffer);
	}

	// SRV �����
	D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};

	tSRVDesc.Format = DXGI_FORMAT_UNKNOWN;
	tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	tSRVDesc.BufferEx.FirstElement = 0;
	tSRVDesc.BufferEx.Flags = 0;
	tSRVDesc.BufferEx.NumElements = m_iElementCount;

	HRESULT Result = GameDevice::MainObj()->Device()->CreateShaderResourceView(m_pBuffer, &tSRVDesc, &m_SRV);

	if (S_OK != Result)
	{
		assert(nullptr);
	}

	if (m_BufferDesc.BindFlags & D3D11_BIND_UNORDERED_ACCESS)
	{
		// UAV �����
		D3D11_UNORDERED_ACCESS_VIEW_DESC tUAVDesc = {};

		tUAVDesc.Format = DXGI_FORMAT_UNKNOWN;
		tUAVDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		tUAVDesc.Buffer.FirstElement = 0;
		tUAVDesc.Buffer.Flags = 0;
		tUAVDesc.Buffer.NumElements = m_iElementCount;

		Result = GameDevice::MainObj()->Device()->CreateUnorderedAccessView(m_pBuffer, &tUAVDesc, &m_UAV);

		if (Result != S_OK)
		{
			assert(nullptr);
		}
	}
}

void GameStructuredBuffer::UpdateDataRW(UINT _iRegisterNum)
{
	UINT i = -1;
	GameDevice::MainObj()->Context()->CSSetUnorderedAccessViews(_iRegisterNum, 1, &m_UAV, &i);
}

void GameStructuredBuffer::SetData(void* _pData, UINT _iSizeOfByte)
{
	assert(m_BufferDesc.Usage == D3D11_USAGE_DYNAMIC);

	D3D11_MAPPED_SUBRESOURCE tSub = {};
	GameDevice::MainObj()->Context()->Map(m_pBuffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, _pData, _iSizeOfByte);
	GameDevice::MainObj()->Context()->Unmap(m_pBuffer, 0);
}

void GameStructuredBuffer::Setting(SHADERTYPE _Type, unsigned int _Reg)
{
	switch (_Type)
	{
	case SHADERTYPE::SHADER_VS:
		GameDevice::MainObj()->Context()->VSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_HS:
		GameDevice::MainObj()->Context()->HSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_DS:
		GameDevice::MainObj()->Context()->DSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_GS:
		GameDevice::MainObj()->Context()->GSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_PS:
		GameDevice::MainObj()->Context()->PSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_END:
		break;
	default:
		break;
	}
}

void GameStructuredBuffer::Reset(UINT _Reg)
{
	ID3D11ShaderResourceView* pSRV = nullptr;
	GameDevice::MainObj()->Context()->VSSetShaderResources(_Reg, 1, &pSRV);
	GameDevice::MainObj()->Context()->HSSetShaderResources(_Reg, 1, &pSRV);
	GameDevice::MainObj()->Context()->CSSetShaderResources(_Reg, 1, &pSRV);
	GameDevice::MainObj()->Context()->DSSetShaderResources(_Reg, 1, &pSRV);
	GameDevice::MainObj()->Context()->GSSetShaderResources(_Reg, 1, &pSRV);
	GameDevice::MainObj()->Context()->PSSetShaderResources(_Reg, 1, &pSRV);
}

void GameStructuredBuffer::ClearRW(UINT _iRegisterNum)
{
	ID3D11UnorderedAccessView* pUAV = nullptr;
	UINT i = -1;
	GameDevice::MainObj()->Context()->CSSetUnorderedAccessViews(_iRegisterNum, 1, &pUAV, &i);
}

GameStructuredBuffer::GameStructuredBuffer()
	: m_SRV(nullptr)
	, m_UAV(nullptr)
	, m_iElementSize(0)
	, m_iElementCount(0)
{
}

GameStructuredBuffer::~GameStructuredBuffer()
{
	if (nullptr != m_SRV)
	{
		m_SRV->Release();
	}

	if (nullptr != m_UAV)
	{
		m_UAV->Release();
	}
}
