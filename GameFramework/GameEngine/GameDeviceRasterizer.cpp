#include "GameDevice.h"
#include "GameDevice.h"
#include <GameIO.h>
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "GameRasterizer.h"
#include "Vtx.h"
//#include "GameDevice.h" ???


#pragma region 26444 없애는 방법
/*
	C++ 특정경고 사용안함
	#pragma warning( push )
	#pragma warning( disable : 26444 )
	{

	}
	#pragma warning( pop )
*/
#pragma endregion

#pragma warning( push )
#pragma warning( disable : 26444 )

void GameDevice::RasterizerInit()
{
#pragma region unnamed scope 문법
	/*
		같은 이름을 쓰기 위한 테스트
	*/
#pragma endregion

#pragma region 레스터라이저 옵션
	/*
		레스터 라이저 ---> 픽셀쉐이더 ---> 프린트

		필모드 :
			삼각형 면(프레임)을 어떻게 채울것인가? (와이어프레임,

		컬모드 :
			시계방향, 반시계방향
			그리는 순서 (앞, 뒤 순서)는 알아서 설정한다. 그릴 것인지에 대한 선택도 결정한다.
	*/
#pragma endregion

	{
		D3D11_RASTERIZER_DESC Desc = { D3D11_FILL_MODE::D3D11_FILL_SOLID , D3D11_CULL_MODE::D3D11_CULL_BACK , 0 };
		Desc.MultisampleEnable = true;
		Desc.AntialiasedLineEnable = true;
		GameRasterizer::Create(L"Back", Desc); // 뒷면은 안그린다. 
	}

	{
		D3D11_RASTERIZER_DESC Desc = { D3D11_FILL_MODE::D3D11_FILL_WIREFRAME , D3D11_CULL_MODE::D3D11_CULL_BACK , 0 };
		Desc.MultisampleEnable = true;
		Desc.AntialiasedLineEnable = true;
		GameRasterizer::Create(L"WBack", Desc);
	}

	{
		D3D11_RASTERIZER_DESC Desc = { D3D11_FILL_MODE::D3D11_FILL_SOLID , D3D11_CULL_MODE::D3D11_CULL_FRONT , 0 };
		Desc.MultisampleEnable = true;
		Desc.AntialiasedLineEnable = true;
		GameRasterizer::Create(L"Front", Desc);
	}

	{
		D3D11_RASTERIZER_DESC Desc = { D3D11_FILL_MODE::D3D11_FILL_WIREFRAME , D3D11_CULL_MODE::D3D11_CULL_FRONT , 0 };
		Desc.MultisampleEnable = true;
		Desc.AntialiasedLineEnable = true;
		GameRasterizer::Create(L"WFront", Desc);
	}

	{
		D3D11_RASTERIZER_DESC Desc = { D3D11_FILL_MODE::D3D11_FILL_SOLID , D3D11_CULL_MODE::D3D11_CULL_NONE , 0 };
		Desc.MultisampleEnable = true;
		Desc.AntialiasedLineEnable = true;
		GameRasterizer::Create(L"None", Desc); // 앞뒷면상관없이 다그린다. 
	}

	{
		D3D11_RASTERIZER_DESC Desc = { D3D11_FILL_MODE::D3D11_FILL_WIREFRAME , D3D11_CULL_MODE::D3D11_CULL_NONE , 0 };
		Desc.MultisampleEnable = true;
		Desc.AntialiasedLineEnable = true;
		GameRasterizer::Create(L"WNone", Desc);
	}

}

#pragma warning( pop )