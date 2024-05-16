#include "GameTexture.h"
#include <vector>

GameTexture::GameTexture() : m_SRV(nullptr), m_RTV(nullptr), m_DSV(nullptr), m_pTex(nullptr)
{
}

GameTexture::~GameTexture()
{
	if (nullptr != m_SRV) { m_SRV->Release(); };
	if (nullptr != m_RTV) { m_RTV->Release(); };
	if (nullptr != m_DSV) { m_DSV->Release(); };
	if (nullptr != m_pTex) { m_pTex->Release(); };
}

void GameTexture::Create(CVector _Size, DXGI_FORMAT _Fmt, UINT _BindFlag, D3D11_USAGE _eUsage)
{
	D3D11_TEXTURE2D_DESC _NewDesc = { 0, };
	_NewDesc.Width = (unsigned)_Size.IX();
	_NewDesc.Height = (unsigned)_Size.IY();
	_NewDesc.ArraySize = 1; //
	_NewDesc.Usage = _eUsage;
	_NewDesc.Format = _Fmt;

	_NewDesc.SampleDesc.Count = 1;
	_NewDesc.SampleDesc.Quality = 0;
	_NewDesc.MipLevels = 1;
	_NewDesc.BindFlags = _BindFlag;

	Create(_NewDesc);
}

void GameTexture::Create(D3D11_TEXTURE2D_DESC _Desc)
{
	Desc = _Desc;

	//  cpu에서 접근가능?
	if (Desc.Usage == D3D11_USAGE::D3D11_USAGE_DYNAMIC)
	{
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		Desc.CPUAccessFlags = 0;
	}

	// 텍스처를 만들어주는 것.
	// m_pTex을 얻어옵니다.
	if (S_OK != GameDevice::MainObj()->Device()->CreateTexture2D(&Desc, nullptr, (ID3D11Texture2D**)&m_pTex))
	{
		assert(false);
	}

	SettingData();
}

void GameTexture::Create(ID3D11Texture2D* _BackBufferTex)
{
	m_pTex = _BackBufferTex;
	_BackBufferTex->GetDesc(&Desc);
	SettingData();
}

void GameTexture::Load()
{
	GameString Ext = CFile.Ext();

	if (Ext == L"dds")
	{

	}
	else if (Ext == L"tga")
	{
		int a = 0;
		if (S_OK != DirectX::LoadFromTGAFile(CFile.FullPath(), nullptr, m_Img))
		{
			MSG_ASSERT_CODE(CFile.FullPath() + L" : 텍스처 로딩에 실패했습니다.");
			return;
		}
	}
	else
	{
		// 로딩만 했다.권한은 아직 얻지 못했다. 
		if (S_OK != DirectX::LoadFromWICFile(CFile.FullPath(), DirectX::WIC_FLAGS_NONE, nullptr, m_Img))
		{
			MSG_ASSERT_CODE(CFile.FullPath() + L" : 텍스처 로딩에 실패했습니다.");
			return;
		}
	}

#pragma region 권한
	/*
		m_SRV
		쉐이더에 넣어주는 것 -> 이 행위도 권한이 필요하다.
		권한을 얻지 않고 하는 것이 없다. 그래픽카드의 권한이 필요하다
		이런 함수 내부는 결국 이중포인터를 넣어줘 그럼 바꿔줄게 식이다.
		상수버퍼, 샘플러, 텍스쳐는 쉐이더에 영향을 끼친다.
		(뎁스스텐실,블랜드 등등 렌더링 전체에 영향을 준다.)
	*/
#pragma endregion


	Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	if (0 != (D3D11_BIND_SHADER_RESOURCE & Desc.BindFlags))
	{
		if (S_OK != DirectX::CreateShaderResourceView(GameDevice::MainObj()->Device(), m_Img.GetImages(), m_Img.GetImageCount(), m_Img.GetMetadata(), &m_SRV))
		{
			MSG_ASSERT_CODE(CFile.FullPath() + L" : 쉐이더 리소스 생성에 실패했습니다.");
			return;
		}
	}

	Desc.Width = (unsigned int)m_Img.GetMetadata().width;
	Desc.Height = (unsigned int)m_Img.GetMetadata().height;
}


// 텍스쳐의 크기를 벡터로 바꿔주는 기능 
CVector GameTexture::Size()
{
	return CVector((float)Desc.Width, (float)Desc.Height, 1.0f);
}


