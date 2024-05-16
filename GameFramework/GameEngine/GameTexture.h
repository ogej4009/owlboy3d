#pragma once
#include "GameShader.h"
#include <GameObjTFuncMgr.h>
#include <CPtr.h>
#include <DirectXTex-main/DirectXTex/DirectXTex.h>

#pragma comment(lib, "DirectXTex.lib")

class GameTexture : public GameFileMgr<GameTexture>
{
public:
	// File
	static CPtr<GameTexture> Load(const GameFile& _File)
	{
		CPtr<GameTexture> Res = CreateAndInsertToFile(_File.FullPath());
		Res->Load();
		return Res;
	}

	// Path 
	static CPtr<GameTexture> Load(const GameString& _Path)
	{
		CPtr<GameTexture> Res = CreateAndInsertToFile(_Path);
		Res->Load();
		return Res;
	}

private:
	DirectX::ScratchImage m_Img; 		// 라이브러리에서 지원해주는 구조체
	D3D11_TEXTURE2D_DESC Desc;			// 텍스처 정보
	ID3D11Resource* m_pTex;				// 텍스처 메모리 권한
	ID3D11RenderTargetView* m_RTV;		// 텍스처 랜더타겟 권한
	ID3D11DepthStencilView* m_DSV;		// 텍스처 깊이타겟 권한

	// 이 권한을 이용해서 넣어줘야 한다.
	ID3D11ShaderResourceView* m_SRV;	// 텍스처 쉐이더 세팅 권한

public:
	CVector Size();
	CVector GetPixel(CVector _Pos);

#pragma region 도화지개념
	/*
		뎁스스텐실 등의 리소스는 디바이스에 있다.
		백버퍼도 텍스쳐다. 그렇기 때문에 디바이스에서 쓰고있다.
		이미지를 로딩해도 그 텍스쳐도 새로운 도화지이다.
		똑같이 화면에 뿌린다.
		로드해서 픽셀쉐이더에 잡힌다.
	*/
#pragma endregion

public:
	const D3D11_TEXTURE2D_DESC& TextDesc()
	{
		return Desc;
	}

public:
	ID3D11DepthStencilView* DSV() 
	{
		return m_DSV;
	}

	ID3D11RenderTargetView* RTV()
	{
		return m_RTV;
	}


	void Create(CVector _Size, DXGI_FORMAT _Fmt, UINT _BindFlag, D3D11_USAGE _eUsage);
	void Create(D3D11_TEXTURE2D_DESC _Desc);
	void Create(ID3D11Texture2D* _BackBufferTex);

public:
	void Load();
	void Setting(SHADERTYPE _Type, unsigned int _Reg);
	void Reset(SHADERTYPE _Type, unsigned int _Reg);
	void SetPixel(void* _PixelData, int Size);
	float4 GetPixel(int2 _Pos);
	void SettingData();


public:
	GameTexture();
	~GameTexture();
};