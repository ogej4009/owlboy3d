#pragma once
#include "GameTexture.h"

class GameSprite : public GameObjTFuncMgr<GameSprite>
{
public:
	static CPtr<GameSprite> Create(const GameString& _Name, unsigned int _X, unsigned int _Y)
	{
		/*
			이름을 만든다.
			텍스처가 없으면 스프라이트는 만들 수 없다.
		*/
		CPtr<GameSprite> Res = CreateAndInsert(_Name);
		Res->m_Tex = GameTexture::Find(_Name);
		if (nullptr == Res->m_Tex)
		{
			MSG_ASSERT_CODE(L"존재하지 않는 텍스처에서 스프라이트를 만들어 내려고 했습니다");
		}
		Res->Create(_X, _Y);
		return Res;
	}

	static CPtr<GameSprite> Create(const GameString& _TexName, const GameString& _SpriteName, unsigned int _X, unsigned int _Y)
	{
		CPtr<GameSprite> Res = CreateAndInsert(_SpriteName);
		Res->m_Tex = GameTexture::Find(_TexName);
		if (nullptr == Res->m_Tex)
		{
			MSG_ASSERT_CODE(L"존재하지 않는 텍스처에서 스프라이트를 만들어 내려고 했습니다");
		}
		Res->Create(_X, _Y);
		return Res;
	}

private:
	/* 	텍스처를 알고 있다. */
	CPtr<GameTexture>		m_Tex;
	std::vector<CVector>	m_SpriteData;

private:
	void Create(unsigned int _X, unsigned int _Y);

public:
	size_t Count()
	{
		return m_SpriteData.size();
	}

public:
	CPtr<GameTexture> Tex()
	{
		return m_Tex;
	}

	CVector SpriteData(unsigned int _Index)
	{
		if (m_SpriteData.size() <= _Index)
		{
			MSG_ASSERT_CODE(L"존재하지 않는 스프라이트의 인덱스를 입력했습니다.");
		}
		return m_SpriteData[_Index];
	}

};