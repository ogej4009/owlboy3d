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

#pragma region 구조체분석
/*
	ByteWidth		: 버퍼 만들 떄 해당 구조체/클래스 사이즈
	Usage			: 값이 계속 수정되는 D3D11_USAGE_DYNAMIC 입니다.
	CPUAccessFlags	: 언제든 CPU가 ACCESS하도록 만듬
	BindFlags		: 파이프라인에 바인딩되는 방법결정

	그래픽디바이스에 넘겨주는 작업(그래픽카드에저장)
	DEVICE	: 메모리 할당
	CONTEXT : 조작하고 사용
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
		MSG_ASSERT_CODE(L"상수버퍼 세팅에 실패했습니다");
	}
}

void GameConstantBuffer::DataChange(void* _Data, unsigned int _Size)
{
	if (m_BufferDesc.ByteWidth != _Size)
	{
		MSG_ASSERT_CODE(Name() + L" 상수버퍼의 크기가 다릅니다.");
	}

	GameDevice::MainObj()->Context()->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_SubData);
	memcpy_s(m_SubData.pData, m_BufferDesc.ByteWidth, _Data, m_BufferDesc.ByteWidth);
	GameDevice::MainObj()->Context()->Unmap(m_pBuffer, 0);
}


#pragma region Context->Map의쓰임, DataChange의의미
/*
	"데이터의수정"을 위한 접근
	m_pBuffer의 내용을 수정하기 위해 그래픽카드에 접근했다.

	버텍스도 수정할 수 있다.
	점의 갯수를 조정한다. 예를들면 4개->6개(비효율적이긴 하다)

	그래픽카드는 시스템의 안정성을 위해, 멀티쓰레드 환경일 경우를 대비해서
	어떤 장치도 사용하지 못하게 막는다. 마치 파일 입출력처럼 제어한다.
	(프로그램실행중에 외부에서 파일을 열때 다른 접근을 허용하지 않는 것처럼)

	레스터라이저에서 나온 픽셀을 검출하려면 범위가 있어야 한다.
	MAP이라는 것은 누가 쓰고 있으면 접근하지 못하게 막는다.

	GameDevice::MainObj()->Context()->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_SubData);
	여기서 &m_SubData -> const가 안붙었으니 수정되서 넘어올것

	memcpy_s(m_SubData.pData, m_BufferDesc.ByteWidth, _Data, m_BufferDesc.ByteWidth);
	단지 데이터의 수정을 하는 것이다. 바이트를 바꾸거나 하는 것은 할 수 없다.

	GameDevice::MainObj()->Context()->Unmap(m_pBuffer, 0);
	사용권을 반환해준다. 다른 장치가 쓸수있게 다썻다고 알려준다.

*/
#pragma endregion 