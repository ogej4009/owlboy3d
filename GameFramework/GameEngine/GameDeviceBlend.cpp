#include "GameDevice.h"
#include <GameIO.h>
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "GameBlend.h"
#include "Vtx.h"


#pragma warning( push )
#pragma warning( disable : 26444 )


#pragma region 블랜드-메커니즘
/*
	CVector	Src;
	CVector	SrcFactor;
	CVector	Dest;
	CVector	DestFactor;
	CVector	Color = { (Src.X * SrcFactor.X) + (Dest.X * DestFactor.X), };

	이미 찍힌 색 : Dest
	찍을 색 : Src
*/
#pragma endregion

void GameDevice::BlendInit()
{
	{
		D3D11_BLEND_DESC Desc = { 0, };

#pragma region 블랜드의진실
		/*
			Desc.AlphaToCoverageEnable = FALSE;
			알파값을 계산해서 깊이 버퍼를 사용할 것인가?
			TRUE는 자동으로 한다는 것인데, 깊이값을 유저들은 인지해야함으로 FALSE로 한다.
			내가 무언가를 그리면 깊이값과 알파값이 동시에 있는 것이다.
			알파값이 0이어서 투명이라 하더라도 안그려진 것이 아니라 그려진 것이고 깊이값이 존재한다.
			먼저 그려진 것에 나중에 그리려고 하면 가끔 안그려지는 경우가 있다.
			이 케이스는 이전 연산으로 인한 깊이테스트를 간과하는 경우이다.
		*/
#pragma endregion
		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE;

#pragma region RenderTarget[0]
		/*
			0번에 있는 설정으로만 블랜드 해라.
			SV_Target
			0번에 있는 설정으로만 0번에 쓸 설정이다.
		*/
#pragma endregion
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

#pragma region 알파계산법-아이솔레이션
		/*
			항상 내 알파를 먼저 고려해라. 그 다음 상대를 계산한다.
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
			혼합계수란 것이있다.		-> 혼합계수는 (0, 0, 0, 0)
			사전혼합작업이란 것이 있다. -> 사전 혼합작업 안한다.
			Dest 알파고려대상			-> ex) Dest1-블루스크린, Dest2-??????
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