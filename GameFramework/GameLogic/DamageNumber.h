#pragma once
#include "GameUnity.h"

class DamageNumber : public ActorComponent
{
	std::vector<CPtr<GameSpriteRenderer>> m_RenderList;
	GameString m_Name;
	CVector m_Size;
	int m_Count;
	int m_MaxValue;
	int m_Order;
	int m_Value;

public:
	void SetValue(int Value);
	void SetColor(CVector Color);

public:
	void Init(int Order = 0);
	void Setting(GameString Name, CVector Size, int Count, int MaxValue);

public:
	DamageNumber();
	~DamageNumber();

};