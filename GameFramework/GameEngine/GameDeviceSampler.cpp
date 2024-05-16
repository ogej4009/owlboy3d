#include "GameDevice.h"
#include <GameIO.h>
#include "GameSampler.h"
#include "GameTexture.h"

#pragma region ���÷� ���� 
/* ���÷��� �ؽ�ó�� �ؽ�ó�� ������ �������� ����� �����Ѵ�. */
#pragma endregion

#pragma region ���ø� ��� 
/*
	<< ������ �Ǵ� ���� >>
	���÷��� �ȼ����̴��� �������ش�.
	MSAA(Multi-Sampling  Anti-Aliasing)��� : ������ ������ ���� �󸶳� ������ �� ������?
	��Ƽ����̾𽺴� �ڵ����� (�ܰ��� �ָ��� �ֵ��� ������ ����)

	<< ������ ���� ���̴� ���� ���� >>
	D3D11_FILTER :: MIMM0AP_MIP_LINEAR (����ó���� ����)
	D3D11_FILTER :: MIN_MAG_MIP_POINT (�ȼ��� �ߺ���)

	<< �ؽ��� ����, �Ӹ� >>
	TEXTURE -> ADDRESS_MODE
	CLAMP	:
	WRAP	:
	D3D11_COMPARISON_NEVER (�̹��� ���� ��� ��� ����)
	�̸� ũ�ų� ���� �̹����� �������� �װ� ������� �ʴ´ٴ� �ǹ��̴�.
	�� ���� ���� �ڵ�(����)�� �ǹ̰� ����.

	<< LOD == LEVEL OF DETAIL >>
	"�ָ� �ִ� ��ü�� �� ������ �ʴ´�."�� ������ ��������
	�������� �̹����� �⿩���� ���� ��� �����ϰ� ǥ���ϴ� ����̴�.
	�ܰ踦 ������ ���迡 ���� �����̳� �ӵ��� ���̰� �����.
	(Z��)������� �ָ� ���� �������� �׸��� ���� ���ΰ�. ũ��, �������� �¿��Ѵ�.
*/
#pragma endregion

void GameDevice::SamplerInit()
{
	{
		D3D11_SAMPLER_DESC Desc = { };
		Desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		Desc.MaxAnisotropy = 0;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;
		Desc.MipLODBias = 1.0f;
		GameSampler::Create(L"LCSMP", Desc);
	}

	{
		D3D11_SAMPLER_DESC Desc = { };
		Desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		Desc.MaxAnisotropy = 0;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;
		Desc.MipLODBias = 1.0f;
		GameSampler::Create(L"LWSMP", Desc);
	}

	{
		D3D11_SAMPLER_DESC Desc = { };
		Desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		Desc.MaxAnisotropy = 0;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;
		Desc.MipLODBias = 1.0f;
		GameSampler::Create(L"PCSMP", Desc);
	}

	{
		D3D11_SAMPLER_DESC Desc = { };
		Desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		Desc.MaxAnisotropy = 0;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;
		Desc.MipLODBias = 1.0f;
		GameSampler::Create(L"PWSMP", Desc);
	}



	/////////////////////////// �߰��߽��ϴ�. 
	{
		D3D11_SAMPLER_DESC Desc = {};

		Desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

		// �̹��� ���� ��� ������
		Desc.ComparisonFunc = D3D11_COMPARISON_NEVER;

		Desc.MaxAnisotropy = 0;

		// ���� D3D11_COMPARISON_NEVER�� �Ѽ��� �Ʒ��� ��� ū �ǹ̴� ����.
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;
		Desc.MipLODBias = 1.0f;

		GameSampler::Create(L"FireSmp", Desc);
	}

	{
		D3D11_SAMPLER_DESC Desc = {};

		Desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

		Desc.MaxAnisotropy = 1;
		Desc.MinLOD = 0.0f;
		Desc.MaxLOD = FLT_MAX;
		Desc.MipLODBias = 0.0f;

		GameSampler::Create(L"FireSmp2", Desc);
	}
	{
		GameDirectory Dic;

		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"Res");
		Dic.Move(L"Texture");

		auto FileList = Dic.DirAllFile();

		for (auto& _File : FileList)
		{
			GameTexture::Load(_File);
		}
	}

}