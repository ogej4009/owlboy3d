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

	//  cpu���� ���ٰ���?
	if (Desc.Usage == D3D11_USAGE::D3D11_USAGE_DYNAMIC)
	{
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		Desc.CPUAccessFlags = 0;
	}

	// �ؽ�ó�� ������ִ� ��.
	// m_pTex�� ���ɴϴ�.
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
			MSG_ASSERT_CODE(CFile.FullPath() + L" : �ؽ�ó �ε��� �����߽��ϴ�.");
			return;
		}
	}
	else
	{
		// �ε��� �ߴ�.������ ���� ���� ���ߴ�. 
		if (S_OK != DirectX::LoadFromWICFile(CFile.FullPath(), DirectX::WIC_FLAGS_NONE, nullptr, m_Img))
		{
			MSG_ASSERT_CODE(CFile.FullPath() + L" : �ؽ�ó �ε��� �����߽��ϴ�.");
			return;
		}
	}

#pragma region ����
	/*
		m_SRV
		���̴��� �־��ִ� �� -> �� ������ ������ �ʿ��ϴ�.
		������ ���� �ʰ� �ϴ� ���� ����. �׷���ī���� ������ �ʿ��ϴ�
		�̷� �Լ� ���δ� �ᱹ ���������͸� �־��� �׷� �ٲ��ٰ� ���̴�.
		�������, ���÷�, �ؽ��Ĵ� ���̴��� ������ ��ģ��.
		(�������ٽ�,���� ��� ������ ��ü�� ������ �ش�.)
	*/
#pragma endregion


	Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	if (0 != (D3D11_BIND_SHADER_RESOURCE & Desc.BindFlags))
	{
		if (S_OK != DirectX::CreateShaderResourceView(GameDevice::MainObj()->Device(), m_Img.GetImages(), m_Img.GetImageCount(), m_Img.GetMetadata(), &m_SRV))
		{
			MSG_ASSERT_CODE(CFile.FullPath() + L" : ���̴� ���ҽ� ������ �����߽��ϴ�.");
			return;
		}
	}

	Desc.Width = (unsigned int)m_Img.GetMetadata().width;
	Desc.Height = (unsigned int)m_Img.GetMetadata().height;
}


// �ؽ����� ũ�⸦ ���ͷ� �ٲ��ִ� ��� 
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

	// ������۴� ��� �ִ� ���ҽ���?
	// �׷���ī�忡 �ִµ�
	// �װ� �����Ϸ���
	// �׷���ī��(Device And Context)���� ����� �þƾ� �Ѵ�.
	// �޸𸮿� ���õ� �Ŵϱ� Device�ϰ� ������ �ƴմϴ�.
	//HGAMEDEVICE::MainContext()->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_Sub);
	//memcpy_s(m_Sub.pData, m_BufferDesc.ByteWidth, _pData, m_BufferDesc.ByteWidth);
	// �ٽ����� �ٽ�ٰ� �˷��ִ°͵� �� �ؾ��Ѵ�.
	//HGAMEDEVICE::MainContext()->Unmap(m_pBuffer, 0);

	// ������ ó���� �����.
	// ��κ� �Ұ����ϴ�.
	// �����ϴٰ� �ϴ��� ��������.
	// �� ������ ���ϱ� ���ؼ� ����.
	// => ��������.
	GameDevice::MainObj()->Context()->Map(m_pTex, 0, D3D11_MAP_WRITE_DISCARD, 0, &MSUB);
	// MSUB�� �׷���ī��� ����� �����͸� �츮���� �ش�.
	// ���⿡ �ִ� �����͸� �����ϸ�
	// ���� �׷��� ī�忡 �ִ� �����Ͱ� �����Ǵ� ���̴�.
	// ���� ����ȵȴ�.
	// ���ؾ��Ѵٸ� ���Ƽ� �ض�.
	// 134 * 16 * 4 ��ŭ �־��ذ� ����Ʈ�� ����� ���ٸ�
	// 134 * �ȼ��ϳ� 16 * 4
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
		// 4����Ʈ �̹Ƿ�
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
	// ���� ���Ľ��̸�
