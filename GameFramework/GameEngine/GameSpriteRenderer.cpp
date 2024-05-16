#include "GameSpriteRenderer.h"
#include "GameActor.h"
#include "GameScene.h"
#include "GameDevice.h"
#include "GameVtxBuffer.h"
#include "GameIdxBuffer.h"
#include "GameConstantBuffer.h"
#include "GameDepthstencil.h"
#include "GameBlend.h"
#include "GameRasterizer.h"
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "GameSampler.h"
#include "GameTexture.h"
#include "GameCamera.h"
#include <GameString.h>

void GameSpriteRenderer::Init()
{
	GameRenderer::Init(L"FrameRect", L"Default", 0);


}

void GameSpriteRenderer::Init(int Order)
{
	GameRenderer::Init(L"FrameRect", L"Default", Order);
	//// m_TD : 트랜스폼 데이터 
	//// 상수버퍼를 Create()만 한다. 
	//// 값을 채워넣는다.
	m_SprDrawColor = CVector::WHITE;
	//m_SprRenderOption[3] = m_SprRenderOption[2] = m_SprRenderOption[1] = m_SprRenderOption[0] = 0;
}

void GameSpriteRenderer::Init(const GameString& Name, int Order)
{
	GameRenderer::Init(L"FrameRect", L"Default", Order);

	m_SprDrawColor = CVector::WHITE;
	//m_SprRenderOption[3] = m_SprRenderOption[2] = m_SprRenderOption[1] = m_SprRenderOption[0] = 0;
	m_Sprite = GameSprite::Find(Name);

	if (m_Sprite != nullptr)
	{
		m_SprCutData = m_Sprite->SpriteData(0);
		SetTexture(L"Tex", m_Sprite->Tex());
		SetSampler(L"Smp", L"LWSMP");
		//SetCBuffer(L"TransData", m_Parent->GetPTransData(), CBUFMODE::CB_LINK);
		SetCBuffer(L"CutData", &m_SprCutData, CBUFMODE::CB_LINK);
		SetCBuffer(L"DrawColor", &m_SprDrawColor, CBUFMODE::CB_LINK);
		//SetCBuffer(L"RenderOption", &m_SprRenderOption, CBUFMODE::CB_LINK);
		//m_SprParent->CreateRenderPlayer(0)->m_RenderOption.IsDifTexture = false;
		//m_SprParent->CreateRenderPlayer(0)->m_RenderOption.IsNormalTexture = true;
	}

}

void GameSpriteRenderer::Update()
{
	m_SprCutData = m_Sprite->SpriteData(m_SprIndex);
}

void GameSpriteRenderer::Render(CPtr<GameCamera> _Cam)
{
	/*
	DebugCheck();
	if (nullptr == m_Sprite)
	{
		MSG_ASSERT_CODE(L"스프라이트가 세팅되지 않았습니다");
	}
	m_SprCutData = m_Sprite->SpriteData(m_SprIndex);
	SetCBuffer(L"TransData", m_Parent->GetPTransData(), CBUFMODE::CB_LINK);
	SetCBuffer(L"CutData", &m_SprCutData, CBUFMODE::CB_LINK);
	SetCBuffer(L"DrawColor", &m_SprDrawColor, CBUFMODE::CB_LINK);
	SetCBuffer(L"RenderOption", &m_SprRenderOption, CBUFMODE::CB_LINK);
	SetTexture(L"Tex", m_Sprite->Tex());
	SetSampler(L"Smp", L"PWSMP");
	*/
	//GameRenderer::Render(_Cam);

}

void GameSpriteRenderer::RenderUpdate(CPtr<GameCamera> _Cam)
{
	//m_Sprite->Tex()->Setting(SHADERTYPE::SHADER_PS, 0);
	/*
	SetTexture(L"Tex", m_Sprite->Tex());
	SetSampler(L"Smp", L"PWSMP");
	*/
}

GameSpriteRenderer::GameSpriteRenderer()
{
}

GameSpriteRenderer::~GameSpriteRenderer()
{
}

/*
	CBTRANS->Setting(SHADERTYPE::SHADER_VS, 0); << 쉐이더 슬롯 넘버 
	CUTDATA->Setting(SHADERTYPE::SHADER_VS, 1);
	CBCOLOR->Setting(SHADERTYPE::SHADER_PS, 0);
	OPTION->Setting(SHADERTYPE::SHADER_PS, 1);

	m_Spr->Tex()->Setting(SHADERTYPE::SHADER_PS, 0);
	SMP->Setting(SHADERTYPE::SHADER_PS, 0);
*/

