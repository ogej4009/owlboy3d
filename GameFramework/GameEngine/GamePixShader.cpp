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
		nullptr,							// ��ũ�ε� �׳� ���̴� �ȿ� �ִ�.
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	// ��ũ��带 �׳� �˾Ƽ� �ϰڴ�.
		FuncName.c_str(),					// �������ϰ� ���� �Լ��̸�.
		Arr,								// ����
		Flag,	// column->row ����� �д� ����� �ٲ㼭 �����Ѵ�. ��ġ�Ѵ�. transposed �׷��� �����ϰڴ�. 
		0,									// �⺻ �ɼ����� ������
		&m_pBlob,
		&m_pErrBlob)
		)
	{
		GameString ErrorText = (char*)m_pErrBlob->GetBufferPointer();
		MSG_ASSERT_CODE(ErrorText + L"���̴� ������ ����");
		return;
	}

	if (S_OK != GameDevice::MainObj()->Device()->CreatePixelShader(
		m_pBlob->GetBufferPointer(),
		m_pBlob->GetBufferSize(),
		nullptr,
		&m_ShaderPtr))
	{
		MSG_ASSERT_CODE(L"���ؽ� ���̴� �������̽� ������ �����߽��ϴ�");
	}

	ResCheck();
}

void GamePixShader::Setting()
{
	GameDevice::MainObj()->Context()->PSSetShader(m_ShaderPtr, 0, 0);
}

