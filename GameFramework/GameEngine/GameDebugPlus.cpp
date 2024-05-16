#include "GameDebugPlus.h"
#include "GameTexture.h"
#include "GameRenderer.h"
#include "GameRenderTarget.h"


std::vector<GameDebugPlus::DebugTextInfo> GameDebugPlus::m_AllDebugText;
CPtr<GameFont>	GameDebugPlus::m_DebugFont;
float GameDebugPlus::m_BasicFontSize = 20.0f;
CVector GameDebugPlus::m_BasicStartPos = CVector(0.0F, 0.0F, 0.0F, 0.0F);
CVector GameDebugPlus::m_CurTextSize = CVector(0.0F, 0.0F, 0.0F, 0.0F);
CVector GameDebugPlus::m_BasicColor = CVector::BLACK;

CPtr<GameRenderPlayer> GameDebugPlus::m_TargetDebugTextureRenderPlayer;
CPtr<GameRenderPlayer> GameDebugPlus::m_TargetDebugTextureBackRenderPlayer;
std::vector<GameDebugPlus::DebugTextureInfo> GameDebugPlus::m_AllDebugTexture;
CMatrix GameDebugPlus::m_VPMAT;

bool GameDebugPlus::bDebugMode = true;

void GameDebugPlus::DebugSwitch()
{
	if (false == bDebugMode)
	{
		bDebugMode = true;
	}
	else
	{
		bDebugMode = false;
	}
}

bool GameDebugPlus::DebugMode()
{
	return bDebugMode;
}

void GameDebugPlus::DebugInit(bool _IsOpenConsole)
{
	CMatrix P;
	CMatrix V;
	V.VIEWLH(CVector(0.0F, 0.0F, -10.0F), CVector::FORWARD, CVector::UP);
	P.ORTHLH(GameDevice::MainObj()->BackBufferRenderTarget()->Texture(0)->Size(), 0.1f, 1000.0f);
	m_VPMAT = V * P;

	GameFont::FontInit();

	m_DebugFont = new GameFont();
	m_DebugFont->CreateGameFont(L"DroidSansFallback.ttf");
	//m_DebugFont->CreateGameFont(L"±¼¸²");

	m_TargetDebugTextureRenderPlayer = new GameRenderPlayer();
	m_TargetDebugTextureRenderPlayer->SetMesh(L"TargetDebugRect");
	m_TargetDebugTextureRenderPlayer->SetMaterial(L"TargetDebug");
	m_TargetDebugTextureRenderPlayer->SetSampler(L"Smp", L"LWSMP");

	m_TargetDebugTextureBackRenderPlayer = new GameRenderPlayer();
	m_TargetDebugTextureBackRenderPlayer->SetMesh(L"TargetDebugRect");
	m_TargetDebugTextureBackRenderPlayer->SetMaterial(L"TargetDebugBack");

	m_AllDebugText.reserve(100);
	m_AllDebugTexture.reserve(100);

	if (true == _IsOpenConsole)
	{
		OpenConsole();
	}
}

void GameDebugPlus::DrawDebugText(const GameString& _Text, float _Size, CVector _Pos, CVector _Color)
{
	m_AllDebugText.push_back({ _Text, _Size, _Pos, _Color });
}

void GameDebugPlus::DrawDebugTexture(const CPtr<GameTexture>& _Texture, CVector _Size, CVector _Pos, CVector _BackColor)
{
	CMatrix MAT;
	_Size.Z = 1.0F;
	_Pos.X += _Size.HX();
	_Pos.Y -= _Size.HY();
	MAT.SetWorld(_Size, { 0.0f, 0.0f, 0.0f, 1.0f }, _Pos);
	MAT = MAT * m_VPMAT;
	m_AllDebugTexture.push_back({ _Texture, _BackColor, MAT });
}


void GameDebugPlus::DebugRender()
{

	for (size_t i = 0; i < m_AllDebugTexture.size(); i++)
	{
		m_TargetDebugTextureBackRenderPlayer->SetCBuffer(L"WVP_Matrix", &m_AllDebugTexture[i].WVP, CBUFMODE::CB_LINK);
		m_TargetDebugTextureBackRenderPlayer->SetCBuffer(L"BackColor", &m_AllDebugTexture[i].BackColor, CBUFMODE::CB_LINK);
		m_TargetDebugTextureBackRenderPlayer->Render();
		m_TargetDebugTextureBackRenderPlayer->Reset();

		m_TargetDebugTextureRenderPlayer->SetTexture(L"Tex", m_AllDebugTexture[i].m_Tex);
		m_TargetDebugTextureRenderPlayer->SetCBuffer(L"WVP_Matrix", &m_AllDebugTexture[i].WVP, CBUFMODE::CB_LINK);
		m_TargetDebugTextureRenderPlayer->Render();
		m_TargetDebugTextureRenderPlayer->Reset();
	}


	if (true == bDebugMode)
	{
		for (size_t i = 0; i < m_AllDebugText.size(); i++)
		{
			m_DebugFont->DrawFont(m_AllDebugText[i].Text, m_AllDebugText[i].Size, m_AllDebugText[i].Pos, m_AllDebugText[i].Color);
		}
	}

	m_CurTextSize = m_BasicStartPos;
	m_AllDebugText.clear();
	m_AllDebugTexture.clear();
	GameDevice::Reset();
}