#include "GameDevice.h"
#include "GameDebugPlus.h"
#include "GameRenderTarget.h"
bool GameDevice::bDefResInit = false;

GameDevice::GameDevice()
	: m_MC(0)
	, m_MQ(0)
	, m_Color(CVector::BLUE) // �Ķ�ȭ��
	, m_pDevice(nullptr)
	, m_pContext(nullptr)
	, m_pSwapChain(nullptr)
	//, m_BackBufferTex(nullptr)
	//, m_DepthStencilTex(nullptr)
	//, m_RTV(nullptr)
	//, m_DSV(nullptr)
{
}

GameDevice::~GameDevice()
{
	//if (nullptr != m_DSV) { m_DSV->Release(); }
	//if (nullptr != m_RTV) { m_RTV->Release(); }
	//if (nullptr != m_DepthStencilTex) { m_DepthStencilTex->Release(); }
	//if (nullptr != m_BackBufferTex) { m_BackBufferTex->Release(); }
	if (nullptr != m_pSwapChain) { m_pSwapChain->Release(); }
	if (nullptr != m_pContext) { m_pContext->Release(); }
	if (nullptr != m_pDevice) { m_pDevice->Release(); }
}

void GameDevice::Init(const CPtr<GameWin>& _Window)
{

	if (nullptr == _Window)
	{
		MSG_ASSERT_CODE(L"�������� �ʴ� �����쿡 ����̽��� ������Ű���� ������� �߽��ϴ�");
	}

	m_Win = _Window;

	int iFlag = 0;

	// �Ӽ�-C++-��ó����-����������-��ũ��
	// #define	_DEBUG
	// �̰��� üũ �ؾ� #ifdef _DEBUG ~ #endif �� �� �� �ִ�. 
	// DEBUG x64�� ���� ����̽� �ɼ� ������ ����. 
#ifdef _DEBUG
	// ����̽� ����� ��尡 ����� ��� 
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// ����̽� ����
	D3D_FEATURE_LEVEL eLV = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	if (S_OK != D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		iFlag,
		nullptr, // ������ �ִ���� �˾Ƴ��� ��
		0,
		D3D11_SDK_VERSION, // ���� �����쿡 ��ġ�� SDK ����
		&m_pDevice,
		&eLV,
		&m_pContext))
	{
		MSG_ASSERT_CODE(L"����̽��� ���ؽ�Ʈ ������ �����߽��ϴ�.");
	}



	m_MC = 4;
	if (S_OK != m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R32G32B32A32_UINT, m_MC, &m_MQ))
	{
		m_MC = 1;
		if (S_OK != m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UINT, m_MC, &m_MQ))
		{
			MSG_ASSERT_CODE(L"��Ƽ���ø� üũ�� ����� ���� �ʾҽ��ϴ�.");
		}
	}

	CreateSwapChain();
	//CreateDepthStencil();
	//CreateViewPort();

	////////////////////////////////////////////// �߰� 
	CreateBackBufferTarget();


	// �ϳ��� ����̽��� ��������� �ʾҴٸ�
	if (false == bDefResInit)
	{
		MeshInit();
		ShaderInit();

		// �����Ͷ����� �������� �̷���. 
		// ���� �ؼ�����
// -0.5 +0.5	+0.5 +0.5
		// ����
		// ����
		// ����
// -0.5 -0.5	+0.5 -0.5

		BlendInit();
		RasterizerInit();
		DepthStencilInit();
		SamplerInit();
		MaterialInit();
		// ����Ÿ��... > �޽�, ���׸���, ���÷� ����
		GameRenderTarget::Init();
		GameDebugPlus::DebugInit(false);
		bDefResInit = true;
	}
}

void GameDevice::CreateViewPort()
{
	m_VIEWPORT = { 0, }; // �ʱ�ȭ 
	// ������ ��ǥ�� ����̴�. (0,0) ���� �簢�� (�����������X,Y) ���� ���̴� 0 < Z < 1
	m_VIEWPORT.TopLeftX = 0.0f;
	m_VIEWPORT.TopLeftY = 0.0f;
	m_VIEWPORT.Width = m_Win->Size().X;
	m_VIEWPORT.Height = m_Win->Size().Y;
	m_VIEWPORT.MinDepth = 0.0f;
	m_VIEWPORT.MaxDepth = 1.0f;
}


