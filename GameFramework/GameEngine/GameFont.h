#pragma once
#include <GameObjTFuncMgr.h>
#include "GameDevBuffer.h"
#include <CPtr.h>
#include <FW1FontWrapper-master/FW1FontWrapper/Source/FW1FontWrapper.h>

#pragma comment(lib, "FW1FontWrapper.lib")

class GameFont : public GameObjTFuncMgr<GameFont>
{
public:
	static void Create(const GameString& _Name)
	{
		CPtr<GameFont> Res = CreateAndInsert(_Name);
		Res->CreateGameFont(_Name);
	}

private:
	class GameFontStarter
	{
	public:
		~GameFontStarter();
		// ����� ���� �Ҹ��ڸ� cpp��
	};
	friend GameFontStarter;
	static GameFontStarter Starter;

public:
	static void FontInit();

private:
	static IFW1Factory* m_pFontFactory;
	IFW1FontWrapper* m_pFontWrapper;

public:
	void DrawFont(const GameString& _Text,
		float _Size,
		CVector _Pos,
		CVector _Color,
		FW1_TEXT_FLAG _Flag = FW1_TOP);

	// ����ũ�⸦ Ư���ϰ� �Ž��� ����� ���� �빮��.
// ������Ʈ�� ���̴��� ����. 
// �⺻������ ������ ��ǥ�踦 ������� �ϴ� �Լ��� �����̴�. 

public:
	void CreateGameFont(const GameString& _Name);

public:
	GameFont();
	~GameFont();
};

#pragma region 
/*
	DrawFont()
	��Ʈ�� �־ ���� ũ�⸦ Ư���ϰ� �Ž��� ����� ���� ������ ������Ʈ�� ���̴��� ����.
	������ ��ǥ�踦 ������� �ϴ� �Լ��� ����.
*/
#pragma endregion