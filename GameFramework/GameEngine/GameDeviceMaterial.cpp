#include "GameDevice.h"
#include "GameMaterial.h"
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "GameBlend.h"
#include "GameRasterizer.h"
#include "GameDepthstencil.h"

void GameDevice::MaterialInit()
{
	//////////////////////////////////////////////// 추가했습니다 .
	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"DebugMesh");
		Material->SetVtxShader(L"VS_DebugMesh");
		Material->SetPixShader(L"PS_DebugMesh");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"AlphaBlend");
	}
	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"TargetDebugBack");
		Material->SetVtxShader(L"VS_TargetDebugBack");
		Material->SetPixShader(L"PS_TargetDebugBack");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"AlphaBlend");
	}
	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"TargetDebug");
		Material->SetVtxShader(L"VS_TargetDebug");
		Material->SetPixShader(L"PS_TargetDebug");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"AlphaBlend");
	}
	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"DeferredMerge");
		Material->SetVtxShader(L"VS_DeferredMerge");
		Material->SetPixShader(L"PS_DeferredMerge");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"DeferredLight");
		Material->SetVtxShader(L"VS_DeferredLight");
		Material->SetPixShader(L"PS_DeferredLight");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"OneBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Deferred");
		Material->SetVtxShader(L"VS_Deferred");
		Material->SetPixShader(L"PS_Deferred");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Dash");
		Material->SetVtxShader(L"VS_Dash");
		Material->SetPixShader(L"PS_Dash");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"DeferredStatic");
		Material->SetVtxShader(L"VS_DeferredStatic");
		Material->SetPixShader(L"PS_DeferredStatic");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Forward");
		Material->SetVtxShader(L"VS_Forward");
		Material->SetPixShader(L"PS_Forward");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Grid");
		Material->SetVtxShader(L"VS_Grid");
		Material->SetPixShader(L"PS_Grid");
		Material->SetRasterizer(L"None");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Sprite2D"); // Frame L"Default"
		Material->SetVtxShader(L"VS_Sprite2D");
		Material->SetPixShader(L"PS_Sprite2D");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth"); // Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"UI");
		Material->SetVtxShader(L"VS_UI");
		Material->SetPixShader(L"PS_UI");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Fire");
		Material->SetVtxShader(L"VS_Fire");
		Material->SetPixShader(L"PS_Fire");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Particle");
		Material->SetVtxShader(L"VS_Particle");
		Material->SetGeoShader(L"GS_Particle");
		Material->SetPixShader(L"PS_Particle");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

#pragma region SKY_BOX 
	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"DeferredFront");
		Material->SetVtxShader(L"VS_DeferredFront");
		Material->SetPixShader(L"PS_DeferredFront");
		Material->SetRasterizer(L"Front");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}



	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"TileMap");
		Material->SetVtxShader(L"VS_TileMap");
		Material->SetPixShader(L"PS_TileMap");
		Material->SetRasterizer(L"None");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Default");
		Material->SetVtxShader(L"VS_Default");
		Material->SetPixShader(L"PS_Default");
		//Material->SetRasterizer(L"Back");
		Material->SetRasterizer(L"None");
		//Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"ExGradien"); //ExGradien
		Material->SetVtxShader(L"VS_ExGradien");
		Material->SetPixShader(L"PS_ExGradien");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"YLight");
		Material->SetVtxShader(L"VS_YLight");
		Material->SetPixShader(L"PS_YLight");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Vertical");
		Material->SetVtxShader(L"VS_Vertical");
		Material->SetPixShader(L"PS_Vertical");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Horizon");
		Material->SetVtxShader(L"VS_Horizon");
		Material->SetPixShader(L"PS_Horizon");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Distortion");
		Material->SetVtxShader(L"VS_Distortion");
		Material->SetPixShader(L"PS_Distortion");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"GhostBurn");
		Material->SetVtxShader(L"VS_GhostBurn");
		Material->SetPixShader(L"PS_GhostBurn");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"TargetMergePlus"); 
		Material->SetVtxShader(L"VS_TargetMerge");
		Material->SetPixShader(L"PS_TargetMerge");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"OneBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"TargetMerge");
		Material->SetVtxShader(L"VS_TargetMerge");
		Material->SetPixShader(L"PS_TargetMerge");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"AlphaBlend");
	}
	
	//////////////////////////////////////////////////////////////////////////////////






}
