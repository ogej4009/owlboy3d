#include "Hero.h"
#include "ValueData.h"
#include "EnumData.h"

void Hero::ColLevelBlock()
{
	ValueData::PIXEL_SCALE = 0.01f;
	ValueData::PIXEL_RATIO = 1.0f / ValueData::PIXEL_SCALE;

	CPtr<GameTexture> CTex = GameTexture::Find(ValueData::STAGE_NAME);
	 
	for (size_t i = 0; i < 4; i++)
	{
		// 데스 
		// 보라 

		m_bArrColorSensorMagenta[i] = false;
		m_bArrColorSensorBlack[i] = false;
		m_bArrColorSensorBlue[i] = false;
		m_bArrColorSensorRed[i] = false;
		m_bArrColorSensorMarker[i] = false;
		m_bArrColorSensorPurple[i] = false;

		CVector CPos = GetTrans()->GetWPos();

		CPos += m_DirFrameSensor[i];
		CPos.Y *= -1.0f;
		CPos *= ValueData::PIXEL_RATIO;

		CVector Color = CTex->GetPixel(CPos);

		if (Color != CVector::MAGENTA)
		{
			m_bArrColorSensorMagenta[i] = true;
		}

		if (Color != CVector::BLUE)
		{
			m_bArrColorSensorBlue[i] = true;
		}

		if (Color != CVector::RED)
		{
			m_bArrColorSensorRed[i] = true;
		}

		if (Color != CVector::BLACK)
		{
			m_bArrColorSensorBlack[i] = true;
		}

	}

	for (size_t i = 0; i < 4; i++)
	{
		CVector CPos = GetTrans()->GetWPos();

		CPos += m_DirFrameSensor[i];
		CPos.Y *= -1.0f;
		CPos *= ValueData::PIXEL_RATIO;

		CVector Color = CTex->GetPixel(CPos);

		if (Color != CVector::MAGENTA)
		{
			m_DirColorSensor[i] = true;
		}

	}

}