// ���̴� ���ҽ��� �Ұ���
	if (0 != (D3D11_BIND_DEPTH_STENCIL & Desc.BindFlags))
	{
		if (S_OK != GameDevice::MainObj()->Device()->CreateDepthStencilView(m_pTex, nullptr, &m_DSV))
		{
			MSG_ASSERT_CODE(L"���̴� ���ҽ� ������ �����߽��ϴ�.");
		}
	}
	else
	{
		// ���ε� �÷��װ�
		// Desc.BindFlags �ȿ� D3D11_BIND_SHADER_RESOURCE �����Ͱ� ����ִٴ� ��.
		// �̰� ��������� ������ �� �ؽ�ó�� ���̴��� ������ ���ټ��� ����.
		if (0 != (D3D11_BIND_SHADER_RESOURCE & Desc.BindFlags))
		{
			if (S_OK != GameDevice::MainObj()->Device()->CreateShaderResourceView(m_pTex, nullptr, &m_SRV))
			{
				MSG_ASSERT_CODE(L"���̴� ���ҽ� ������ �����߽��ϴ�.");
			}
		}

		if (0 != (D3D11_BIND_RENDER_TARGET & Desc.BindFlags))
		{
			if (S_OK != GameDevice::MainObj()->Device()->CreateRenderTargetView(m_pTex, nullptr, &m_RTV))
			{
				MSG_ASSERT_CODE(L"���� Ÿ�� ������ �����߽��ϴ�.");
			}
		}
	}
}

#pragma region GetPixel
/*
	GetPixel �Լ�
	�Է¹��� ��ġ���� "�ؽ�ó �ȼ�"�� �������� �Լ�(���� ��� ���� 0,0)
	=> �̶� �Է¹޴� ��ġ�� (x, y)��� �ؽ�ó �ȼ� ��ġ�� (x, y)�����Ѵ�.
	��, ���� ���� �־���Ѵٴ� �ǹ�.
*/
#pragma endregion

CVector GameTexture::GetPixel(CVector _Pos)
{

	if (0.0f > _Pos.X || 0.0f > _Pos.Y)
	{
		return CVector::BLACK;
		MSG_ASSERT_CODE(L"�̷� �ȼ��� �������� �ʽ��ϴ�.");
	}

	if ((float)Desc.Width <= _Pos.X || (float)Desc.Height <= _Pos.Y)
	{
		return CVector::BLACK;
		MSG_ASSERT_CODE(L"�� �̹��� �ٱ� �ȼ��� ������ ���������� �߽��ϴ�.");
	}

#pragma region ����
	/*
		ĳ���ʹ� �� ����Ʈ �ϱ�? 1����Ʈ
		uint8_t(unsigned char) : 1����Ʈ / uint16_t(unsigned short) : 2����Ʈ
		0, 0 �ȼ��� R�� ������ => FirstColor[0]
		0, 0 �ȼ��� G�� ������ => FirstColor[1]
		0, 1 �ȼ��� R�� ������ => FirstColor[4]
		(��, ���� ���� 1����Ʈ�鼭, rgba ���� ��츸 �ش��Ѵ�. ��, �̹��� ���� ���˿� ���� �ٸ���!)
		�̹����� ���� ������ �����ü� �ִ�.
	*/
#pragma endregion

	uint8_t* FirstColor = m_Img.GetPixels();
	DXGI_FORMAT Fmt = m_Img.GetMetadata().format;
	CVector Color = CVector::BLACK;

#pragma region RGBA������(�ؽ���)
	/*
		(1, 0) �� ���, x�� �ʺ�(width)�� 1 ���ϰ� 0���� �ִ� ��ġ
		=> �ʺ� 10�̶�� �����ϸ�, 10 * 1 + 0�̱� ������ 10�� ��ġ��asss
		RGBA�� ������ŭ �߰��� 4�� ���ϴ� ������ ���ϴ� �ؽ�ó �ȼ��� R ���� ���� �� �ִ�.
		==> ��, FirstColor�� ���ϴ� ��ġ�� �ؽ�ó�� 0��° �����͸� ������ �ִ� ���̴�.
		(����� BGRA�̱� ������ B�� ����)
	*/
#pragma endregion

	switch (Fmt)
	{
	case DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM:
		FirstColor = &FirstColor[(Desc.Width * _Pos.UIY() + _Pos.UIX()) * 4];
		Color = CVector::ColorToUintInt8(FirstColor[2], FirstColor[1], FirstColor[0], FirstColor[3]);
		break;
	default:
		MSG_ASSERT_CODE(L"ó���Ҽ� ���� �����Դϴ�.");
		break;
	}
	return Color;

}

#pragma region �����Ͱ��
/*
	0, 0�ȼ��� r�� �������̴�
	���� �⺻���� ������ ����
	�� �ȼ��� �ǳʶٰ� ������ ���� 4�� �ؾ��Ѵ�.
	FirstColor += 4;
	0, 0�ȼ��� g�� ������
*/
#pragma endregion