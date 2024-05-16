#include "GameGeometryShader.h"



void GameGeometryShader::Load(const GameString& _FuncName, unsigned int _VH, unsigned int _VL)
{
	m_VH = _VH;
	m_VL = _VL;

	unsigned int Flag = 0;

#ifdef _DEBUG
	// 디버그 모드로 쉐이더 기동
	Flag = D3D10_SHADER_DEBUG;
#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	char Arr[200];

	sprintf_s(Arr, "gs_%d_%d", m_VH, m_VL);

	std::string FuncName = _FuncName;

	if (S_OK != D3DCompileFromFile(
		CFile.FullPath(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		FuncName.c_str(),
		Arr,
		Flag,
		0,
		&m_pBlob,
		&m_pErrBlob)
		)
	{
		GameString ErrorText = (char*)m_pErrBlob->GetBufferPointer();
		MSG_ASSERT_CODE(ErrorText + L"쉐이더 컴파일 에러");
		return;
	}

	if (S_OK != GameDevice::MainObj()->Device()->CreateGeometryShader(
		m_pBlob->GetBufferPointer(),
		m_pBlob->GetBufferSize(),
		nullptr,
		&m_ShaderPtr))
	{
		MSG_ASSERT_CODE(L"버텍스 쉐이더 인터페이스 생성에 실패했습니다");
	}

	ResCheck();
}

void GameGeometryShader::Setting()
{
	GameDevice::MainObj()->Context()->GSSetShader(m_ShaderPtr, 0, 0);
}
