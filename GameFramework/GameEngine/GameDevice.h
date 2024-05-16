#pragma once
#include <GameMath.h>
#include <GameDebug.h>
#include <CPtr.h>
#include <GameObjTFuncMgr.h>
#include <GameWin.h>

#pragma comment(lib, "GameBase.lib")

#pragma region 디바이스 
/*
	프로그램이 윈도우에 내용을 출력하는 메커니즘에서,
	그래픽카드의 메모리를 간접적으로 접근할 수 있는 권한을 얻기 위한 단계
*/
#pragma endregion

class GameRenderTarget;
class GameDevice : public GameFirstObjMgr<GameDevice>
{
public:
	static bool bDefResInit;

public:
	static CPtr<GameDevice> Create(const GameString& _Win)
	{
		CPtr<GameDevice> DEVICE = CreateAndInsert(_Win);
		DEVICE->Init(GameWin::Find(_Win));
		return DEVICE;
	}

public:
	CPtr<GameWin> m_Win;

public:
	UINT m_MC;
	UINT m_MQ;
	CVector m_Color;

#pragma region 그래픽카드 
	/*
		디바이스 : 그래픽카드의 메모리 -> 메모리 조작,할당, 로딩
		컨텍스트 : 그래픽카드의 연산 -> 랜더링
	*/
#pragma endregion
public:
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pContext;


#pragma region 인터페이스 
	/*
		<< 이유가 있는 선언 순서 >>
		스왑체인 : 다이렉트한 화면 출력의 메커니즘(Clear, Print)
		백퍼버 : 유저가 보는 최종 화면을 출력하기 위한 단 하나의 통로(2차원배열==텍스쳐)
				 랜더 타겟은 여러 개이지만, 최종적으로 디바이스에 넘겨주기 위한 (유저가 보는) 텍스쳐는 하나다.
		뎁스스텐실 : 깊이값(z)을 들고 있다.
	*/
#pragma endregion

public:
	IDXGISwapChain* m_pSwapChain;
	ID3D11Texture2D* m_BackBufferTex;
	ID3D11Texture2D* m_DepthStencilTex;

#pragma region 텍스쳐 
	/*
		텍스쳐는 메모리적 관점에서 2차원 배열
		파일이란 비트의 집합. 메모리는 데이터의 덩어리.
		프로그래머 딜레마 : 메모리 vs 연산
		공짜는 없고 비용을 처리해야 한다. 메모리의 관점으로 보자.

		1. 들고 있는 메모리에 대한 관점
			: 그림을 메모리적 관점에서 이용하는 인터페이스는 ID3D11Texture2D*;
		2. 메모리 사용처에 대한 관점
			: 그림을 그리거나 특수한 기능으로 이용하게 하는 인터페이스는 ID3D11RenderTargetView*;
			  어떤 리소스가 있을 때, 메모리의 저장소를 대표하는 인터페이스(객체 혹은 함수)가 ID3D11RenderTargetView;
	*/
#pragma endregion

#pragma region 뷰
	/*
		숫자(Z값) 하나를 이용해서 Case에 따라 조건을 부여한다.
		m_DSV : Z값에 대한 연산 기능 인터페이스
		깊이 값 (본질은 float값)
		스텐실 값 (본질은 int값)
	*/
#pragma endregion

	ID3D11RenderTargetView* m_RTV;
	ID3D11DepthStencilView* m_DSV;
	D3D11_VIEWPORT m_VIEWPORT;

	ID3D11Device* Device()
	{
		return m_pDevice;
	}

	ID3D11DeviceContext* Context()
	{
		return m_pContext;
	}

private:
	CPtr<GameRenderTarget>		m_BackBufferRenderTarget;
	CPtr<GameRenderTarget>		m_UserDataTarget;

public:
	CPtr<GameRenderTarget> BackBufferRenderTarget();
	CPtr<GameRenderTarget> DataRenderTarget();

public:
	GameDevice();
	~GameDevice();

public:
	void CreateSwapChain();
	void CreateDepthStencil();
	void CreateViewPort();

	void CreateBackBufferTarget();

public:
	void RenderStart();
	void RenderEnd();

public:
	void MeshInit();
	void ShaderInit();
	void BlendInit();
	void RasterizerInit();
	void DepthStencilInit();
	void SamplerInit();
	void MaterialInit();

public:
	void SphereMeshInit();

#pragma region 픽셀쉐이더 메커니즘
	/*
		렌더링 화면 크기 1280 X 720

		FOR문 돌면서 그린다.
		반복하면서 연산을 한다.
		정점쉐이더는 점의 갯수만큼.
		픽셀쉐이더는 픽셀의 갯수만큼.

		RASTERIZER	- Pixel with Interpolated data ->	Pixel shader
		레스터라이저	픽셀 		보간	데이터		픽셀쉐이더

		-> pixel color and depth -> Output Merger(stencil test (run before pixel shader) )
			픽셀 컬러 앤 깊이		출력(픽셀쉐이더 전에 처리된다.)
	*/
#pragma endregion

public:
	static void Reset();

private:
	void Init(const CPtr<GameWin>& _Window);

};