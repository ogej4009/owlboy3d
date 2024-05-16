#include "ValueData.h"
#include <GameMath.h>

CVector ValueData::CAM_DEF_POS = { 0.0f, 0.0f, -9.9f };

float ValueData::PIXEL_RATIO;
float ValueData::PIXEL_SCALE;
GameString ValueData::STAGE_NAME;
CVector ValueData::STAGE_SCALE;
CVector ValueData::PLAYER_DEFAULT_POS_INSTAGE;
float ValueData::PLAYER_DEFAULT_Z_ORDER = -7.0f;//8.0f;
float ValueData::DEBUG_DEFAULT_Z_ORDER = 16.0f;

bool OverCheck(CVector Pos)
{
	/*if (Pos.X < 0 || Pos.X >= MAPCOUNT_X ||
		Pos.Y < 0 || Pos.Y >= MAPCOUNT_Y)
	{
		return true;
	}*/

	return false;
}
