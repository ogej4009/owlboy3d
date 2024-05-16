#include "GameMath.h"

const float GameMath::PI = 3.14159265358979323846264338f;
const float GameMath::PI2 = 3.14159265358979323846264338f * 2;
const float GameMath::DTOR = GameMath::PI / 180.0f;
const float GameMath::RTOD = 180.0f / GameMath::PI;

const CVector CVector::RIGHT = { 1.0f, 0.0f };
const CVector CVector::LEFT = { -1.0f, 0.0f };
const CVector CVector::UP = { 0.0f, 1.0f };
const CVector CVector::DOWN = { 0.0f, -1.0f, 0.0f, 1.0f };
const CVector CVector::FORWARD = { 0.0f, 0.0f, 1.0f };
const CVector CVector::BACK = { 0.0f, 0.0f, -1.0f };

const CVector CVector::RED = { 1.0f, 0.0f, 0.0f, 1.0f };
const CVector CVector::GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
const CVector CVector::BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };

const CVector CVector::BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
const CVector CVector::WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };

const CVector CVector::MAGENTA = { 1.0f, 0.0f, 1.0f, 1.0f };
//const CVector CVector::PURPLE = { 0.0f, 1.0f, 1.0f, 1.0f };
//const CVector CVector::MARKER = { 1.0f, 1.0f, 0.0f, 1.0f };
//const CVector CVector::MARKER = { 1.0f, 1.0f, 0.0f, 1.0f };

const CVector CVector::NONE = { 0.0f, 0.0f, 0.0f, 0.0f };
const CVector CVector::ZERO = { 0.0f, 0.0f, 0.0f, 1.0f };
const CVector CVector::ONE = { 1.0f, 1.0f, 1.0f, 1.0f };


int GameMath::RandomInt(int _Min, int _Max)
{
	static std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(_Min, _Max);
	return dis(gen);
}


float GameMath::RandomFloat(float _Min, float _Max)
{
	static std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(_Min, _Max);
	return dis(gen);
}

CVector& CVector::operator*=(const CMatrix& _Value)
{
#pragma region 반복문으로 행렬만들기 
	/*
		for (size_t x = 0; x < 4; x++)
		{
			NewResult.Arr2D[0][x] = 0.0f;
			for (size_t CalCount = 0; CalCount < 4; CalCount++)
			{
				NewResult.Arr2D[0][x] += Arr2D[0][CalCount] * _Value.ArrF2D[CalCount][x];
			}
		}
		*this = NewResult;
	*/
#pragma endregion

	CVector NewResult;
	DXVEC = DirectX::XMVector4Transform(DXVEC, _Value);
	return *this;
}


CVector CVector::operator*(const CMatrix& _Value)
{
	CVector NewResult;

	for (size_t x = 0; x < 4; x++)
	{
		NewResult.Arr2D[0][x] = 0.0f;

		for (size_t CalCount = 0; CalCount < 4; CalCount++)
		{
			NewResult.Arr2D[0][x] += Arr2D[0][CalCount] * _Value.Arr2D[CalCount][x];
		}
	}

	return NewResult;
}


CVector CVector::MatrixToQuaternion(const CMatrix& M)
{
    CVector Return;

    if (M.ArrV[0].IsNearlyZero() || M.ArrV[1].IsNearlyZero() || M.ArrV[2].IsNearlyZero())
    {
        Return.X = 0.0f;
        Return.Y = 0.0f;
        Return.Z = 0.0f;
        Return.W = 1.0f;
        return Return;
    }

    float s;

    const float tr = M.Arr2D[0][0] + M.Arr2D[1][1] + M.Arr2D[2][2];

    if (tr > 0.0f)
    {
        float InvS = InvSqrt(tr + 1.f);
        Return.W = 0.5f * (1.f / InvS);
        s = 0.5f * InvS;

        Return.X = (M.Arr2D[1][2] - M.Arr2D[2][1]) * s;
        Return.Y = (M.Arr2D[2][0] - M.Arr2D[0][2]) * s;
        Return.Z = (M.Arr2D[0][1] - M.Arr2D[1][0]) * s;
    }
    else
    {
        int i = 0;

        if (M.Arr2D[1][1] > M.Arr2D[0][0])
            i = 1;

        if (M.Arr2D[2][2] > M.Arr2D[i][i])
            i = 2;

        static const int nxt[3] = { 1, 2, 0 };
        const int j = nxt[i];
        const int k = nxt[j];

        s = M.Arr2D[i][i] - M.Arr2D[j][j] - M.Arr2D[k][k] + 1.0f;

        float InvS = InvSqrt(s);

        float qt[4];
        qt[i] = 0.5f * (1.f / InvS);

        s = 0.5f * InvS;

        qt[3] = (M.Arr2D[j][k] - M.Arr2D[k][j]) * s;
        qt[j] = (M.Arr2D[i][j] + M.Arr2D[j][i]) * s;
        qt[k] = (M.Arr2D[i][k] + M.Arr2D[k][i]) * s;

        Return.X = qt[0];
        Return.Y = qt[1];
        Return.Z = qt[2];
        Return.W = qt[3];
    }

    return Return;
}
