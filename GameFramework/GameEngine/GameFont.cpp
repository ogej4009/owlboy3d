#include "GameFont.h"
#include "GameDevice.h"

IFW1Factory* GameFont::m_pFontFactory = nullptr;

GameFont::GameFontStarter GameFont::Starter;

void GameFont::FontInit()
{
	if (S_OK != FW1CreateFactory(FW1_VERSION, &m_pFontFactory))
	{
		MSG_ASSERT_CODE(L"폰트 팩토리 생성에 실패했습니다.");
	}
}

GameFont::GameFontStarter::~GameFontStarter()
{
	if (nullptr != m_pFontFactory)
	{
		m_pFontFactory->Release();
	}
}

GameFont::GameFont() : m_pFontWrapper(nullptr)
{
}

GameFont::~GameFont()
{
	if (nullptr != m_pFontWrapper)
	{
		m_pFontWrapper->Release();
	}
}

void GameFont::CreateGameFont(const GameString& _Name)
{
	if (S_OK != m_pFontFactory->CreateFontWrapper(GameDevice::MainObj()->Device(), _Name, &m_pFontWrapper))
	{
		MSG_ASSERT_CODE(L"폰트 생성에 실패했습니다. " + _Name);
	}
}

void GameFont::DrawFont(const GameString& _Text, float _Size, CVector _Pos, CVector _Color, FW1_TEXT_FLAG _Flag)
{
	m_pFontWrapper->DrawString(GameDevice::MainObj()->Context(), _Text, _Size, _Pos.X, _Pos.Y, _Color.ColorToUint(), _Flag);
}