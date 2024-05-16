#include "GameDevice.h"
#include "GameDevice.h"
#include <GameIO.h>
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "GameRasterizer.h"
#include "Vtx.h"
//#include "GameDevice.h" ???


#pragma region 26444 ���ִ� ���
/*
	C++ Ư����� ������
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
#pragma region unnamed scope ����
	/*
		���� �̸��� ���� ���� �׽�Ʈ
	*/
#pragma endregion

#pragma region �����Ͷ����� �ɼ�
	/*
		������ ������ ---> �ȼ����̴� ---> ����Ʈ

		�ʸ�� :
			�ﰢ�� ��(������)�� ��� ä����ΰ�? (���̾�������,

		�ø�� :
			�ð����, �ݽð����
			�׸��� ���� (��, �� ����)�� �˾Ƽ� �����Ѵ�. �׸� �������� ���� ���õ� �����Ѵ�.
	*/
#pragma endregion

	{
		D3D11_RASTERIZER_DESC Desc = { D3D11_FILL_MODE::D3D11_FILL_SOLID , D3D11_CULL_MODE::D3D11_CULL_BACK , 0 };
		Desc.MultisampleEnable = true;
		Desc.AntialiasedLineEnable = true;
		GameRasterizer::Create(L"Back", Desc); // �޸��� �ȱ׸���. 
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
		GameRasterizer::Create(L"None", Desc); // �յ޸������� �ٱ׸���. 
	}

	{
		D3D11_RASTERIZER_DESC Desc = { D3D11_FILL_MODE::D3D11_FILL_WIREFRAME , D3D11_CULL_MODE::D3D11_CULL_NONE , 0 };
		Desc.MultisampleEnable = true;
		Desc.AntialiasedLineEnable = true;
		GameRasterizer::Create(L"WNone", Desc);
	}

}

#pragma warning( pop )