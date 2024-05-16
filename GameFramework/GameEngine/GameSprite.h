#pragma once
#include "GameTexture.h"

class GameSprite : public GameObjTFuncMgr<GameSprite>
{
public:
	static CPtr<GameSprite> Create(const GameString& _Name, unsigned int _X, unsigned int _Y)
	{
		/*
			�̸��� �����.
			�ؽ�ó�� ������ ��������Ʈ�� ���� �� ����.
		*/
		CPtr<GameSprite> Res = CreateAndInsert(_Name);
		Res->m_Tex = GameTexture::Find(_Name);
		if (nullptr == Res->m_Tex)
		{
			MSG_ASSERT_CODE(L"�������� �ʴ� �ؽ�ó���� ��������Ʈ�� ����� ������ �߽��ϴ�");
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
			MSG_ASSERT_CODE(L"�������� �ʴ� �ؽ�ó���� ��������Ʈ�� ����� ������ �߽��ϴ�");
		}
		Res->Create(_X, _Y);
		return Res;
	}

private:
	/* 	�ؽ�ó�� �˰� �ִ�. */
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
			MSG_ASSERT_CODE(L"�������� �ʴ� ��������Ʈ�� �ε����� �Է��߽��ϴ�.");
		}
		return m_SpriteData[_Index];
	}

};