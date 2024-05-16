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
		void* ���� �������� �׳� char[]�̴�
		char[]�ȿ� ���̴��ڵ带 ��´�.
		�����ϵ� �ڵ��� ���̳ʸ� ������
		������ ����ش�.
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
