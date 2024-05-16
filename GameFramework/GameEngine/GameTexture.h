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
	DirectX::ScratchImage m_Img; 		// ���̺귯������ �������ִ� ����ü
	D3D11_TEXTURE2D_DESC Desc;			// �ؽ�ó ����
	ID3D11Resource* m_pTex;				// �ؽ�ó �޸� ����
	ID3D11RenderTargetView* m_RTV;		// �ؽ�ó ����Ÿ�� ����
	ID3D11DepthStencilView* m_DSV;		// �ؽ�ó ����Ÿ�� ����

	// �� ������ �̿��ؼ� �־���� �Ѵ�.
	ID3D11ShaderResourceView* m_SRV;	// �ؽ�ó ���̴� ���� ����

public:
	CVector Size();
	CVector GetPixel(CVector _Pos);

#pragma region ��ȭ������
	/*
		�������ٽ� ���� ���ҽ��� ����̽��� �ִ�.
		����۵� �ؽ��Ĵ�. �׷��� ������ ����̽����� �����ִ�.
		�̹����� �ε��ص� �� �ؽ��ĵ� ���ο� ��ȭ���̴�.
		�Ȱ��� ȭ�鿡 �Ѹ���.
		�ε��ؼ� �ȼ����̴��� ������.
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