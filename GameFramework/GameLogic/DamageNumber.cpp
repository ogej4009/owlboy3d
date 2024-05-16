#include "DamageNumber.h"
#include "ValueData.h"
#include "EnumData.h"

void DamageNumber::SetValue(int Value)
{
	if (m_MaxValue <= Value)
	{
		Value = m_MaxValue;
	}

	GameString Str = GameString::IntToString(Value);

	for (int i = 0; i < (int)Str.StrCount(); i++)
	{
		wchar_t Value = Str.At(i);
		int Number = Value - L'0';
		m_RenderList[i]->SetSprite(m_Name, Number);
	}
}

void DamageNumber::SetColor(CVector _Color)
{
	/* Ŭ���̾�Ʈ�� ���� */
	// ���� ����ϰ�, �����ϴ°�? = ���� ���� �� �ƴ� ��? 
	// ���ڸ� ���� �� �ƴ°�? ���� ������ �ִ°�?
	for (size_t i = 0; i < m_RenderList.size(); i++)
	{
		m_RenderList[i]->SetColor(_Color);
	}
}

void DamageNumber::Init(int Order)
{
	Order = Order;
}

void DamageNumber::Setting(GameString Name, CVector Size, int Count, int MaxValue)
{
	m_Value = 0;
	m_Name = Name;
	m_Size = Size;
	m_Count = Count;
	MaxValue = MaxValue;

	/* Ŭ���̾�Ʈ�� ���� */
	// �� ���� ��Ȳ�� �ϼ��ϸ�, �״����� �����̴�.

	float StartX = m_Size.X * m_Count;
	StartX = -(StartX / 2.0f);
	StartX += m_Size.HX();

	for (size_t i = 0; i < m_Count; i++)
	{
		CPtr<GameSpriteRenderer> Render = GetActor()->CreateCom<GameSpriteRenderer>(m_Order);
		Render->SetLScale(m_Size);
		Render->SetLPos({ StartX + (m_Size.X * i), 0.0f, 0.0f });
		Render->SetSprite(m_Name, 0);
		m_RenderList.push_back(Render);	// vector�� push_back()
	}
}

DamageNumber::DamageNumber()
{
}

DamageNumber::~DamageNumber()
{
}
