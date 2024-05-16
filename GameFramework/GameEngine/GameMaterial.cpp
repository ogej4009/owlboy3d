#include "GameMaterial.h"
#include <GameDebug.h>

GameMaterial::GameMaterial() : m_AllCheck(true)
{
	m_AllShader.resize((int)SHADERTYPE::SHADER_END);
}

GameMaterial::~GameMaterial()
{

}

MATERIAL_TYPE GameMaterial::MType()
{
	return GetPixShader()->MType();
}

void GameMaterial::SetVtxShader(const GameString& _Name)
{
	m_VtxShader = GameVtxShader::Find(_Name);

	if (nullptr == m_VtxShader)
	{
		MSG_ASSERT_CODE(L"존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다." + _Name);
	}

	m_AllShader[(int)SHADERTYPE::SHADER_VS] = m_VtxShader;

}


void GameMaterial::SetPixShader(const GameString& _Name)
{
	m_PixShader = GamePixShader::Find(_Name);

	if (nullptr == m_PixShader)
	{
		MSG_ASSERT_CODE(L"존재하지 않는 픽셀 쉐이더를 세팅하려고 했습니다." + _Name);
	}

	m_AllShader[(int)SHADERTYPE::SHADER_PS] = m_PixShader;
}

void GameMaterial::SetGeoShader(const GameString& _Name)
{
	m_GeoShader = GameGeometryShader::Find(_Name);

	if (nullptr == m_GeoShader)
	{
		MSG_ASSERT_CODE(L"존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다." + _Name);
	}

	m_AllShader[(int)SHADERTYPE::SHADER_GS] = m_GeoShader;
}

