#include "GameShader.h"
#include "GameVtxShader.h"
#include "GamePixShader.h"

#include "GameGeometryShader.h"

void GameShader::AutoShaderCompile(const GameString& FileName)
{

	GameFile File = GameFile(FileName, L"rt");
	GameString AllText = File.AllText();

	std::list<StringData> AllData = AllText.AllFindData(L"(");

	std::list<StringData> Name;
	std::list<StringData> Para;

	std::list<StringData>::iterator Start = AllData.begin();
	std::list<StringData>::iterator End = AllData.end();

	for (; Start != End; ++Start)
	{
		Name.push_back(AllText.RerversTrimToTrim((*Start).StartPos - 1));
		Para.push_back(AllText.TrimToTrim((*Start).EndPos));
	}

	int a1 = 0;

	{
		std::list<StringData>::iterator NameStart = Name.begin();
		std::list<StringData>::iterator NameEnd = Name.end();

		std::list<StringData>::iterator ParaStart = Para.begin();
		std::list<StringData>::iterator ParaEnd = Para.end();

		std::list<StringData> AllFunc = std::list<StringData>();

		for (; NameStart != NameEnd;)
		{
			////////////////////////// �߰��߽��ϴ�. 
			if (std::wstring::npos != NameStart->StrText.Find(L"GS_Particle"))
			{
				int a = 0;
			}
			///////////////////////////

			if (L"register" == (*NameStart).StrText || L"" == (*NameStart).StrText)
			{
				NameStart = Name.erase(NameStart);
				ParaStart = Para.erase(ParaStart);
			}
			else if (L"point" == (*ParaStart).StrText)
			{
				++NameStart;
				++ParaStart;
				// ������Ʈ�� ���̴��� ���
			}
			else
			{
				std::list<StringData> FindParaList = AllText.RerversAllFindData((*ParaStart).StrText, (*ParaStart).StartPos);

				if (0 == FindParaList.size())
				{
					NameStart = Name.erase(NameStart);
					ParaStart = Para.erase(ParaStart);
				}
				else if (0 != FindParaList.size())
				{
					StringData Data;

					for (auto& _ShaderFind : FindParaList)
					{
						Data = AllText.RerversTrimToTrim(_ShaderFind.StartPos - 1);

						if (L"struct" == Data.StrText)
						{
							break;
						}
					}

					if (L"struct" == Data.StrText)
					{
						++NameStart;
						++ParaStart;
					}
					else
					{
						NameStart = Name.erase(NameStart);
						ParaStart = Para.erase(ParaStart);
					}

				}
				else 
				{
					++NameStart;
					++ParaStart;
				}
				int aa = 0;
			}
		}
	}

	if (true == Name.empty())
	{
		MSG_ASSERT_CODE(L"�Լ��� �ϳ��� ������� �ʽ��ϴ�.");
		return;
	}

	if (Name.size() != Para.size())
	{
		MSG_ASSERT_CODE(L"�Լ��� �Ķ������ ������ �ٸ��ϴ�.");
		return;
	}

	int a2 = 0;

	{
		std::list<StringData>::iterator NameStart = Name.begin();
		std::list<StringData>::iterator NameEnd = Name.end();

		std::list<StringData>::iterator ParaStart = Para.begin();
		std::list<StringData>::iterator ParaEnd = Para.end();

		// VtxShader or PixShader????
		for (; NameStart != NameEnd; ++NameStart)
		{
			if (NameStart->StrText == "VS_Particle")
			{
				int a = 0; // Ȯ�� 
			}


			// ���⼭ �ݴ��ʿ� �ִ� ����� ������̿� �ִ� �༮��
			// �Լ��� ���� ���̴�.
			StringData ReturnData = AllText.RerversTrimToTrim(NameStart->StartPos - 1);

			if (L"void" == ReturnData.StrText)
			{
				GameGeometryShader::Load(FileName, NameStart->StrText);
			}



			if (L"float4" == ReturnData.StrText)
			{
				size_t FindStartPos = AllText.Find(L")", ReturnData.EndPos);
				
				FindStartPos = AllText.Find(L":", FindStartPos);

				StringData SementicData = AllText.TrimToTrim(FindStartPos + 1);

				if (0 == SementicData.StrText.Find(L"SV_Position"))
				{
					GameVtxShader::Load(FileName, NameStart->StrText);
					int a3 = 0;
				}
				else if (0 == SementicData.StrText.Find(L"SV_Target"))
				{
					GamePixShader::Load(FileName, NameStart->StrText);
					int a4 = 0;
				}
				else
				{
					MSG_ASSERT_CODE(L"���̴� Ÿ���� ������ �� ���� ��Ȳ�Դϴ�");
				}
			}
			else
			{

				std::list<StringData> FindReturnList = AllText.RerversAllFindData(ReturnData.StrText, ReturnData.StartPos);

				if (0 == FindReturnList.size())
				{
					MSG_ASSERT_CODE(L"�Լ��� ���ϰ��� �������� �ʽ��ϴ�. \n �������ϱ��� ��� ã�ƺ����ϴ� ��Ȳ�Դϴ�. Ȥ�� �Լ��̸� �м� �����Դϴ�.");
				}
				else if (0 != FindReturnList.size())
				{
					StringData FindData;
					
					bool Check = false;

					for (auto& _Shader : FindReturnList)
					{
						FindData = AllText.RerversTrimToTrim(_Shader.StartPos - 1);

						if (L"struct" == FindData.StrText)
						{
							size_t LastPos = AllText.Find(L"}", FindData.EndPos);
							
							GameString StructText = AllText.Cut(FindData.EndPos + 1, LastPos);

							if (std::wstring::npos != StructText.Find(L"SV_Position"))
							{
								GameVtxShader::Load(FileName, NameStart->StrText);
								Check = true;
							}
			
							////////////////////////////////////////////// �߰��߽��ϴ�. 
							else if (std::wstring::npos != StructText.Find(L"Fog"))
							{
								GameVtxShader::Load(FileName, NameStart->StrText);
								Check = true;
							}

							else if (std::wstring::npos != StructText.Find(L"SV_Target"))
							{
								CPtr<GamePixShader> PTR = GamePixShader::Load(FileName, NameStart->StrText);

								GameString Text = StructText.ToUpperReturn();

								if (std::wstring::npos != Text.Find(L"Deferred"))
								{
									PTR->MType(MATERIAL_TYPE::MT_DEFERRED);
									int a = 0;
								}

								if (std::wstring::npos != Text.Find(L"Forward"))
								{
									PTR->MType(MATERIAL_TYPE::MT_FORWARD);
									int a = 0;
								}

								Check = true;
							}
							else
							{
								MSG_ASSERT_CODE(L"���̴� Ÿ���� ������ �� ���� ��Ȳ�Դϴ�");
							}
						}
						else {
							MSG_ASSERT_CODE(L"���̴� Ÿ���� ������ �� ���� ��Ȳ�Դϴ�");
						}
					}
					if (Check == false)
					{
						MSG_ASSERT_CODE(L"���̴� Ÿ���� ������ �� ���� ��Ȳ�Դϴ�");
					}
				}
			}
		}
	}
}


