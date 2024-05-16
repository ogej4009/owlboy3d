#pragma once
#include "GameShader.h"
#include <vector>

class GameVtxShader : public GameShader, public GameFileMgr<GameVtxShader>
{
public:
	static CPtr<GameVtxShader> Load(const GameString& _Path, const GameString& _FuncName, unsigned int _VH = 5, unsigned int _VL = 0)
	{
		CPtr<GameVtxShader> Res = CreateAndInsertToName(_Path, _FuncName);
		Res->Load(_FuncName, _VH, _VL);
		return Res;
	}

public:
	unsigned int FmtSize(DXGI_FORMAT _Fmt);

public:
	ID3D11InputLayout* m_pLayOut;
	unsigned int		m_Offset;
	std::vector<D3D11_INPUT_ELEMENT_DESC>	m_ArrInputList;

public:
	void AddLayout
	(
		const char* _SmtName,			// "POSITIONT3"
		unsigned int _Index,			// "POSITIONT0 ~ N"
		DXGI_FORMAT _Fmt,				// r32g32
		unsigned int _InputSlot = 0,	// 무시 인스턴싱 관련
		unsigned int _IDSR = 0,			// 인스턴싱 관련
		D3D11_INPUT_CLASSIFICATION _InputClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA // 인스턴싱 관련
	);

	void CreateLayout();
	void LayOutCheck();

public:
	void Load(const GameString& _FuncName, unsigned int _VH = 5, unsigned int _VL = 0);
	void Setting();

public:
	ID3D11VertexShader* m_ShaderPtr;

public:
	GameVtxShader()
		: m_ShaderPtr(nullptr)
		, m_pLayOut(nullptr)
	{
		// SHADERTYPE:: 최신 VS에서 enum문 사용할 때 정확히 범위를 명시해달라고 유저에게 요청함
		m_Type = SHADERTYPE::SHADER_VS;
	}

	~GameVtxShader()
	{
		if (nullptr != m_pLayOut)
		{
			m_pLayOut->Release();
		}
		m_ShaderPtr->Release();
	}

};