void GameMaterial::SetRasterizer(const GameString& _Name)
{
	m_Rasterizer = GameRasterizer::Find(_Name);

	if (nullptr == m_Rasterizer)
	{
		MSG_ASSERT_CODE(L"존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
	}
}

void GameMaterial::SetDepthStencil(const GameString& _Name)
{
	m_DepthStencil = GameDepthstencil::Find(_Name);

	if (nullptr == m_DepthStencil)
	{
		MSG_ASSERT_CODE(L"존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
	}
}

void GameMaterial::SetBlend(const GameString& _Name)
{
	m_Blend = GameBlend::Find(_Name);

	if (nullptr == m_Blend)
	{
		MSG_ASSERT_CODE(L"존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
	}
}


CPtr<GameMaterial> GameMaterial::MaterialClone()
{
	return new GameMaterial(*this);
}


void GameMaterial::Setting()
{
	if (true == m_AllCheck)
	{
		if (nullptr == m_VtxShader ||
			nullptr == m_PixShader ||
			nullptr == m_Rasterizer ||
			nullptr == m_DepthStencil ||
			nullptr == m_Blend)
		{
			MSG_ASSERT_CODE(L"세팅중 nullptr이 있습니다.");
		}
	}

	if (nullptr != m_VtxShader)
	{
		m_VtxShader->Setting();
	}

	if (nullptr != m_PixShader)
	{
		m_PixShader->Setting();
	}

	if (nullptr != m_GeoShader)
	{
		m_GeoShader->Setting();
	}

	m_Rasterizer->Setting();
	m_DepthStencil->Setting();
	m_Blend->Setting();

}




/// 

/* 
void HSRENDERPATH::LastReset()
{
	for (size_t i = 0; i < HSSHADER::ST_MAX; ++i)
	{
		LastShader[i] = nullptr;
	}
	LastBlend = nullptr;
	LastRasterizer = nullptr;
	LastDepthStencil = nullptr;
}

*/


/* 

void HSRENDERMGR::Render()
{
	HSRENDERPATH::LastReset();
	////////////////Rendering//////////////////
	HSGAMEDEVICE::HMainDevice()->RenderBegin();

	HSGAMEDEVICE::HMainDevice()->DEFRENDERTARGETSET();
	HSGAMEDEVICE::HMainDevice()->DEFVIEWPORTSET();

	for (std::pair<const unsigned int, HSPTR<HSCAM>>& Item : m_AllCam)
	{
		for (unsigned int Value : Item.second->m_Group)
		{

			GIter = m_AllRender.find(Value);

			if (GIter == m_AllRender.end())
			{
				continue;
			}

			for (auto& Renderer : GIter->second)
			{
				if (false == Renderer->IsUpdate())
				{
					continue;
				}

				Renderer->RenderUpdate(Item.second);
				Renderer->Render(Item.second);
			}
		}

	}
	if (true == HS3DDEBUG::IsDebugOnoff())
	{
		m_pScene->DebugRender();
		HS3DDEBUG::DebugRender();
	}
	m_pScene->FontRender();
	HSGAMEFONT::FontRender();

	HSGAMEDEVICE::HMainDevice()->RenderEnd();
}

*/







//#include "GameMaterial.h"
//#include "_ljRenderPath.h"
//#include "HSRENDERPATH.h"
//#include "HSSHADER.h"
//#include "HSVERTEXSHADER.h"
//#include "HSPIXELSHADER.h"
//#include "HSBLEND.h"
//#include "HSRASTERIZER.h"
//#include "HSDEPTHSTENCIL.h"
//
//
//HSSHADER* HSRENDERPATH::LastShader[5];
//HSBLEND* HSRENDERPATH::LastBlend = nullptr;
//HSRASTERIZER* HSRENDERPATH::LastRasterizer = nullptr;
//HSDEPTHSTENCIL* HSRENDERPATH::LastDepthStencil = nullptr;
//
//
//
//HSRENDERPATH::HSRENDERPATH() : m_IsClone(false)
//{
//	m_Shader.resize(HSSHADER::ST_MAX);
//}
//
//HSRENDERPATH::HSRENDERPATH(const HSRENDERPATH& _Other) : m_VTXShader(_Other.m_VTXShader), m_PIXShader(_Other.m_PIXShader), m_Blend(_Other.m_Blend), m_IsClone(true)
//{
//
//}
//
//HSRENDERPATH::~HSRENDERPATH()
//{
//
//}
//
//void HSRENDERPATH::VTXSHADER(const HSSTRING& _Name)
//{
//	m_VTXShader = HSVERTEXSHADER::Find(_Name);
//	if (nullptr == m_VTXShader)
//	{
//		BOOM;
//	}
//	m_Shader[m_VTXShader->ShaderType()] = m_VTXShader;
//}
//
//void HSRENDERPATH::PIXSHADER(const HSSTRING& _Name)
//{
//	m_PIXShader = HSPIXELSHADER::Find(_Name);
//	if (nullptr == m_PIXShader)
//	{
//		BOOM;
//	}
//	m_Shader[m_PIXShader->ShaderType()] = m_PIXShader;
//}
//
//void HSRENDERPATH::BLEND(const HSSTRING& _Name)
//{
//	m_Blend = HSBLEND::Find(_Name);
//	if (nullptr == m_Blend)
//	{
//		BOOM;
//	}
//}
//
//void HSRENDERPATH::RASTERIZER(const HSSTRING& _Name)
//{
//	m_Rasterizer = HSRASTERIZER::Find(_Name);
//	if (nullptr == m_Rasterizer)
//	{
//		BOOM;
//	}
//}
//void HSRENDERPATH::DEPTHSTENCIL(const HSSTRING& _Name)
//{
//	m_DepthStencil = HSDEPTHSTENCIL::Find(_Name);
//	if (nullptr == m_DepthStencil)
//	{
//		BOOM;
//	}
//}
//
//void HSRENDERPATH::LastReset()
//{
//	for (size_t i = 0; i < HSSHADER::ST_MAX; ++i)
//	{
//		LastShader[i] = nullptr;
//	}
//	LastBlend = nullptr;
//	LastRasterizer = nullptr;
//	LastDepthStencil = nullptr;
//}
//
//
//HSPTR<HSRENDERPATH> HSRENDERPATH::Clone()
//{
//	return new HSRENDERPATH(*this);
//}
//
//bool HSRENDERPATH::Create()
//{
//	return true;
//}
//
//void HSRENDERPATH::Setting()
//{
//	//쉐이더 세팅
//	for (size_t i = 0; i < m_Shader.size(); ++i)
//	{
//		if (nullptr == m_Shader[i] && LastShader[i] == m_Shader[i])
//		{
//			continue;
//		}
//		m_Shader[i]->Setting();
//		LastShader[i] = m_Shader[i];
//	}
//	//블렌드 세팅
//	if (nullptr != m_Blend && LastBlend != m_Blend)
//	{
//		m_Blend->Setting();
//		LastBlend = m_Blend;
//	}
//	//레스터라이저 세팅
//	if (nullptr != m_Rasterizer && LastRasterizer != m_Rasterizer)
//	{
//		m_Rasterizer->Setting();
//		LastRasterizer = m_Rasterizer;
//	}
//	//뎁스스텐실 세팅
//	if (nullptr != m_DepthStencil && LastDepthStencil != m_DepthStencil)
//	{
//		m_DepthStencil->Setting();
//		LastDepthStencil = m_DepthStencil;
//	}
//}