void GameShader::ResCheck()
{
	ID3D11ShaderReflection* Reflector = nullptr;

	if (S_OK
		!=
		D3DReflect(m_pBlob->GetBufferPointer(), m_pBlob->GetBufferSize()
			, IID_ID3D11ShaderReflection, (void**)&Reflector))
	{
	}

	D3D11_SHADER_DESC ShaderDesc;
	Reflector->GetDesc(&ShaderDesc);

	D3D11_SHADER_INPUT_BIND_DESC ResDesc;
	ShaderData SData;
	
	for (unsigned int i = 0; i < ShaderDesc.BoundResources; i++)
	{
		Reflector->GetResourceBindingDesc(i, &ResDesc);

		SData.Name = ResDesc.Name;
		SData.ShaderType = m_Type;
		SData.Index = ResDesc.BindPoint;
		SData.DataType = ResDesc.Type;

		switch (ResDesc.Type)
		{
		case D3D_SIT_CBUFFER:
		{
			ID3D11ShaderReflectionConstantBuffer* ConstBufferData = Reflector->GetConstantBufferByName(ResDesc.Name);
			D3D11_SHADER_BUFFER_DESC BufferDesc;
			ConstBufferData->GetDesc(&BufferDesc);
			SData.Size = BufferDesc.Size;
			break;
		}
		case D3D_SIT_TEXTURE:
			break;
		case D3D_SIT_SAMPLER:
			break;
		case D3D_SIT_STRUCTURED:
			break;
		default:
			MSG_ASSERT_CODE(L"���� ó���ϴ� ����� ������ ���� ���ҽ� �Դϴ�.");
			break;
		}

		if (m_ResData.end() != m_ResData.find(ResDesc.Name))
		{
			MSG_ASSERT_CODE(L"�ߺ� ���ҽ��� �����մϴ�.");
		}

		m_ResData[ResDesc.Name] = SData;
	}
}

GameShader::GameShader()
{
}

GameShader::~GameShader()
{
}
