#include "GameDevice.h"
#include <GameIO.h>
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "GameDepthstencil.h"
#include "Vtx.h"


#pragma region z Ȱ�� ��Ŀ���� 
/*
	if (���� �׸� ������Ʈ z > ���� �׷����� ������Ʈ z) <---- LESS_EQUAL
	{
		�׸���.
	}
	else
	{
		�׸��� �ʴ´�.
	}

	LESS_EQUAL
	0.5 < 0.6
*/
#pragma endregion

#pragma warning( push )
#pragma warning( disable : 26444 )

void GameDevice::DepthStencilInit()
{
	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		Desc.DepthEnable = true;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.StencilEnable = false;
		GameDepthstencil::Create(L"EqualDepth", Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		Desc.DepthEnable = true;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.StencilEnable = false;
		GameDepthstencil::Create(L"DefaultDepth", Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		Desc.DepthEnable = true;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		Desc.StencilEnable = false;
		GameDepthstencil::Create(L"ZeroDepth", Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		Desc.DepthEnable = true;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.StencilEnable = false;
		GameDepthstencil::Create(L"AlwaysDepth", Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		Desc.DepthEnable = true;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		Desc.StencilEnable = false;
		GameDepthstencil::Create(L"AlwaysZeroDepth", Desc);
	}

}

#pragma warning( pop )