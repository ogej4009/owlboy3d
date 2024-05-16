#include "GameRenderer.h"
#include "GameActor.h"
#include "GameScene.h"
#include "GameDevice.h"
#include "GameVtxBuffer.h"
#include "GameIdxBuffer.h"
#include "GameConstantBuffer.h"
#include "GameDepthstencil.h"
#include "GameBlend.h"
#include "GameRasterizer.h"
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "GameSampler.h"
#include "GameCamera.h"
#include "GameMesh.h"
#include "GameConstantBuffer.h"
#include "GameSprite.h"
#include "GameLight.h"

//////////////////////////////////////////////// 랜더러 ////////////////////////////////////////////////

GameRenderer::GameRenderer() {}
GameRenderer::~GameRenderer() {}

void GameRenderer::Init(int _Order)
{

	if (nullptr == GetActor()->GetScene())
	{
		MSG_ASSERT_CODE(L"랜더러 에러");
	}

	SetParent(GetActor()->GetTrans());
	Order(_Order);
	GetActor()->GetScene()->PushRender(this);
}

void GameRenderer::Init(const GameString& _Mesh, const GameString& _Mat, int _Order)
{
	Init(_Order);
	CreateRenderPlayer(_Mesh, _Mat);
}

void GameRenderer::Init(const CPtr<GameMesh>& _Mesh, const GameString& _Mat, int _Order)
{
	Init(_Order);
	CreateRenderPlayer(_Mesh, _Mat);
}

CPtr<GameRenderPlayer> GameRenderer::CreateRenderPlayer(const CPtr<GameMesh>& _Mesh, const GameString& _Mat)
{
	GameRenderPlayer* NewPlayer = new GameRenderPlayer();
	NewPlayer->m_Parent = this;
	NewPlayer->SetMesh(_Mesh);
	NewPlayer->SetMaterial(_Mat);
	m_PlayerList.push_back(NewPlayer);
	return NewPlayer;
}

CPtr<GameRenderPlayer> GameRenderer::CreateRenderPlayer(const GameString& _Mesh, const GameString& _Mat)
{
	GameRenderPlayer* NewPlayer = new GameRenderPlayer();
	NewPlayer->m_Parent = this;
	NewPlayer->SetMesh(_Mesh);
	NewPlayer->SetMaterial(_Mat);
	m_PlayerList.push_back(NewPlayer);
	return NewPlayer;
}

CPtr<GameRenderPlayer> GameRenderer::CreateRenderPlayer(const CPtr<GameMesh>& _Mesh)
{
	GameRenderPlayer* NewPlayer = new GameRenderPlayer();
	NewPlayer->m_Parent = this;
	NewPlayer->SetMesh(_Mesh);
	m_PlayerList.push_back(NewPlayer);
	return NewPlayer;
}

CPtr<GameRenderPlayer> GameRenderer::GetRenderPlayer(int _Index)
{
	return m_PlayerList[_Index];
}

void GameRenderer::SetTexture(const GameString& _Name, const CPtr<GameTexture>& _Res)
{
	for (auto& RenderPlayer : m_PlayerList)
	{
		RenderPlayer->SetTexture(_Name, _Res);
	}
}

void GameRenderer::SetTexture(const GameString& _Name, const GameString& _ResName)
{
	for (auto& RenderPlayer : m_PlayerList)
	{
		RenderPlayer->SetTexture(_Name, _ResName);
	}
}

void GameRenderer::SetCBuffer(const GameString& _Name, void* _Data, CBUFMODE _Mode)
{
	for (auto& RenderPlayer : m_PlayerList)
	{
		RenderPlayer->SetCBuffer(_Name, _Data, _Mode);
	}
}

void GameRenderer::SetSampler(const GameString& _Name, const GameString& _ResName)
{
	for (auto& RenderPlayer : m_PlayerList)
	{
		RenderPlayer->SetSampler(_Name, _ResName);
	}
}


void GameRenderer::Render(CPtr<GameCamera> _Cam)
{
	CamUpdate(_Cam);

	for (auto& RenderPlayer : m_PlayerList)
	{
		if (false == RenderPlayer->IsUpdateObj())
		{
			continue;
		}

		if (true == RenderPlayer->IsConBuffer(L"LightData"))
		{
			ObjectLightData* Data = GetScene()->GetLightData(Order());
			RenderPlayer->SetCBuffer(L"LightData", Data, CBUFMODE::CB_LINK);
		};

		RenderPlayer->Render();
	}
}


