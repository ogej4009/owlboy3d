#include "GameDevice.h"
#include "GameDebugPlus.h"
#include "GameRenderTarget.h"
bool GameDevice::bDefResInit = false;

GameDevice::GameDevice()
	: m_MC(0)
	, m_MQ(0)
	, m_Color(CVector::BLUE) // 파란화면
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
		MSG_ASSERT_CODE(L"존재하지 않는 윈도우에 디바이스를 장착시키려고 만드려고 했습니다");
	}

	m_Win = _Window;

	int iFlag = 0;

	// 속성-C++-전처리기-구성관리자-매크로
	// #define	_DEBUG
	// 이것을 체크 해야 #ifdef _DEBUG ~ #endif 를 할 수 있다. 
	// DEBUG x64일 때만 디바이스 옵션 에러를 뱉어낸다. 
#ifdef _DEBUG
	// 디바이스 만드는 모드가 디버그 모드 
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 디바이스 레벨
	D3D_FEATURE_LEVEL eLV = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	if (S_OK != D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		iFlag,
		nullptr, // 가능한 최대버전 알아내는 것
		0,
		D3D11_SDK_VERSION, // 현재 윈도우에 설치된 SDK 버전
		&m_pDevice,
		&eLV,
		&m_pContext))
	{
		MSG_ASSERT_CODE(L"디바이스와 컨텍스트 생성에 실패했습니다.");
	}



	m_MC = 4;
	if (S_OK != m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R32G32B32A32_UINT, m_MC, &m_MQ))
	{
		m_MC = 1;
		if (S_OK != m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UINT, m_MC, &m_MQ))
		{
			MSG_ASSERT_CODE(L"멀티샘플링 체크가 제대로 되지 않았습니다.");
		}
	}

	CreateSwapChain();
	//CreateDepthStencil();
	//CreateViewPort();

	////////////////////////////////////////////// 추가 
	CreateBackBufferTarget();


	// 하나의 디바이스도 만들어지지 않았다면
	if (false == bDefResInit)
	{
		MeshInit();
		ShaderInit();

		// 레스터라이저 가기전에 이렇다. 
		// 대충 해석하자
// -0.5 +0.5	+0.5 +0.5
		// □□□
		// □□□
		// □□□
// -0.5 -0.5	+0.5 -0.5

		BlendInit();
		RasterizerInit();
		DepthStencilInit();
		SamplerInit();
		MaterialInit();
		// 랜더타겟... > 메쉬, 머테리얼, 샘플러 세팅
		GameRenderTarget::Init();
		GameDebugPlus::DebugInit(false);
		bDefResInit = true;
	}
}

void GameDevice::CreateViewPort()
{
	m_VIEWPORT = { 0, }; // 초기화 
	// 윈도우 좌표계 기반이다. (0,0) 부터 사각형 (윈도우사이즈X,Y) 까지 깊이는 0 < Z < 1
	m_VIEWPORT.TopLeftX = 0.0f;
	m_VIEWPORT.TopLeftY = 0.0f;
	m_VIEWPORT.Width = m_Win->Size().X;
	m_VIEWPORT.Height = m_Win->Size().Y;
	m_VIEWPORT.MinDepth = 0.0f;
	m_VIEWPORT.MaxDepth = 1.0f;
}


void GameDevice::CreateSwapChain()
{
	// 넘겨줄 정보구조체를 구성한다. 
	// 디바이스 내의 코드가 모두 이 같은 방식으로 진행된다. 
	DXGI_SWAP_CHAIN_DESC SCDESC = { 0, };	// = { 0, }; 초기화   
	SCDESC.BufferDesc.Width = m_Win->Size().UIX();
	SCDESC.BufferDesc.Height = m_Win->Size().UIY();
	SCDESC.BufferDesc.RefreshRate.Numerator = 60;
	SCDESC.BufferDesc.RefreshRate.Denominator = 1;
	SCDESC.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SCDESC.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SCDESC.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SCDESC.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // BufferUsage == 용도 
	SCDESC.SampleDesc.Quality = 0;
	SCDESC.SampleDesc.Count = 1;
	SCDESC.OutputWindow = m_Win->WINHWND(); // 내가 출력하는 윈도우의 핸들 
	SCDESC.BufferCount = 2;
	SCDESC.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	//SCDESC.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
	SCDESC.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	SCDESC.Windowed = true;	// 전체화면활용여부 

	IDXGIDevice* pD = nullptr;
	IDXGIAdapter* pA = nullptr;
	IDXGIFactory* pF = nullptr;

	// 윈도우가 제공하는 말단 API입니다. 
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
		MSG_ASSERT_CODE(L"스왑체인 생성에 실패했습니다.");
	}

	pF->Release();
	pA->Release();
	pD->Release();

}

