#pragma once
#include <GameMath.h>
#include <GameString.h>

enum class SAVEMAPDIR
{
	L,
	R,
	T,
	B,
	MAX
};

class EntityData
{
public:
	int Type;
	CVector Pos;
	GameString Name;
};

class SaveMapData
{
public:
	union
	{
		struct
		{
			bool ArrSaveDir[(int)SAVEMAPDIR::MAX];
		};
	};
	CVector ArrSaveMapDir[(int)SAVEMAPDIR::MAX];

	wchar_t BackSprite[256];
};