void GameRenderer::DeferredRender(CPtr<GameCamera> _Cam)
{
	if (0 == m_DeferredList.size())
	{
		return;
	}

	CamUpdate(_Cam);

	for (auto& RenderPlayer : m_DeferredList)
	{
		if (false == RenderPlayer->IsUpdateObj())
		{
			continue;
		}

		if (true == RenderPlayer->IsConBuffer(L"LightData"))
		{
			ObjectLightData* Data = GetScene()->GetLightData(Order());
			RenderPlayer->SetCBuffer(L"LightData", Data, CBUFMODE::CB_LINK);
		};

		RenderPlayer->Render();
	}
}


void GameRenderer::ForwardRender(CPtr<GameCamera> _Cam)
{
	if (0 == m_ForwardList.size())
	{
		return;
	}

	CamUpdate(_Cam);

	for (auto& RenderPlayer : m_ForwardList)
	{
		if (false == RenderPlayer->IsUpdateObj())
		{
			continue;
		}

		if (true == RenderPlayer->IsConBuffer(L"LightData"))
		{
			ObjectLightData* Data = GetScene()->GetLightData(Order());
			RenderPlayer->SetCBuffer(L"LightData", Data, CBUFMODE::CB_LINK);
		};

		RenderPlayer->Render();
	}
}

void GameRenderer::ShadowRender(const LightData& _Light)
{
	LightUpdate(_Light);

	for (auto& RenderPlayer : m_ShadowList)
	{
		if (false == RenderPlayer->IsUpdateObj())
		{
			continue;
		}

		RenderPlayer->Render();
	}
}


void GameRenderer::ShadowOn()
{

	for (auto& RenderPlayer : m_DeferredList)
	{
		GameRenderPlayer* NewPlayer = new GameRenderPlayer();
		NewPlayer->m_Parent = this;
		NewPlayer->SetMesh(RenderPlayer->GetMesh());
		NewPlayer->SetMaterial(L"Shadow", false);

		if (true == RenderPlayer->IsTexture(L"FrameAniTex"))
		{
			CPtr<GameTexture> Tex = RenderPlayer->GetTexture(L"FrameAniTex");
			GameString TexName = Tex->Name();

			if (nullptr != Tex && L"Error.png" != TexName)
			{
				NewPlayer->m_RenderOption.IsAni = true;
				NewPlayer->SetTexture(L"FrameAniTex", Tex);
			}
		}

		m_ShadowList.push_back(NewPlayer);

	}
}


//////////////////////////////////////////////// 플레이어 ////////////////////////////////////////////////

std::list<TextureData*> GameRenderPlayer::AllTexData(const GameString& _SetterName)
{
	std::list<TextureData*> List;

	if (false == IsTexture(_SetterName))
	{
		return List;
	}

	for (auto& _Setter : m_Texture[_SetterName])
	{
		List.push_back(&_Setter);
	}

	return List;
}

CPtr<GameMesh> GameRenderPlayer::GetMesh()
{
	return m_Mesh;
}

CPtr<GameMaterial> GameRenderPlayer::GetMaterial()
{
	return m_Material;
}

void GameRenderPlayer::SetMesh(const CPtr<GameMesh>& _Mesh)
{
	if (nullptr == _Mesh)
	{
		MSG_ASSERT_CODE(L"nullptr인 매쉬를 세팅해줄수는 없습니다.");
	}

	m_Mesh = _Mesh;
}

void GameRenderPlayer::SetMesh(const GameString& _Name)
{
	m_Mesh = GameMesh::Find(_Name);

	if (nullptr == m_Mesh)
	{
		MSG_ASSERT_CODE(L"존재하지 않는 매쉬을 세팅하려고 했습니다.");
	}
}