void GameDevice::CreateSwapChain()
{
	// �Ѱ��� ��������ü�� �����Ѵ�. 
	// ����̽� ���� �ڵ尡 ��� �� ���� ������� ����ȴ�. 
	DXGI_SWAP_CHAIN_DESC SCDESC = { 0, };	// = { 0, }; �ʱ�ȭ   
	SCDESC.BufferDesc.Width = m_Win->Size().UIX();
	SCDESC.BufferDesc.Height = m_Win->Size().UIY();
	SCDESC.BufferDesc.RefreshRate.Numerator = 60;
	SCDESC.BufferDesc.RefreshRate.Denominator = 1;
	SCDESC.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SCDESC.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SCDESC.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SCDESC.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // BufferUsage == �뵵 
	SCDESC.SampleDesc.Quality = 0;
	SCDESC.SampleDesc.Count = 1;
	SCDESC.OutputWindow = m_Win->WINHWND(); // ���� ����ϴ� �������� �ڵ� 
	SCDESC.BufferCount = 2;
	SCDESC.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	//SCDESC.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
	SCDESC.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	SCDESC.Windowed = true;	// ��üȭ��Ȱ�뿩�� 

	IDXGIDevice* pD = nullptr;
	IDXGIAdapter* pA = nullptr;
	IDXGIFactory* pF = nullptr;

	// �����찡 �����ϴ� ���� API�Դϴ�. 
	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pD);
	if (nullptr == pD)
	{
		MSG_ASSERT_CODE(L"if (nullptr == pD)");
	}

	pD->GetParent(__uuidof(IDXGIAdapter), (void**)&pA);
	if (nullptr == pA)
	{
		MSG_ASSERT_CODE(L"if (nullptr == pA)");
	}

	pA->GetParent(__uuidof(IDXGIFactory), (void**)&pF);
	if (nullptr == pF)
	{
		MSG_ASSERT_CODE(L"if (nullptr == pF)");
	}

	if (S_OK != pF->CreateSwapChain(m_pDevice, &SCDESC, &m_pSwapChain))
	{
		MSG_ASSERT_CODE(L"����ü�� ������ �����߽��ϴ�.");
	}

	pF->Release();
	pA->Release();
	pD->Release();

}

void GameDevice::CreateDepthStencil()
{
	if (S_OK != m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_BackBufferTex))
	{
		MSG_ASSERT_CODE(L"����ü�ο� �ؽ�ó�� �������� �ʽ��ϴ�.");
	}

	if (S_OK != m_pDevice->CreateRenderTargetView(m_BackBufferTex, 0, &m_RTV))
	{
		MSG_ASSERT_CODE(L"����� �̿����(RTV)�� ������ ���߽��ϴ�.");
	}

	// ���� 
	// ������ �ɹ������� ��� public�϶��� �ȴ�.
	// �׸��� �ƹ��� �����ڵ� ����� �Ѵ�.
	D3D11_TEXTURE2D_DESC TD = { 0, };

	TD.ArraySize = 1;

	TD.Width = m_Win->Size().UIX();
	TD.Height = m_Win->Size().UIY();

	TD.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;// 45

	TD.SampleDesc.Count = 1;
	TD.SampleDesc.Quality = 0;
	TD.MipLevels = 1;

	// ������ �׷��� ī�忡 
	TD.Usage = D3D11_USAGE_DEFAULT;

	TD.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	// 1. ����� ���� �޸��� ���� 
	// 2. �װ��� ���� ���� ���� 
	m_pDevice->CreateTexture2D(&TD, 0, &m_DepthStencilTex);

	if (nullptr == m_DepthStencilTex)
	{
		MSG_ASSERT_CODE(L"���� ���� �ؽ�ó�� ������ ���߽��ϴ�.");
	}

	m_pDevice->CreateDepthStencilView(m_DepthStencilTex, 0, &m_DSV);

	if (nullptr == m_DSV)
	{
		MSG_ASSERT_CODE(L"���� ���� ������(DSV)�� ������ ���߽��ϴ�.");
	}

}

