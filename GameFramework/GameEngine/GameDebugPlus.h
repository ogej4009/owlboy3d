#pragma once
#include <GameString.h>
#include "GameFont.h"
#include <vector>
#include <GameDebug.h>

class GameTexture;
class GameRenderPlayer;
class GameDebugPlus
{
private:
	static CPtr<GameFont> m_DebugFont;
	static float m_BasicFontSize;
	static CVector m_BasicStartPos;
	static CVector m_CurTextSize;
	static CVector m_BasicColor;
	static CPtr<GameRenderPlayer> m_TargetDebugTextureRenderPlayer;
	static CPtr<GameRenderPlayer> m_TargetDebugTextureBackRenderPlayer;
	static CMatrix m_VPMAT;

public:
	static void DebugInit(bool _IsOpenConsole = false);

private:
	class DebugTextInfo
	{
	public:
		GameString Text;
		float Size;
		CVector Pos;
		CVector Color;
	};

	class DebugTextureInfo
	{
	public:
		CPtr<GameTexture> m_Tex;
		CVector BackColor;
		CMatrix WVP;
	};

	static std::vector<DebugTextInfo> m_AllDebugText;
	static std::vector<DebugTextureInfo> m_AllDebugTexture;

public:
	static void DrawDebugText(const GameString& _Text, float _Size, CVector _Pos, CVector _Color);
	static void DrawDebugTexture(const CPtr<GameTexture>& _Texture, CVector _Size, CVector _Pos, CVector _BackColor);

public:
	template<typename ... REST>
	static void DrawDebugText(const GameString& _Text, REST ... _Arg)
	{
		wchar_t ArrText[256];
		swprintf_s(ArrText, _Text, _Arg...);
		GameDebugPlus::DrawDebugText(ArrText, m_BasicFontSize, m_CurTextSize, m_BasicColor);
		m_CurTextSize.Y += m_BasicFontSize;
	}

public:
	template<typename ... REST>
	static void ConsolePrintText(const GameString& _Text, REST ... _Arg)
	{
		GameDebug::ConsolePrintText(_Text, _Arg...);
	}

public:
	static void OpenConsole()
	{
		GameDebug::OpenConsole();
	}

public:
	static bool bDebugMode;

public:
	void DebugSwitch();
	bool DebugMode();

public:
	static void DebugRender();

};