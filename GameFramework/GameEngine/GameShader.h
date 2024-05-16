#pragma once
#include "GameDevice.h"
#include <GameObjTFuncMgr.h>

enum class SHADERTYPE
{
	SHADER_VS,
	SHADER_HS,
	SHADER_DS,
	SHADER_GS,
	SHADER_PS,
	SHADER_END,
};

class ShaderData
{
public:
	GameString Name;
	size_t Size;
	SHADERTYPE ShaderType;
	D3D_SHADER_INPUT_TYPE DataType;
	unsigned int Index;
};

class GameRenderPlayer;
class GameShader
{
public:
	friend GameRenderPlayer;

protected:
	/*
		void* 같아 보이지만 그냥 char[]이다
		char[]안에 쉐이더코드를 담는다.
		컴파일된 코드의 바이너리 포인터
		에러도 담아준다.
	*/
	ID3DBlob* m_pBlob;
	ID3DBlob* m_pErrBlob;
	unsigned int m_VH;
	unsigned int m_VL;
	SHADERTYPE m_Type;

private:
	std::map<GameString, ShaderData> m_ResData;

public:
	void ResCheck();
	static void AutoShaderCompile(const GameString& FileName);

public:
	GameShader();
	~GameShader();
};