void GameDevice::RenderStart()
{
	m_BackBufferRenderTarget->Clear(true);
	m_BackBufferRenderTarget->Setting();

	//ID3D11RasterizerState
	//m_pContext->RSSetState()

	// ������ ũ�⸸�� ȭ�鿡 ������ ����ϰڴ�.
	/////////////////m_pContext->RSSetViewports(1, &m_VIEWPORT);
	// �׸������� ȭ���� �ѹ� �Ķ������� �����.
	/////////////////m_pContext->ClearRenderTargetView(m_RTV, m_Color.Arr);
	// ���̿� ���ٽ��� �ʱ�ȭ�Ѵ�.
	// 0.0 < 0.5 < 0.6 < 1.0  �ִ� 1, �ּ� 0


	// TD.FORMAT
	// int : 4byte 
	// 32bit 
	///////////////////m_pContext->ClearDepthStencilView(m_DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0); // ���� : float ���ٽ� : uint �̷��� �ϳ� 
	// �����/�����/�����/�����/

	// 1	1	1	1
	// 1	0.6	0.6	1
	// 1	0.6	0.6	1
	// 1	1	1	1

	// DX ���������������� ���������� 
	// �ѹ��� ���� 
	// �ڵ� ���� 16����Ʈ�� ó���Ǵ� ��� 
	// �ϵ���� �ٺ��� ���迡 ���� CPU, GPU 2^������ ó���� ����ȭ 

	// 3����Ʈ�� FLOAT
	// 8����Ʈ�� UINT 

	// COLOR : 2�����迭 16BYTE
	// DEPTH : 2�����迭 16BYTE

	// �ű� ���� �׸��ڴ�.
	// ���� ���� �׸� ��ȭ���� �����.
	///////////////////m_pContext->OMSetRenderTargets(1, &m_RTV, m_DSV);

	// ������������������ ������ ������ �ѹ��� �̷������. 
	// DRAW�� ȣ���ϸ� �ѹ��� ����ȴ�. 

}

void GameDevice::RenderEnd()
{
	m_pSwapChain->Present(0, 0);
}


// ������ ����.. �� �ѹ��� ���̴��� ����.  
void GameDevice::Reset()
{
	GameDevice::MainObj()->Context()->PSSetShader(nullptr, 0, 0);
	GameDevice::MainObj()->Context()->GSSetShader(nullptr, 0, 0);
	GameDevice::MainObj()->Context()->HSSetShader(nullptr, 0, 0);
	GameDevice::MainObj()->Context()->DSSetShader(nullptr, 0, 0);
	GameDevice::MainObj()->Context()->VSSetShader(nullptr, 0, 0);
}

// 1. ����Ÿ���� ����� .
// 2. ����̽����� ����Ÿ�� �ؽ�ó���� �����Ѵ�. �ڷᱸ����    
// 3. ���������� �ؽ��� ������ �ϳ��� �����Ѵ�. 

//////////////////////////////////////////////////////////////////////////////////////////
void GameDevice::CreateBackBufferTarget()
{
	ID3D11Texture2D* m_BackBufferTex;

	if (S_OK != m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_BackBufferTex))
	{
		MSG_ASSERT_CODE(L"����ü�ο� �ؽ�ó�� �������� �ʽ��ϴ�.");
	}

	m_BackBufferRenderTarget = new GameRenderTarget();
	m_BackBufferRenderTarget->CreateTarget(m_BackBufferTex, CVector::BLUE, true);
	m_BackBufferRenderTarget->CreateDepth(0);

	m_UserDataTarget = new GameRenderTarget();
	m_UserDataTarget->CreateTarget(m_BackBufferRenderTarget->Texture(0)->Size(), CVector::ZERO);
	m_UserDataTarget->CreateTarget(m_BackBufferRenderTarget->Texture(0)->Size(), CVector::ZERO);
	m_UserDataTarget->CreateTarget(m_BackBufferRenderTarget->Texture(0)->Size(), CVector::ZERO);
	m_UserDataTarget->CreateTarget(m_BackBufferRenderTarget->Texture(0)->Size(), CVector::ZERO);
	m_UserDataTarget->CreateTarget(m_BackBufferRenderTarget->Texture(0)->Size(), CVector::ZERO);
	m_UserDataTarget->CreateTarget(m_BackBufferRenderTarget->Texture(0)->Size(), CVector::ZERO);
	m_UserDataTarget->CreateTarget(m_BackBufferRenderTarget->Texture(0)->Size(), CVector::ZERO);
	m_UserDataTarget->CreateTarget(m_BackBufferRenderTarget->Texture(0)->Size(), CVector::ZERO);

}

CPtr<GameRenderTarget> GameDevice::BackBufferRenderTarget()
{
	return m_BackBufferRenderTarget;
}

CPtr<GameRenderTarget> GameDevice::DataRenderTarget()
{
	return m_UserDataTarget;
}