void GameTexture::Setting(SHADERTYPE _Type, unsigned int _Reg)
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

void GameTexture::Reset(SHADERTYPE _Type, unsigned int _Reg)
{
	ID3D11ShaderResourceView* NULLPTR = nullptr;

	switch (_Type)
	{
	case SHADERTYPE::SHADER_VS:
		GameDevice::MainObj()->Context()->VSSetShaderResources(_Reg, 1, &NULLPTR);
		break;
	case SHADERTYPE::SHADER_HS:
		GameDevice::MainObj()->Context()->HSSetShaderResources(_Reg, 1, &NULLPTR);
		break;
	case SHADERTYPE::SHADER_DS:
		GameDevice::MainObj()->Context()->DSSetShaderResources(_Reg, 1, &NULLPTR);
		break;
	case SHADERTYPE::SHADER_GS:
		GameDevice::MainObj()->Context()->GSSetShaderResources(_Reg, 1, &NULLPTR);
		break;
	case SHADERTYPE::SHADER_PS:
		GameDevice::MainObj()->Context()->PSSetShaderResources(_Reg, 1, &NULLPTR);
		break;
	case SHADERTYPE::SHADER_END:
		break;
	default:
		break;
	}
}

void GameTexture::SetPixel(void* _PixelData, int Size)
{
	D3D11_MAPPED_SUBRESOURCE MSUB;

	// 상수버퍼는 어디에 있는 리소스죠?
	// 그래픽카드에 있는데
	// 그걸 수정하려면
	// 그래픽카드(Device And Context)에게 허락을 맡아야 한다.
	// 메모리와 관련된 거니까 Device일거 같은데 아닙니다.
	//HGAMEDEVICE::MainContext()->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_Sub);
	//memcpy_s(m_Sub.pData, m_BufferDesc.ByteWidth, _pData, m_BufferDesc.ByteWidth);
	// 다썼으면 다썼다고 알려주는것도 꼭 해야한다.
	//HGAMEDEVICE::MainContext()->Unmap(m_pBuffer, 0);

	// 랜더링 처리가 멈춘다.
	// 대부분 불가능하다.
	// 가능하다고 하더라도 위험하죠.
	// 그 위험을 피하기 위해서 멈춰.
	// => 느려진다.
	GameDevice::MainObj()->Context()->Map(m_pTex, 0, D3D11_MAP_WRITE_DISCARD, 0, &MSUB);
	// MSUB에 그래픽카드와 연결된 포인터를 우리에게 준다.
	// 여기에 있는 포인터를 수정하면
	// 실제 그래픽 카드에 있는 데이터가 수정되는 것이다.
	// 많이 쓰면안된다.
	// 꼭해야한다면 몰아서 해라.
	// 134 * 16 * 4 만큼 넣어준것 바이트로 계산해 본다면
	// 134 * 픽셀하나 16 * 4
	memcpy_s(MSUB.pData, Size, _PixelData, Size);
	GameDevice::MainObj()->Context()->Unmap(m_pTex, 0);
}

float4 GameTexture::GetPixel(int2 _Pos)
{
	if (Size().X <= _Pos.x)
	{
		_Pos.x = 0;
	}

	if (Size().Y <= _Pos.y)
	{
		_Pos.y = 0;
	}

	if (0 > _Pos.y)
	{
		_Pos.y = 0;
	}

	if (0 > _Pos.x)
	{
		_Pos.x = 0;
	}

	uint8_t* Ptr = m_Img.GetPixels();
	CVector Color = CVector::ZERO;
	DXGI_FORMAT For = m_Img.GetMetadata().format;
	switch (For)
	{
	case DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM:
		// 4바이트 이므로
		Ptr = Ptr + (((_Pos.y * (int)Size().X) + _Pos.x) * 4);
		Color.X = Ptr[0] / 255.0f; // R;
		Color.Y = Ptr[1] / 255.0f; // G;
		Color.Z = Ptr[2] / 255.0f; // B;
		Color.W = Ptr[3] / 255.0f; // A;
		break;
	default:
		break;
	}
	return Color;
}