void GameDevice::CreateDepthStencil()
{
	if (S_OK != m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_BackBufferTex))
	{
		MSG_ASSERT_CODE(L"스왑체인에 텍스처가 존재하지 않습니다.");
	}

	if (S_OK != m_pDevice->CreateRenderTargetView(m_BackBufferTex, 0, &m_RTV))
	{
		MSG_ASSERT_CODE(L"백버퍼 이용권한(RTV)을 얻어오지 못했습니다.");
	}

	// 깊이 
	// 내부의 맴버변수가 모두 public일때만 된다.
	// 그리고 아무런 생성자도 없어야 한다.
	D3D11_TEXTURE2D_DESC TD = { 0, };

	TD.ArraySize = 1;

	TD.Width = m_Win->Size().UIX();
	TD.Height = m_Win->Size().UIY();

	TD.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;// 45

	TD.SampleDesc.Count = 1;
	TD.SampleDesc.Quality = 0;
	TD.MipLevels = 1;

	// 무조건 그래픽 카드에 
	TD.Usage = D3D11_USAGE_DEFAULT;

	TD.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	// 1. 만들기 위한 메모리적 권한 
	// 2. 그것을 쓰기 위한 권한 
	m_pDevice->CreateTexture2D(&TD, 0, &m_DepthStencilTex);

	if (nullptr == m_DepthStencilTex)
	{
		MSG_ASSERT_CODE(L"깊이 버퍼 텍스처를 만들지 못했습니다.");
	}

	m_pDevice->CreateDepthStencilView(m_DepthStencilTex, 0, &m_DSV);

	if (nullptr == m_DSV)
	{
		MSG_ASSERT_CODE(L"깊이 버퍼 사용권한(DSV)을 만들지 못했습니다.");
	}

}

void GameDevice::RenderStart()
{
	m_BackBufferRenderTarget->Clear(true);
	m_BackBufferRenderTarget->Setting();

	//ID3D11RasterizerState
	//m_pContext->RSSetState()

	// 윈도우 크기만한 화면에 뭔가를 출력하겠다.
	/////////////////m_pContext->RSSetViewports(1, &m_VIEWPORT);
	// 그리기전에 화면을 한번 파란색으로 지운다.
	/////////////////m_pContext->ClearRenderTargetView(m_RTV, m_Color.Arr);
	// 깊이와 스텐실을 초기화한다.
	// 0.0 < 0.5 < 0.6 < 1.0  최대 1, 최소 0


	// TD.FORMAT
	// int : 4byte 
	// 32bit 
	///////////////////m_pContext->ClearDepthStencilView(m_DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0); // 뎁스 : float 스텐실 : uint 이렇게 하나 
	// □□□□/□□□□/□□□□/□□□□/

	// 1	1	1	1
	// 1	0.6	0.6	1
	// 1	0.6	0.6	1
	// 1	1	1	1

	// DX 랜더링파이프라인 슬롯형개념 
	// 한번만 세팅 
	// 코드 전부 16바이트로 처리되는 방식 
	// 하드웨어 근본의 설계에 의해 CPU, GPU 2^단위의 처리에 최적화 

	// 3바이트의 FLOAT
	// 8바이트의 UINT 

	// COLOR : 2차원배열 16BYTE
	// DEPTH : 2차원배열 16BYTE

	// 거기 위에 그리겠다.
	// 지금 부터 그릴 도화지는 여기야.
	///////////////////m_pContext->OMSetRenderTargets(1, &m_RTV, m_DSV);

	// 랜더링파이프라인의 실행은 세팅후 한번에 이루어진다. 
	// DRAW를 호출하면 한번에 실행된다. 

}

void GameDevice::RenderEnd()
{
	m_pSwapChain->Present(0, 0);
}


// 지금은 단지.. 단 한번의 쉐이더를 쓴다.  
void GameDevice::Reset()
{
	GameDevice::MainObj()->Context()->PSSetShader(nullptr, 0, 0);
	GameDevice::MainObj()->Context()->GSSetShader(nullptr, 0, 0);
	GameDevice::MainObj()->Context()->HSSetShader(nullptr, 0, 0);
	GameDevice::MainObj()->Context()->DSSetShader(nullptr, 0, 0);
	GameDevice::MainObj()->Context()->VSSetShader(nullptr, 0, 0);
}

// 1. 렌더타겟을 만든다 .
// 2. 디바이스에서 렌더타겟 텍스처쪽을 점검한다. 자료구조로    
// 3. 렌더러에서 텍스쳐 관련을 하나로 통일한다. 

//////////////////////////////////////////////////////////////////////////////////////////
void GameDevice::CreateBackBufferTarget()
{
	ID3D11Texture2D* m_BackBufferTex;

	if (S_OK != m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_BackBufferTex))
	{
		MSG_ASSERT_CODE(L"스왑체인에 텍스처가 존재하지 않습니다.");
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
