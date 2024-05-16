#pragma once
#include "GameShader.h"

class GameGeometryShader : public GameShader, public GameFileMgr<GameGeometryShader>
{
public:
	static CPtr<GameGeometryShader> Load(const GameString& Path, const GameString& FuncName, unsigned int _VH = 5, unsigned int _VL = 0)
	{
		CPtr<GameGeometryShader> Res = CreateAndInsert(Path, FuncName);
		Res->Load(FuncName, _VH, _VL);
		return Res;
	}

private:
	ID3D11GeometryShader* m_ShaderPtr;

public:
	void Load(const GameString& FuncName, unsigned int _VH = 5, unsigned int _VL = 0);
	void Setting();

public:
	GameGeometryShader() : m_ShaderPtr(nullptr)
	{
		m_Type = SHADERTYPE::SHADER_GS;
	}

	~GameGeometryShader()
	{
		m_ShaderPtr->Release();
	}
};


