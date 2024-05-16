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
		// 릴리즈를 위해 소멸자만 cpp로
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

	// 글자크기를 특정하고 매쉬를 만들수 없기 대문에.
// 지오메트릭 쉐이더를 쓴다. 
// 기본적으로 윈도우 좌표계를 기반으로 하는 함수를 쓸것이다. 

public:
	void CreateGameFont(const GameString& _Name);

public:
	GameFont();
	~GameFont();
};

#pragma region 
/*
	DrawFont()
	폰트에 있어서 글자 크기를 특정하고 매쉬를 만들수 없기 때문에 지오메트릭 쉐이더를 쓴다.
	윈도우 좌표계를 기반으로 하는 함수를 쓴다.
*/
#pragma endregion