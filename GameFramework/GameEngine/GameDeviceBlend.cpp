#include "GameDevice.h"
#include <GameIO.h>
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "GameBlend.h"
#include "Vtx.h"


#pragma warning( push )
#pragma warning( disable : 26444 )


#pragma region ����-��Ŀ����
/*
	CVector	Src;
	CVector	SrcFactor;
	CVector	Dest;
	CVector	DestFactor;
	CVector	Color = { (Src.X * SrcFactor.X) + (Dest.X * DestFactor.X), };

	�̹� ���� �� : Dest
	���� �� : Src
*/
#pragma endregion

void GameDevice::BlendInit()
{
	{
		D3D11_BLEND_DESC Desc = { 0, };

#pragma region ����������
		/*
			Desc.AlphaToCoverageEnable = FALSE;
			���İ��� ����ؼ� ���� ���۸� ����� ���ΰ�?
			TRUE�� �ڵ����� �Ѵٴ� ���ε�, ���̰��� �������� �����ؾ������� FALSE�� �Ѵ�.
			���� ���𰡸� �׸��� ���̰��� ���İ��� ���ÿ� �ִ� ���̴�.
			���İ��� 0�̾ �����̶� �ϴ��� �ȱ׷��� ���� �ƴ϶� �׷��� ���̰� ���̰��� �����Ѵ�.
			���� �׷��� �Ϳ� ���߿� �׸����� �ϸ� ���� �ȱ׷����� ��찡 �ִ�.
			�� ���̽��� ���� �������� ���� �����׽�Ʈ�� �����ϴ� ����̴�.
		*/
#pragma endregion
		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE;

#pragma region RenderTarget[0]
		/*
			0���� �ִ� �������θ� ���� �ض�.
			SV_Target
			0���� �ִ� �������θ� 0���� �� �����̴�.
		*/
#pragma endregion
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

#pragma region ���İ���-���ַ̼��̼�
		/*
			�׻� �� ���ĸ� ���� ����ض�. �� ���� ��븦 ����Ѵ�.
		*/
#pragma endregion

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;

#pragma region D3D11_BLEND::
		/*
			D3D11_BLEND_ZERO, D3D11_BLEND_ONE, D3D11_BLEND_OP_ADD
			ȥ�հ���� �����ִ�.		-> ȥ�հ���� (0, 0, 0, 0)
			����ȥ���۾��̶� ���� �ִ�. -> ���� ȥ���۾� ���Ѵ�.
			Dest ���İ�����			-> ex) Dest1-��罺ũ��, Dest2-??????
		*/
#pragma endregion

		GameBlend::Create(L"AlphaBlend", Desc);
	}


	{
		D3D11_BLEND_DESC Desc = { 0, };
		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE; 
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;	
		GameBlend::Create(L"OneBlend", Desc);
	}

	{
		D3D11_BLEND_DESC Desc = { 0, };
		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = TRUE;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[1].BlendEnable = true;
		Desc.RenderTarget[1].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[1].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[1].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[1].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		Desc.RenderTarget[1].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[1].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[1].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
		Desc.RenderTarget[2].BlendEnable = true;
		Desc.RenderTarget[2].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[2].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[2].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[2].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		Desc.RenderTarget[2].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[2].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[2].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
		Desc.RenderTarget[3].BlendEnable = true;
		Desc.RenderTarget[3].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[3].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[3].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[3].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		Desc.RenderTarget[3].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[3].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[3].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
		GameBlend::Create(L"AlphaBlendDeferred", Desc);
	}




	{
		D3D11_BLEND_DESC Desc = { 0, };
		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ZERO;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
		GameBlend::Create(L"ShadowBlend", Desc);
	}








}
#pragma warning( pop )