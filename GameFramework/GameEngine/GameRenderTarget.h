#pragma once
#include <vector>
#include "GameDevice.h"
#include "GameRenderer.h"

struct MergeOption
{
	float AlphaOption;
	float Dummy00;
	float Dummy01;
	float Dummy02;
}; 

class GameTexture;
class GameRenderTarget : public GameObjTFuncMgr<GameRenderTarget>
{
public:
	friend GameDevice;

private:
	static void Init();

private:
	static GameRenderPlayer TargetMergePlayer;
	static GameRenderPlayer TargetPlusPlayer;

private:
	std::vector<CPtr<GameTexture>> m_AllTexture;
	std::vector<CVector> m_ClearColor;
	std::vector<D3D11_VIEWPORT> m_VIEWPORT;
	std::vector<bool> m_Clear;
	// T * 
	// ID3D11RenderTargetView**
	// ID3D11RenderTargetView**
	std::vector<ID3D11RenderTargetView*> m_AllRTV;

	CPtr<GameTexture> m_Depth;

	MergeOption Option;

	void CreateViewPort(D3D11_TEXTURE2D_DESC _Desc);

public:
	CPtr<GameTexture> Texture(int _index)
	{
		return m_AllTexture[_index];
	}

	void Clear(bool _IsDepthClear); // 출력 대상이 되는것.
	void Setting(); // 출력 대상이 되는것.


	void Reset(); // 출력 대상이 되는것.


	void CreateDepth(unsigned int _TargetIndex = 0);

	void Setting(int _Index); // 출력 대상이 되는것.

	void Depth(CPtr<GameTexture> _Depth);

	CPtr<GameTexture> Depth();


public:
	// 순수하게 직접 만들때.
	void CreateTarget(CVector _Size, CVector _ClearColor, bool _Clear = true, DXGI_FORMAT _Fmt = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, unsigned int _BindFlag = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE);

	// 백버퍼가 사용.
	void CreateTarget(ID3D11Texture2D* _BackBufferTex, CVector _ClearColor, bool _Clear);

	// 다른 타겟의 타겟을 내것으로 쓸때.
	void CreateTarget(CPtr<GameTexture> _Target, CVector _ClearColor, bool _Clear);

	void Merge(CPtr<GameRenderTarget> _Target, int _ThisIndex = 0, int _OtherIndex = 0, bool _AlphaOption = false);
	void Plus(CPtr<GameRenderTarget> _Target, int _ThisIndex = 0, int _OtherIndex = 0, bool _AlphaOption = false);


public:
	GameRenderTarget();
	~GameRenderTarget();
};

