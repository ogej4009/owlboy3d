#pragma once
#include <GameMath.h>
#include <GameDebug.h>
#include <CPtr.h>
#include <GameObjTFuncMgr.h>
#include <GameWin.h>

#pragma comment(lib, "GameBase.lib")

#pragma region ����̽� 
/*
	���α׷��� �����쿡 ������ ����ϴ� ��Ŀ���򿡼�,
	�׷���ī���� �޸𸮸� ���������� ������ �� �ִ� ������ ��� ���� �ܰ�
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

#pragma region �׷���ī�� 
	/*
		����̽� : �׷���ī���� �޸� -> �޸� ����,�Ҵ�, �ε�
		���ؽ�Ʈ : �׷���ī���� ���� -> ������
	*/
#pragma endregion
public:
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pContext;


#pragma region �������̽� 
	/*
		<< ������ �ִ� ���� ���� >>
		����ü�� : ���̷�Ʈ�� ȭ�� ����� ��Ŀ����(Clear, Print)
		���۹� : ������ ���� ���� ȭ���� ����ϱ� ���� �� �ϳ��� ���(2�����迭==�ؽ���)
				 ���� Ÿ���� ���� ��������, ���������� ����̽��� �Ѱ��ֱ� ���� (������ ����) �ؽ��Ĵ� �ϳ���.
		�������ٽ� : ���̰�(z)�� ��� �ִ�.
	*/
#pragma endregion

public:
	IDXGISwapChain* m_pSwapChain;
	ID3D11Texture2D* m_BackBufferTex;
	ID3D11Texture2D* m_DepthStencilTex;

#pragma region �ؽ��� 
	/*
		�ؽ��Ĵ� �޸��� �������� 2���� �迭
		�����̶� ��Ʈ�� ����. �޸𸮴� �������� ���.
		���α׷��� ������ : �޸� vs ����
		��¥�� ���� ����� ó���ؾ� �Ѵ�. �޸��� �������� ����.

		1. ��� �ִ� �޸𸮿� ���� ����
			: �׸��� �޸��� �������� �̿��ϴ� �������̽��� ID3D11Texture2D*;
		2. �޸� ���ó�� ���� ����
			: �׸��� �׸��ų� Ư���� ������� �̿��ϰ� �ϴ� �������̽��� ID3D11RenderTargetView*;
			  � ���ҽ��� ���� ��, �޸��� ����Ҹ� ��ǥ�ϴ� �������̽�(��ü Ȥ�� �Լ�)�� ID3D11RenderTargetView;
	*/
#pragma endregion

#pragma region ��
	/*
		����(Z��) �ϳ��� �̿��ؼ� Case�� ���� ������ �ο��Ѵ�.
		m_DSV : Z���� ���� ���� ��� �������̽�
		���� �� (������ float��)
		���ٽ� �� (������ int��)
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

#pragma region �ȼ����̴� ��Ŀ����
	/*
		������ ȭ�� ũ�� 1280 X 720

		FOR�� ���鼭 �׸���.
		�ݺ��ϸ鼭 ������ �Ѵ�.
		�������̴��� ���� ������ŭ.
		�ȼ����̴��� �ȼ��� ������ŭ.

		RASTERIZER	- Pixel with Interpolated data ->	Pixel shader
		�����Ͷ�����	�ȼ� 		����	������		�ȼ����̴�

		-> pixel color and depth -> Output Merger(stencil test (run before pixel shader) )
			�ȼ� �÷� �� ����		���(�ȼ����̴� ���� ó���ȴ�.)
	*/
#pragma endregion

public:
	static void Reset();

private:
	void Init(const CPtr<GameWin>& _Window);

};