void GameRenderPlayer::SetMaterial(const GameString& _Name, bool _Push)
{
	m_Material = GameMaterial::Find(_Name);

	if (nullptr == m_Material)
	{
		MSG_ASSERT_CODE(L"존재하지 않는 메테리얼을 세팅하려고 했습니다.");
	}

	for (auto _Shader : m_Material->m_AllShader)
	{
		if (nullptr == _Shader)
		{
			continue;
		}

		for (auto& _Res : _Shader->m_ResData)
		{
			switch (_Res.second.DataType)
			{
			case D3D_SIT_CBUFFER:
			{
				m_ConBuffer[_Res.second.Name].resize(m_ConBuffer[_Res.second.Name].size() + 1);
				ConBufferData& Data = m_ConBuffer[_Res.second.Name][m_ConBuffer[_Res.second.Name].size() - 1];
				Data.m_Data = &(_Res.second);
				Data.m_Res = new GameConstantBuffer();
				Data.m_Res->Create((int)Data.m_Data->Size);
				Data.m_Mode = CBUFMODE::CB_NONE;

				if (L"TransData" == _Res.second.Name)
				{
					SetCBuffer(L"TransData", m_Parent->GetPTransData(), CBUFMODE::CB_LINK);
				} // XTransData WTransData HTransData

				if (L"RenderOption" == _Res.second.Name)
				{
					SetCBuffer(L"RenderOption", &m_RenderOption, CBUFMODE::CB_LINK);
				}

				break;
			}
			case D3D_SIT_TEXTURE:
			{
				m_Texture[_Res.second.Name].resize(m_Texture[_Res.second.Name].size() + 1);
				TextureData& Data = m_Texture[_Res.second.Name][m_Texture[_Res.second.Name].size() - 1];
				Data.m_Data = &(_Res.second);
				Data.m_Res = GameTexture::Find(L"Error.png");
				Data.IsOption = false;
				int a = 0;
				break;
			}
			case D3D_SIT_SAMPLER:
			{
				m_Sampler[_Res.second.Name].resize(m_Sampler[_Res.second.Name].size() + 1);
				SamplerData& Data = m_Sampler[_Res.second.Name][m_Sampler[_Res.second.Name].size() - 1];
				Data.m_Data = &(_Res.second);
				Data.m_Res = GameSampler::Find(L"LWSMP");
				break;
			}
			case D3D_SIT_STRUCTURED:
			{
				m_StructuredBuffer[_Res.second.Name].resize(m_StructuredBuffer[_Res.second.Name].size() + 1);
				StructuredBufferData& Setter = m_StructuredBuffer[_Res.second.Name][m_StructuredBuffer[_Res.second.Name].size() - 1];
				Setter.m_Data = &(_Res.second);
				Setter.m_Res = nullptr;
				break;
			}
			default:
				MSG_ASSERT_CODE(L"아직 처리하는 방식을 정하지 않은 리소스 입니다.");
				break;
			}
		}
	}

	if (nullptr == m_Parent)
	{
		return;
	}

	//////////////////////////////////////////////////////////////////// 확인 
	if (true == _Push)
	{
		switch (m_Material->MType())
		{
		case MATERIAL_TYPE::MT_DEFERRED:
			m_Parent->m_DeferredList.push_back(this);
			break;
		case MATERIAL_TYPE::MT_FORWARD:
			m_Parent->m_ForwardList.push_back(this);
			break;
		default:
			break;
		}
	}
	
}

CPtr<GameTexture> GameRenderPlayer::GetTexture(const GameString& _Name)
{
	for (auto& _Res : m_Texture[_Name])
	{
		if (nullptr != _Res.m_Res)
		{
			return _Res.m_Res;
		}
	}

	return nullptr;
}

void GameRenderPlayer::SetTexture(const GameString& _Name, const CPtr<GameTexture>& _Tex)
{
	if (false == IsTexture(_Name))
	{
		MSG_ASSERT_CODE(L"존재하지 않는 텍스처 세팅입니다." + _Name);
	}
	
	if (nullptr == _Tex)
	{
		MSG_ASSERT_CODE(L"존재하지 않는 텍스처 를 세팅하려고 했습니다." + _Name);
		return;
	}

	for (auto& _Res : m_Texture[_Name])
	{
		_Res.m_Res = _Tex;
	}
}

void GameRenderPlayer::SetTexture(const GameString& _Name, const GameString& _TexName)
{
	if (false == IsTexture(_Name))
	{
		MSG_ASSERT_CODE(L"존재하지 않는 텍스처 세팅입니다." + _Name);
	}

	CPtr<GameTexture> Tex = GameTexture::Find(_TexName);

	if (nullptr == Tex)
	{
		MSG_ASSERT_CODE(L"존재하지 않는 텍스처 를 세팅하려고 했습니다." + _Name);
		return;
	}

	for (auto& _Res : m_Texture[_Name])
	{
		_Res.m_Res = Tex;
	
	}
}

void GameRenderPlayer::SetSampler(const GameString& _Name, const GameString& _SmpName)
{
	if (false == IsSampler(_Name))
	{
		MSG_ASSERT_CODE(L"존재하지 않는 샘플러 세팅입니다." + _Name);
	}

	CPtr<GameSampler> Smp = GameSampler::Find(_SmpName);

	if (nullptr == Smp)
	{
		MSG_ASSERT_CODE(L"존재하지 않는 텍스처 를 세팅하려고 했습니다." + _Name);
		return;
	}

	for (auto& _Res : m_Sampler[_Name])
	{
		_Res.m_Res = Smp;
	}
}

