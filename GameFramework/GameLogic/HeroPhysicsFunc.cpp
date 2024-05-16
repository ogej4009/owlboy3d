#include "Hero.h"
#include "ValueData.h"
#include "EnumData.h"



void Hero::ChkFly()
{

	while (false == m_DirColorSensor[(unsigned int)DIR_STATE::DIRD])
	{
		GetTrans()->WMove({ 0.0f, 0.001f, 0.0f });
		ColLevelBlock();

		if (true == m_DirColorSensor[(unsigned int)DIR_STATE::DIRD])
		{
			GetTrans()->WMove({ 0.0f, -0.001f, 0.0f });
			if (true == m_bLand)
			{
				ChangeState(HEROSTATE::STAND);
				m_bLand = false;
			}
			break;
		}
	}

	while (false == m_DirColorSensor[(unsigned int)DIR_STATE::DIRU])
	{
		GetTrans()->WMove({ 0.0f, -0.001f, 0.0f });
		ColLevelBlock();

		if (true == m_DirColorSensor[(unsigned int)DIR_STATE::DIRU])
		{
			GetTrans()->WMove({ 0.0f, 0.001f, 0.0f });
			break;
		}
	}

	while (false == m_DirColorSensor[(unsigned int)DIR_STATE::DIRR])
	{
		GetTrans()->WMove({ -0.001f, 0.0f, 0.0f });
		ColLevelBlock();

		if (true == m_DirColorSensor[(unsigned int)DIR_STATE::DIRR])
		{
			GetTrans()->WMove({ 0.001f, 0.0f, 0.0f });
			break;
		}
	}

	while (false == m_DirColorSensor[(unsigned int)DIR_STATE::DIRL])
	{
		GetTrans()->WMove({ 0.001f, 0.0f, 0.0f });
		ColLevelBlock();

		if (true == m_DirColorSensor[(unsigned int)DIR_STATE::DIRL])
		{
			GetTrans()->WMove({ -0.001f, 0.0f, 0.0f });
			break;
		}
	}

}

void Hero::ChkBlock()
{

	if (true == m_DirColorSensor[(unsigned int)DIR_STATE::DIRD])
	{
		GetTrans()->WMove(GetTrans()->WDown() * GameTime::DeltaTime(m_Gravity));
	}

	while (false == m_DirColorSensor[(unsigned int)DIR_STATE::DIRD])
	{
		GetTrans()->WMove({ 0.0f, 0.001f, 0.0f });
		ColLevelBlock();

		if (true == m_DirColorSensor[(unsigned int)DIR_STATE::DIRD])
		{
			GetTrans()->WMove({ 0.0f, -0.001f, 0.0f });
			if (true == m_bLand)
			{
				ChangeState(HEROSTATE::STAND);
				m_bLand = false;
			}
			break;
		}

	}


	// 어떤 경우 동작 안함 (선택적인 블록킹)을 위한 것   
	if (m_bBlock == true)
	{
		while (false == m_DirColorSensor[(unsigned int)DIR_STATE::DIRR])
		{
			GetTrans()->WMove({ -0.001f, 0.0f, 0.0f });
			ColLevelBlock();

			if (true == m_DirColorSensor[(unsigned int)DIR_STATE::DIRR])
			{
				GetTrans()->WMove({ 0.001f, 0.0f, 0.0f });
				break;
			}
		}

		while (false == m_DirColorSensor[(unsigned int)DIR_STATE::DIRL])
		{
			GetTrans()->WMove({ 0.001f, 0.0f, 0.0f });
			ColLevelBlock();

			if (true == m_DirColorSensor[(unsigned int)DIR_STATE::DIRL])
			{
				GetTrans()->WMove({ -0.001f, 0.0f, 0.0f });
				break;
			}
		}
	}

}