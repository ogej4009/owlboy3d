#include "GameDevice.h"
#include <GameIO.h>
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "Vtx.h"

#pragma  warning( push )
#pragma  warning( disable : 26444 )

void GameDevice::ShaderInit()
{
	GameDirectory m_Dir;
	m_Dir.MoveParent(L"GameFramework");
	m_Dir.Move(L"GameShader");
	
	std::list<GameFile> File = m_Dir.DirAllFile(L"hlsl");

	for (auto& _Value : File)
	{
		GameShader::AutoShaderCompile(_Value.FullPath());
	}

	//{
	//	CPtr<GameVtxShader> VTX = GameVtxShader::Load(m_Dir.CombineFileName(L"Default.hlsl"), L"VS_2D_DEFAULT");
	//	VTX->AddLayout("SHA_INIT_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->CreateLayout();
	//	GamePixShader::Load(m_Dir.CombineFileName(L"Default.hlsl"), L"PS_2D_DEFAULT");
	//}

	//{
	//	CPtr<GameVtxShader> VTX = GameVtxShader::Load(m_Dir.CombineFileName(L"ExplosionGradien.hlsl"), L"VS_2D_EX_GRADIEN");
	//	VTX->AddLayout("SHA_INIT_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->CreateLayout();
	//	//GamePixShader::Load(m_Dir.CombineFileName(L"ExplosionGradien.hlsl"), L"PS_2D_EX_GRADIEN");
	//}

	//{
	//	CPtr<GameVtxShader> VTX = GameVtxShader::Load(m_Dir.CombineFileName(L"Light.hlsl"), L"VS_2D_LIGHT");
	//	VTX->AddLayout("SHA_INIT_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->CreateLayout();
	//	//GamePixShader::Load(m_Dir.CombineFileName(L"Light.hlsl"), L"PS_2D_LIGHT");
	//}

	//{
	//	CPtr<GameVtxShader> VTX = GameVtxShader::Load(m_Dir.CombineFileName(L"Vertical.hlsl"), L"VS_2D_VERTICAL");
	//	VTX->AddLayout("SHA_INIT_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->CreateLayout();
	//	//GamePixShader::Load(m_Dir.CombineFileName(L"Vertical.hlsl"), L"PS_2D_VERTICAL");
	//}

	//{
	//	CPtr<GameVtxShader> VTX = GameVtxShader::Load(m_Dir.CombineFileName(L"Horizon.hlsl"), L"VS_2D_HORIZON");
	//	VTX->AddLayout("SHA_INIT_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->CreateLayout();
	//	//GamePixShader::Load(m_Dir.CombineFileName(L"Horizon.hlsl"), L"PS_2D_HORIZON");
	//}

	//{
	//	CPtr<GameVtxShader> VTX = GameVtxShader::Load(m_Dir.CombineFileName(L"Distortion.hlsl"), L"VS_2D_DISTORTION");
	//	VTX->AddLayout("SHA_INIT_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->CreateLayout();
	//	//GamePixShader::Load(m_Dir.CombineFileName(L"Distortion.hlsl"), L"PS_2D_DISTORTION");
	//}

	//{
	//	CPtr<GameVtxShader> VTX = GameVtxShader::Load(m_Dir.CombineFileName(L"Ghostburn.hlsl"), L"VS_2D_GHOSTBURN");
	//	VTX->AddLayout("SHA_INIT_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->CreateLayout();
	//	//GamePixShader::Load(m_Dir.CombineFileName(L"Ghostburn.hlsl"), L"PS_2D_GHOSTBURN");
	//}

	//{
	//	CPtr<GameVtxShader> VTX = GameVtxShader::Load(m_Dir.CombineFileName(L"TileMap.hlsl"), L"VS_2D_TILEMAP");
	//	VTX->AddLayout("SHA_INIT_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("SHA_INIT_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->CreateLayout();
	//	//GamePixShader::Load(m_Dir.CombineFileName(L"TileMap.hlsl"), L"PS_2D_TILEMAP");
	//}

}
#pragma warning( pop )