void GameRenderPlayer::SetCBuffer(const GameString& _Name, void* _Data, CBUFMODE _Mode)
{
	if (false == IsConBuffer(_Name))
	{
		MSG_ASSERT_CODE(L"존재하지 않는 상수버퍼 세팅입니다." + _Name);
	}

	for (auto& _Res : m_ConBuffer[_Name])
	{
		_Res.m_Mode = _Mode;

		switch (_Mode)
		{
		case CBUFMODE::CB_LINK:
			_Res.m_Value = _Data;
			break;
		case CBUFMODE::CB_NEW:
			_Res.m_Value = new char[_Res.m_Data->Size];
			memcpy_s(_Res.m_Value, _Res.m_Data->Size, _Data, _Res.m_Data->Size);
			break;
		default:
			break;
		}
	}
}

void GameRenderPlayer::SetStructuredBuffer(const GameString& _Name, const CPtr<GameStructuredBuffer>& _Buffer)
{
	if (false == IsStructuredBuffer(_Name))
	{
		MSG_ASSERT_CODE(L"존재하지 않는 스트럭쳐 버퍼 세팅입니다." + _Name);
	}

	if (nullptr == _Buffer)
	{
		MSG_ASSERT_CODE(L"존재하지 않는 스트럭쳐 버퍼를 세팅하려고 했습니다." + _Name);
		return;
	}

	for (auto& _Res : m_StructuredBuffer[_Name])
	{
		_Res.m_Res = _Buffer;
	}
}

bool GameRenderPlayer::IsTexture(const GameString& _Name)
{
	if (m_Texture.end() == m_Texture.find(_Name))
	{
		return false;
	}

	return true;
}

bool GameRenderPlayer::IsSampler(const GameString& _Name)
{
	if (m_Sampler.end() == m_Sampler.find(_Name))
	{
		return false;
	}

	return true;
}

bool GameRenderPlayer::IsConBuffer(const GameString& _Name)
{
	if (m_ConBuffer.end() == m_ConBuffer.find(_Name))
	{
		return false;
	}

	return true;
}


bool GameRenderPlayer::IsStructuredBuffer(const GameString& _Name)
{
	if (m_StructuredBuffer.end() == m_StructuredBuffer.find(_Name))
	{
		return false;
	}

	return true;
}

void GameRenderPlayer::Render()
{
	//DebugCheck();

	for (auto& _ResGroup : m_ConBuffer)
	{
		for (auto& _Res : _ResGroup.second)
		{
			if (_Res.m_Mode == CBUFMODE::CB_NONE)
			{
				MSG_ASSERT_CODE(L"상수버퍼의 값이 세팅이 되지 않았습니다. -> " + _Res.m_Data->Name);
				continue;
			}

			_Res.m_Res->DataChange(_Res.m_Value, (unsigned int)_Res.m_Data->Size);
			_Res.m_Res->Setting(_Res.m_Data->ShaderType, _Res.m_Data->Index);
		}
	}

	for (auto& _ResGroup : m_Texture)
	{
		for (auto& _Res : _ResGroup.second)
		{
			if (nullptr == _Res.m_Res)
			{
				MSG_ASSERT_CODE(L"텍스처를 세팅해주지 않았습니다. -> " + _Res.m_Data->Name);
			}

			_Res.m_Res->Setting(_Res.m_Data->ShaderType, _Res.m_Data->Index);
		}
	}

	for (auto& _ResGroup : m_Sampler)
	{
		for (auto& _Res : _ResGroup.second)
		{
			if (nullptr == _Res.m_Res)
			{
				MSG_ASSERT_CODE(L"샘플러를 세팅해주지 않았습니다. -> " + _Res.m_Data->Name);
			}

			_Res.m_Res->Setting(_Res.m_Data->ShaderType, _Res.m_Data->Index);
		}
	}

	for (auto& _ResGroup : m_StructuredBuffer)
	{
		for (auto& _Res : _ResGroup.second)
		{
			if (nullptr == _Res.m_Res)
			{
				MSG_ASSERT_CODE(L"스트럭처 버퍼를 세팅하지 않았습니다. -> " + _Res.m_Data->Name);
			}

			_Res.m_Res->Setting(_Res.m_Data->ShaderType, _Res.m_Data->Index);
		}
	}

	m_Material->Setting(); 
	m_Mesh->Render();

	GameDevice::MainObj()->Reset();
}

void GameRenderPlayer::Reset()
{
	// 랜더 타겟일 가능성 
	for (auto& _ResGroup : m_Texture)
	{
		for (auto& _Res : _ResGroup.second)
		{
			if (nullptr == _Res.m_Res)
			{
				MSG_ASSERT_CODE(L"텍스처를 세팅해주지 않았습니다. -> " + _Res.m_Data->Name);
			}

			_Res.m_Res->Reset(_Res.m_Data->ShaderType, _Res.m_Data->Index);
		}
	}
}

GameRenderPlayer::GameRenderPlayer()
{
}

GameRenderPlayer::~GameRenderPlayer()
{
}
