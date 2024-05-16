#pragma once
#include "GameTransform.h"
#include "GameMaterial.h"
#include "GameMath.h"
#include "GameConstantBuffer.h"
#include "GameTexture.h"
#include "GameSampler.h"
#include "Vtx.h"// Ãß°¡ 
#include "GameStructuredBuffer.h"
#include <set>

class ConBufferData
{
public:
	friend class GameRenderPlayer;
	friend class GameRenderer;

public:
	CBUFMODE m_Mode;
	const ShaderData* m_Data;
	CPtr<GameConstantBuffer> m_Res;
	void* m_Value;

public:
	ConBufferData() {}
	~ConBufferData()
	{
		if (nullptr != m_Value && m_Mode == CBUFMODE::CB_NEW)
		{
			delete[] m_Value;
		}
	}

};

class TextureData
{
public:
	friend class GameRenderPlayer;
	friend class GameRenderer;

public:
	const ShaderData* m_Data;
	CPtr<GameTexture> m_Res;
	bool IsOption;
};

class SamplerData
{
public:
	friend class GameRenderPlayer;
	friend class GameRenderer;

public:
	const ShaderData* m_Data;
	CPtr<GameSampler> m_Res;
};


class StructuredBufferData
{
public:
	friend class XRenderPlayer;
	friend class XRender;
public:
	const ShaderData* m_Data;
	CPtr<GameStructuredBuffer> m_Res;
};


#define BOOLTOINT(NAME)  \
public: \
	bool NAME; \
private: \
	bool NAME##Temp##[3]; \

class RenderPlayerOption
{
public:
	BOOLTOINT(IsDifTexture);
	BOOLTOINT(IsNormalTexture);
	BOOLTOINT(IsShadow);
	BOOLTOINT(IsAni);
	BOOLTOINT(IsDummy0);
	BOOLTOINT(IsDummy1);
	BOOLTOINT(IsDummy2);
	BOOLTOINT(IsDummy3);

public:
	float4 BasicColor;

public:
	RenderPlayerOption()
	{
		IsDifTexture = false;
		IsNormalTexture = false;
		IsAni = false;
		IsShadow = false;
		BasicColor = CVector::WHITE;
	}
};



class GameMesh;
class GameMaterial;
class GameRenderer;
class GameRenderPlayer : public CRef, public GameVirtualProgress
{
	friend GameRenderer;

public:
	GameRenderer* m_Parent;
	RenderPlayerOption	m_RenderOption;

public:
	CPtr<GameMesh> m_Mesh;
	CPtr<GameMaterial> m_Material;
	std::map<GameString, std::vector<ConBufferData>> m_ConBuffer;
	std::map<GameString, std::vector<TextureData>> m_Texture;
	std::map<GameString, std::vector<SamplerData>> m_Sampler;
	std::map<GameString, std::vector<StructuredBufferData>> m_StructuredBuffer;

public:
	std::list<TextureData*> AllTexData(const GameString& _SetterName);

public:
	CPtr<GameMesh> GetMesh();
	CPtr<GameMaterial> GetMaterial();

	void SetMesh(const CPtr<GameMesh>& _Mesh);
	void SetMesh(const GameString& _Name);
	void SetMaterial(const GameString& _Name, bool _Push = true);

	CPtr<GameTexture> GetTexture(const GameString& _Name);
	void SetTexture(const GameString& _Name, const CPtr<GameTexture>& _Tex);
	void SetTexture(const GameString& _Name, const GameString& _TexName);
	void SetSampler(const GameString& _Name, const GameString& _SmpName);
	void SetCBuffer(const GameString& _Name, void* _Data, CBUFMODE _Mode);
	void SetStructuredBuffer(const GameString& _Name, const CPtr<GameStructuredBuffer>& _Buffer);

	bool IsTexture(const GameString& _Name);
	bool IsSampler(const GameString& _Name);
	bool IsConBuffer(const GameString& _Name);
	bool IsStructuredBuffer(const GameString& _Name);

public:
	void Render();
	void Reset();

public:
	GameRenderPlayer();
	~GameRenderPlayer();
};




class GameMaterial;
class GameMesh;
class GameCamera;
class GameSprite;
class GameRenderer : public GameTransform
{
public:
	std::vector<CPtr<GameRenderPlayer>> m_PlayerList;
	std::vector<CPtr<GameRenderPlayer>> m_DeferredList;
	std::vector<CPtr<GameRenderPlayer>> m_ForwardList;
	std::vector<CPtr<GameRenderPlayer>> m_ShadowList;

public:
	CPtr<GameRenderPlayer> CreateRenderPlayer(const CPtr<GameMesh>& _Mesh, const GameString& _Mat);
	CPtr<GameRenderPlayer> CreateRenderPlayer(const GameString& _Mesh, const GameString& _Mat);
	CPtr<GameRenderPlayer> CreateRenderPlayer(const CPtr<GameMesh>& _Mesh);
	CPtr<GameRenderPlayer> GetRenderPlayer(int _Index);

public:  
	void SetTexture(const GameString& _Name, const CPtr<GameTexture>& _Res);
	void SetTexture(const GameString& _Name, const GameString& _ResName);
	void SetCBuffer(const GameString& _Name, void* _Data, CBUFMODE _Mode = CBUFMODE::CB_LINK);
	void SetSampler(const GameString& _Name, const GameString& _ResName);

public:
	void Init(int _Order = 0);
	void Init(const GameString& _Mesh, const GameString& _Mat, int _Order = 0);
	void Init(const CPtr<GameMesh>& _Mesh, const GameString& _Mat, int _Order = 0);

	virtual void Render(CPtr<GameCamera> _CAM);

	virtual void DeferredRender(CPtr<GameCamera> _Cam);
	virtual void ForwardRender(CPtr<GameCamera> _Cam);
	virtual void ShadowRender(const LightData& _Data);

	//std::vector<CPtr<GameRenderPlayer>> CreateRenderPlayerToFbxEx(const GameString& _FbxExName, const GameString& _MatName, int DrawSet = 0);
	//CPtr<GameRenderPlayer> CreateRenderPlayerToFbxPartEx(const GameString& _FbxExName, const GameString& _MatName, int _DrawSet, int _SubIndex, int _MainIndex);
	//std::vector<CPtr<GameRenderPlayer>> CreateRenderPlayerToFbx(const GameString& _FbxName, const GameString& _MatName, const XStGameStringring& _SmpName);
	//std::vector<CPtr<GameRenderPlayer>> CreateRenderPlayerToFbxNoneMat(const GameString& _FbxName);

public:
	void ShadowOn();

public:
	GameRenderer();
	~GameRenderer();
};