void GameTexture::SettingData()
{
	// 뎁스 스탠실이면
// 쉐이더 리소스가 불가능
	if (0 != (D3D11_BIND_DEPTH_STENCIL & Desc.BindFlags))
	{
		if (S_OK != GameDevice::MainObj()->Device()->CreateDepthStencilView(m_pTex, nullptr, &m_DSV))
		{
			MSG_ASSERT_CODE(L"쉐이더 리소스 생성에 실패했습니다.");
		}
	}
	else
	{
		// 바인드 플래그가
		// Desc.BindFlags 안에 D3D11_BIND_SHADER_RESOURCE 데이터가 들어있다는 것.
		// 이걸 만들어주지 않으면 이 텍스처를 쉐이더에 세팅을 해줄수가 없다.
		if (0 != (D3D11_BIND_SHADER_RESOURCE & Desc.BindFlags))
		{
			if (S_OK != GameDevice::MainObj()->Device()->CreateShaderResourceView(m_pTex, nullptr, &m_SRV))
			{
				MSG_ASSERT_CODE(L"쉐이더 리소스 생성에 실패했습니다.");
			}
		}

		if (0 != (D3D11_BIND_RENDER_TARGET & Desc.BindFlags))
		{
			if (S_OK != GameDevice::MainObj()->Device()->CreateRenderTargetView(m_pTex, nullptr, &m_RTV))
			{
				MSG_ASSERT_CODE(L"랜더 타겟 생성에 실패했습니다.");
			}
		}
	}
}

#pragma region GetPixel
/*
	GetPixel 함수
	입력받은 위치에서 "텍스처 픽셀"의 가져오는 함수(왼쪽 상단 부터 0,0)
	=> 이때 입력받는 위치가 (x, y)라면 텍스처 픽셀 위치도 (x, y)여야한다.
	즉, 동일 선상에 있어야한다는 의미.
*/
#pragma endregion

CVector GameTexture::GetPixel(CVector _Pos)
{

	if (0.0f > _Pos.X || 0.0f > _Pos.Y)
	{
		return CVector::BLACK;
		MSG_ASSERT_CODE(L"이런 픽셀은 존재하지 않습니다.");
	}

	if ((float)Desc.Width <= _Pos.X || (float)Desc.Height <= _Pos.Y)
	{
		return CVector::BLACK;
		MSG_ASSERT_CODE(L"맵 이미지 바깥 픽셀의 색깔을 가져오려고 했습니다.");
	}

#pragma region 포맷
	/*
		캐릭터는 몇 바이트 일까? 1바이트
		uint8_t(unsigned char) : 1바이트 / uint16_t(unsigned short) : 2바이트
		0, 0 픽셀의 R의 포인터 => FirstColor[0]
		0, 0 픽셀의 G의 포인터 => FirstColor[1]
		0, 1 픽셀의 R의 포인터 => FirstColor[4]
		(단, 위의 식은 1바이트면서, rgba 순일 경우만 해당한다. 즉, 이미지 색깔 포맷에 따라 다르다!)
		이미지의 색깔 포맷을 가져올수 있다.
	*/
#pragma endregion

	uint8_t* FirstColor = m_Img.GetPixels();
	DXGI_FORMAT Fmt = m_Img.GetMetadata().format;
	CVector Color = CVector::BLACK;

#pragma region RGBA데이터(텍스쳐)
	/*
		(1, 0) 일 경우, x의 너비(width)을 1 곱하고 0번에 있는 위치
		=> 너비가 10이라고 가정하면, 10 * 1 + 0이기 때문에 10번 위치로asss
		RGBA의 개수만큼 추가로 4를 곱하는 것으로 원하는 텍스처 픽셀의 R 값을 얻을 수 있다.
		==> 즉, FirstColor는 원하는 위치의 텍스처의 0번째 포인터를 가지고 있는 것이다.
		(현재는 BGRA이기 때문에 B의 색상)
	*/
#pragma endregion

	switch (Fmt)
	{
	case DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM:
		FirstColor = &FirstColor[(Desc.Width * _Pos.UIY() + _Pos.UIX()) * 4];
		Color = CVector::ColorToUintInt8(FirstColor[2], FirstColor[1], FirstColor[0], FirstColor[3]);
		break;
	default:
		MSG_ASSERT_CODE(L"처리할수 없는 포맷입니다.");
		break;
	}
	return Color;

}

#pragma region 포인터계산
/*
	0, 0픽셀의 r의 포인터이다
	가장 기본적인 포인터 문법
	한 픽셀을 건너뛰고 싶으면 보통 4로 해야한다.
	FirstColor += 4;
	0, 0픽셀의 g의 포인터
*/
#pragma endregion