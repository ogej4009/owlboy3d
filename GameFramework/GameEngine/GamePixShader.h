#pragma once
#include "GameShader.h"

enum class MATERIAL_TYPE
{
	MT_FORWARD,
	MT_DEFERRED,
	RP_SHADOW,
};

class GamePixShader : public GameShader, public GameFileMgr<GamePixShader>
{
	MATERIAL_TYPE m_MType;

public:
	void MType(MATERIAL_TYPE Type)
	{
		m_MType = Type;
	}

	MATERIAL_TYPE MType()
	{
		return m_MType;
	}

public:
	static CPtr<GamePixShader> Load(const GameString& _Path, const GameString& _FuncName, unsigned int _VH = 5, unsigned int _VL = 0)
	{
		CPtr<GamePixShader> Res = CreateAndInsertToName(_Path, _FuncName);
		Res->Load(_FuncName, _VH, _VL);
		return Res;
	}

public:
	ID3D11PixelShader* m_ShaderPtr;

public:
	void Load(const GameString& _FuncName, unsigned int _VH = 5, unsigned int _VL = 0);
	void Setting();

public:
	GamePixShader() : m_ShaderPtr(nullptr), m_MType(MATERIAL_TYPE::MT_FORWARD)
	{
		m_Type = SHADERTYPE::SHADER_PS;
	}

	~GamePixShader()
	{
		m_ShaderPtr->Release();
	}
};