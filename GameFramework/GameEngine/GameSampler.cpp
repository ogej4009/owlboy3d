#include "GameSampler.h"

GameSampler::GameSampler(const D3D11_SAMPLER_DESC& _Desc) : m_Desc(_Desc)
{
	Create();
}

GameSampler::~GameSampler()
{
	if (nullptr != m_State)
	{
		m_State->Release();
	}
}

void GameSampler::Create()
{
	if (S_OK != GameDevice::MainObj()->Device()->CreateSamplerState(&m_Desc, &m_State))
	{
		MSG_ASSERT_CODE(L"레스터라이저 스테이트 생성에 실패했습니다.");
	}
}

void GameSampler::Setting(SHADERTYPE _Type, unsigned int _Reg)
{
	switch (_Type)
	{
	case SHADERTYPE::SHADER_VS:
		GameDevice::MainObj()->Context()->VSSetSamplers(_Reg, 1, &m_State);
		break;
	case SHADERTYPE::SHADER_HS:
		GameDevice::MainObj()->Context()->HSSetSamplers(_Reg, 1, &m_State);
		break;
	case SHADERTYPE::SHADER_DS:
		GameDevice::MainObj()->Context()->DSSetSamplers(_Reg, 1, &m_State);
		break;
	case SHADERTYPE::SHADER_GS:
		GameDevice::MainObj()->Context()->GSSetSamplers(_Reg, 1, &m_State);
		break;
	case SHADERTYPE::SHADER_PS:
		GameDevice::MainObj()->Context()->PSSetSamplers(_Reg, 1, &m_State);
		break;
	case SHADERTYPE::SHADER_END:
		break;
	default:
		break;
	}
}