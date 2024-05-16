#include "GameDevice.h"
#include <GameIO.h>
#include "GameSampler.h"
#include "GameTexture.h"

#pragma region 샘플러 정의 
/* 샘플러는 텍스처를 텍스처의 색상을 가져오는 방법을 정의한다. */
#pragma endregion

#pragma region 샘플링 기술 
/*
	<< 보간이 되는 순간 >>
	샘플러는 픽셀쉐이더에 영향을준다.
	MSAA(Multi-Sampling  Anti-Aliasing)기술 : 임의의 센서에 점을 얼마나 감지할 수 있을까?
	안티얼라이언스는 자동적용 (외곽에 애매한 애들은 반투명 적용)

	<< 보간에 의한 보이는 것의 차이 >>
	D3D11_FILTER :: MIMM0AP_MIP_LINEAR (라인처리의 장점)
	D3D11_FILTER :: MIN_MAG_MIP_POINT (픽셀이 잘보임)

	<< 텍스쳐 압축, 밉맵 >>
	TEXTURE -> ADDRESS_MODE
	CLAMP	:
	WRAP	:
	D3D11_COMPARISON_NEVER (이미지 압축 방식 사용 안함)
	미리 크거나 작은 이미지를 만들어놓고 그걸 사용하지 않는다는 의미이다.
	이 순간 다음 코드(설정)는 의미가 없다.

	<< LOD == LEVEL OF DETAIL >>
	"멀리 있는 물체는 잘 보이지 않는다."는 생각을 바탕으로
	랜더링될 이미지에 기여도가 작을 경우 간략하게 표현하는 방법이다.
	단계를 나누어 설계에 따라 성능이나 속도에 차이가 생긴다.
	(Z값)어느정도 멀리 있을 때까지의 그림을 취할 것인가. 크기, 선명함을 좌우한다.
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



	/////////////////////////// 추가했습니다. 
	{
		D3D11_SAMPLER_DESC Desc = {};

		Desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

		// 이미지 압축 방식 사용안함
		Desc.ComparisonFunc = D3D11_COMPARISON_NEVER;

		Desc.MaxAnisotropy = 0;

		// 내가 D3D11_COMPARISON_NEVER를 한순간 아래는 사실 큰 의미는 없다.
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