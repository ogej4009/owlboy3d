#include "GamePixShader.h"

void GamePixShader::Load(const GameString& _FuncName, unsigned int _VH, unsigned int _VL)
{
	m_VH = _VH;
	m_VL = _VL;

	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	char Arr[200];

	sprintf_s(Arr, "ps_%d_%d", m_VH, m_VL);

	std::string FuncName = _FuncName;

	if (S_OK != D3DCompileFromFile(
		CFile.FullPath(),
		nullptr,							// 매크로도 그냥 쉐이더 안에 있다.
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	// 인크루드를 그냥 알아서 하겠다.
		FuncName.c_str(),					// 컴파일하고 싶은 함수이름.
		Arr,								// 버전
		Flag,	// column->row 행렬을 읽는 방식을 바꿔서 전달한다. 전치한다. transposed 그렇게 생각하겠다. 
		0,									// 기본 옵션으로 컴파일
		&m_pBlob,
		&m_pErrBlob)
		)
	{
		GameString ErrorText = (char*)m_pErrBlob->GetBufferPointer();
		MSG_ASSERT_CODE(ErrorText + L"쉐이더 컴파일 에러");
		return;
	}

	if (S_OK != GameDevice::MainObj()->Device()->CreatePixelShader(
		m_pBlob->GetBufferPointer(),
		m_pBlob->GetBufferSize(),
		nullptr,
		&m_ShaderPtr))
	{
		MSG_ASSERT_CODE(L"버텍스 쉐이더 인터페이스 생성에 실패했습니다");
	}

	ResCheck();
}

void GamePixShader::Setting()
{
	GameDevice::MainObj()->Context()->PSSetShader(m_ShaderPtr, 0, 0);
}

