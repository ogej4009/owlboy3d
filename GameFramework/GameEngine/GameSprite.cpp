#include "GameSprite.h"

void GameSprite::Create(unsigned int _X, unsigned int _Y)
{
	//              XStart  YStart   X������     Y������
	CVector Data = { 0,    0,    1.0f / _X, 1.0f / _Y };

	for (size_t y = 0; y < _Y; y++)
	{
		for (size_t x = 0; x < _X; x++)
		{
			// ���̴������� ����
			// XStart     XSize
			Data.X = Data.Z * x;
			// YStart     YSize
			Data.Y = Data.W * y;
			m_SpriteData.push_back(Data);
		}
	}
}
