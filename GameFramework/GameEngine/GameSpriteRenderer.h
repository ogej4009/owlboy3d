#pragma once
#include "GameRenderer.h"
#include "GameSprite.h"

class GameSpriteRenderer : public GameRenderer
{
private:
	CPtr<GameSprite> m_Sprite;
	CVector m_SprCutData;
	CVector m_SprDrawColor;
	unsigned int m_SprIndex;
	int m_SprRenderOption[4];
	CVector m_SprScale;

	GameString m_VSShaderName;
	GameString m_SprName;
	
	CPtr<GameRenderer> m_SprParent;
	std::vector<CPtr<GameRenderPlayer>> m_SprRp;

public:
	void SetNullSprite()
	{
		m_Sprite = nullptr;
	}

	void VSShaderName(GameString _VSShaderName)
	{
		m_VSShaderName = _VSShaderName;
	}

	GameString GetSprName()
	{
		return m_SprName;
	}

	void SetSprite(const GameString& _Name, unsigned int _SpriteIndex = 0)
	{
		m_Sprite = GameSprite::Find(_Name);
		m_SprName = _Name;
		SpriteIndex(_SpriteIndex);
	}

	CPtr<GameSprite> GetSprite()
	{
		return  m_Sprite;
	}

	void SpriteIndex(unsigned int _SpriteIndex)
	{
		m_SprIndex = _SpriteIndex;
	}

	void SpriteIndexPlus(unsigned int _SpriteIndex)
	{
		m_SprIndex += _SpriteIndex;
	}

	void SpriteIndexMinus(unsigned int _SpriteIndex)
	{
		m_SprIndex -= _SpriteIndex;
	}

	void ColorMode(unsigned int _SpriteIndex)
	{
		m_SprRenderOption[0] = _SpriteIndex;
	}

	void SetCutData(CVector _CutData)
	{
		m_SprCutData = _CutData;
	}

	int ColorMode()
	{
		return m_SprRenderOption[0];
	}

	void SetAlpha(float _Alpha)
	{
		m_SprDrawColor.W = _Alpha;
	}

	float GetAlpha()
	{
		return m_SprDrawColor.W;
	}

	void SetPlusAlpha(float _Alpha)
	{
		m_SprDrawColor.W += _Alpha;
	}

	void SetMinusAlpha(float _Alpha)
	{
		m_SprDrawColor.W -= _Alpha;
	}

	void SetColor(CVector _Color)
	{
		m_SprDrawColor = _Color;
	}

	void SetScale(CVector _Scale)
	{
		m_SprScale.X = _Scale.X;
		m_SprScale.Y = _Scale.Y;
		m_SprScale.Z = 1.0f;
	}

public:
	void Init() override;
	void Init(int Order = 0);
	void Init(const GameString& Name, int Order);
	void Update() override;
	void Render(CPtr<GameCamera> _Cam) override;
	void RenderUpdate(CPtr<GameCamera> _Cam) override;

public:
	GameSpriteRenderer();
	~GameSpriteRenderer();

};