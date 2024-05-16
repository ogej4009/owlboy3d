#pragma once
#include <crtdbg.h>
#include <assert.h>
#include <Windows.h>
#include <math.h>
#include <iostream>
#include <random>

#include <DirectXTK-main/Inc/SimpleMath.h>
#include <DirectXTK-main/Inc/SimpleMath.inl>

#pragma region 인터페이스-SIMD연산함수,DIRECTX함수,쉐이더함수
/*
	SIMD연산은 대략 float 4개를 한꺼번에 곱하거나 더한다는 개념이다.
	DirectX에서 지원하는 함수들이 SIMD 연산을 지원한다.
	#include <DirectXPackedVector.h>	-> SIMD 연산이 적용된 벡터용 함수를 적용한 헤더.
	#include <d3d11_4.h>				-> DirectX 디바이스용 함수들이 들어있는 헤더
	#include <d3dcompiler.h>			-> 쉐이더컴파일 함수
*/
#pragma endregion

#include <DirectXCollision.h>
#include <DirectXCollision.inl>
#include <DirectXPackedVector.h>	
#include <d3d11_4.h>				
#include <d3dcompiler.h>			

/* 	DX LIB 내장  */
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

#ifdef _DEBUG
#define MATHMSG(MESSAGE) _wassert(MESSAGE, _CRT_WIDE(__FILE__), (unsigned)(__LINE__))
#else
#define MATHMSG(_MESSAGE) assert(false)
#endif

class CMatrix;
class GameMath
{
public:
	static const float PI;
	static const float DTOR;
	static const float RTOD;
	static const float PI2;
	static const float PI2D1;

public:
	static int RandomInt(int _Min, int _Max);
	static float RandomFloat(float _Min, float _Max);

};

class CVector
{
public:
	const static CVector FORWARD;
	const static CVector BACK;
	const static CVector RIGHT;
	const static CVector LEFT;
	const static CVector UP;
	const static CVector DOWN;

public:
	const static CVector RED;
	const static CVector GREEN;
	const static CVector BLUE;
	const static CVector MAGENTA;
//	const static CVector CYAN;
//	const static CVector YELLOW;
	const static CVector WHITE;
	const static CVector BLACK;

public:
	const static CVector NONE;
	const static CVector ZERO;
	const static CVector ONE;

#pragma region Vector->Scale==0?
	/*
		벡터의 스케일(크기)을 0으로 쓰면 안됨
		이유1. 화면에 안나오는 케이스
		이유2. 나누기 연산이 있는 케이스 ZERO-DIVISION
	*/
#pragma endregion
public:
	void ZEROCHECK() const
	{
		if (X == 0.0F) { MATHMSG(L"X 크기 속성이 0입니다"); }
		if (Y == 0.0F) { MATHMSG(L"Y 크기 속성이 0입니다"); }
		if (Z == 0.0F) { MATHMSG(L"Z 크기 속성이 0입니다"); }
	}

	static CVector MatrixToQuaternion(const CMatrix& _Mat);

	bool IsNearlyZero() const
	{
		// 8.3123162721622e-d
		return fabsf(X) <= 1.e-4f && fabsf(Y) <= 1.e-4f && fabsf(Z) <= 1.e-4f;
	}

	static float Distance(CVector _L, CVector _R)
	{
		float Dis;
		Dis = (float)sqrt((((_L.X - _R.X) * (_L.X - _R.X)) + ((-_L.X + _R.Y) * (-_L.X + _R.Y)) + ((_L.X - _R.Z) * (_L.X - _R.Z))));

		return Dis;
	}


	// 제곱근 뒤집기.
	static float InvSqrt(float f)
	{
		const __m128 fOneHalf = _mm_set_ss(0.5f);
		__m128 Y0, X0, X1, X2, FOver2;
		float temp;

		Y0 = _mm_set_ss(f);
		X0 = _mm_rsqrt_ss(Y0);	// 1/sqrt estimate (12 bits)
		FOver2 = _mm_mul_ss(Y0, fOneHalf);

		// 1st Newton-Raphson iteration
		X1 = _mm_mul_ss(X0, X0);
		X1 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X1));
		X1 = _mm_add_ss(X0, _mm_mul_ss(X0, X1));

		// 2nd Newton-Raphson iteration
		X2 = _mm_mul_ss(X1, X1);
		X2 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X2));
		X2 = _mm_add_ss(X1, _mm_mul_ss(X1, X2));

		_mm_store_ss(&temp, X2);
		return temp;
	}





public:
	/* 벡터로 컬러를 표현하려면 0~1사이의 값을 넣어주세요 */
	static unsigned int ColorToUint(float _R, float _G, float _B, float _A)
	{
		unsigned int uColor = 0;
		__int8* Ptr = (__int8*)&uColor;
		//       0.5 * 255
		Ptr[0] = (__int8)(_R * 255.0f);
		Ptr[1] = (__int8)(_G * 255.0f);
		Ptr[2] = (__int8)(_B * 255.0f);
		Ptr[3] = (__int8)(_A * 255.0f);
		return uColor;
	}

	unsigned int ColorToUint()
	{
		unsigned int uColor = 0;
		__int8* Ptr = (__int8*)&uColor;
		Ptr[0] = (__int8)(R * 255.0f);
		Ptr[1] = (__int8)(G * 255.0f);
		Ptr[2] = (__int8)(B * 255.0f);
		Ptr[3] = (__int8)(A * 255.0f);
		return uColor;
	}

	static unsigned int ColorToUintInt8(unsigned int _R, unsigned int _G, unsigned int _B, unsigned int _A)
	{
		unsigned int uColor = 0;
		__int8* Ptr = (__int8*)&uColor;
		Ptr[0] = (__int8)_R;
		Ptr[1] = (__int8)_G;
		Ptr[2] = (__int8)_B;
		Ptr[3] = (__int8)_A;
		return uColor;
	}

	static CVector ColorToUintInt8(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A)
	{
		unsigned int uColor = 0;
		unsigned char* Ptr = (unsigned char*)&uColor;
		Ptr[0] = _R;
		Ptr[1] = _G;
		Ptr[2] = _B;
		Ptr[3] = _A;
		CVector Color;
		Color = UintToColor(uColor);
		return Color;
	}

	static CVector UintToColor(unsigned int _R)
	{
		CVector vColor;
		unsigned __int8* Ptr = (unsigned __int8*)&_R;
		vColor.X = (float)((float)Ptr[0] / 255.0F);
		vColor.Y = (float)((float)Ptr[1] / 255.0F);
		vColor.Z = (float)((float)Ptr[2] / 255.0F);
		vColor.W = (float)((float)Ptr[3] / 255.0F);
		return vColor;
	}

public:
	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};

		struct
		{
			float R;
			float G;
			float B;
			float A;
		};

		struct
		{
			float Arr[4];
		};

		struct
		{
			float Arr2D[1][4];
		};

		DirectX::XMVECTOR DXVEC;
	};

#pragma region int<->float변환
	/*
		윈도우의 draw() 는 int를 요구하므로 변환함수를 만든다. int <-> float
		실제 위치나 크기는 float로 표현하고, 윈도우의 픽셀단위로 보낼때는 int로 변환한다.
	*/
#pragma endregion

	/* 
	DirectionVector
	WindowPosTo3DPos
	ReversWindowPosTo3DPos

	QToRad
	QToDeg


	*/

	static CVector Lerp(CVector _Start, CVector _End, float _Ratio)
	{
		return DirectX::XMVectorLerp(_Start.DXVEC, _End.DXVEC, _Ratio);
	}

	static CVector QSLerp(CVector _Start, CVector _End, float _Ratio)
	{
		return DirectX::XMQuaternionSlerp(_Start.DXVEC, _End.DXVEC, _Ratio);
	}


	static CVector DirectionVector(const CVector _RotationVector)
	{
		CVector Return;
		//pitch =x;
		//Yaw = y;
		//roll = z;
		Return.X = (float)(-cos(_RotationVector.Y) * sin(_RotationVector.Z) - sin(_RotationVector.Y) * sin(_RotationVector.X) * cos(_RotationVector.Z));
		Return.Y = (float)(sin(_RotationVector.Y) * sin(_RotationVector.Z) - cos(_RotationVector.Y) * sin(_RotationVector.X) * cos(_RotationVector.Z));
		Return.Z = (float)(cos(_RotationVector.X) * cos(_RotationVector.Z));

		return Return.Normal3dVecReturn();
	}

public:
	static CVector WindowPosTo3dPos(CVector _WindowPos, const CVector& _ScreenSize)
	{
		CVector ConPos = _WindowPos;
		ConPos.Y *= -1.0f;
		ConPos += _ScreenSize.HalfVec();
		return ConPos;
	}

	static CVector ReversWindowPosTo3dPos(CVector _WindowPos, const CVector& _ScreenSize)
	{
		CVector ConPos = _WindowPos;
		ConPos.Y *= -1.0f;
		ConPos -= _ScreenSize.HalfVec();
		return ConPos;
	}

	static CVector Cross3d(const CVector& _Left, const CVector& _Right)
	{
		return CVector
		(
			_Left.Y * _Right.Z - _Left.Z * _Right.Y,
			_Left.Z * _Right.X - _Left.X * _Right.Z,
			_Left.X * _Right.Y - _Left.Y * _Right.X
		);
	}

	static float Dot2d(const CVector& _Left, const CVector& _Right)
	{
		return DirectX::XMVector2Dot(_Left, _Right).m128_f32[0];
	}

	static float Dot(const CVector& _Left, const CVector& _Right)
	{
		/* 
		DirectX::XMVECTOR DXVEC = DirectX::XMVector3Dot(_Left.DXVEC, _Right.DXVEC);
		return DXVEC.m128_f32[0];
		*/
		return DirectX::XMVector3Dot(_Left, _Right).m128_f32[0];
	}

	operator DirectX::XMVECTOR() const
	{
		return DXVEC;
	}

	/* float3만을 위한 함수 */
	operator DirectX::XMFLOAT3() const
	{
		return DirectX::XMFLOAT3(X, Y, Z);
	}

	operator DirectX::XMFLOAT4() const
	{
		return DirectX::XMFLOAT4(X, Y, Z, W);
	}

	float Dot(const CVector& _Other)
	{
		return X * _Other.X + Y * _Other.Y + Z * _Other.Z;
	}

	float Dot3D(const CVector& _Other)
	{
		CVector Result = DirectX::XMVector3Dot(DXVEC, _Other);
		return Result.X;
	}

	float Dot4D(const CVector& _Other)
	{
		CVector Result = DirectX::XMVector4Dot(DXVEC, _Other);
		return Result.Y;
	}

	float DirToRadZ()
	{
		CVector Dir = *this;
		Dir.Normalize3d();
		return acosf(Dir.X);
	}

	float DirToDegZ()
	{
		return DirToRadZ() * GameMath::RTOD;
	}

	/* 	각도를 인자로 넣으면 단위벡터를 만들어주는 함수 */
	/*
		CalPos.X = (1 * cosf(_Rad)) ;
		CalPos.Y = (1 * sinf(_Rad)) ;
	*/
	static CVector RadToDirZ(float _Rad)
	{
		return { cosf(_Rad) , sinf(_Rad) };
	}

	int IX() const { return (int)X; }
	int IY() const { return (int)Y; }
	int IZ() const { return (int)Z; }
	int IW() const { return (int)W; }
	//unsigned int UIX() const { return (unsigned int)X; }
	//unsigned int UIY() const { return (unsigned int)Y; }

	int UIY() const { return (unsigned int)Y; }
	int UIZ() const { return (unsigned int)Z; }
	int UIX() const { return (unsigned int)X; }

	/* 나누기보다 곱하기가 연산이 빠르다.  */
	float HX() const { return X * 0.5f; }
	float HY() const { return Y * 0.5f; }

	int HIX() const { return (int)HX(); }
	int HIY() const { return (int)HY(); }

	/* 벡터의 길이구하기 sqrtf((X * X) + (Y * Y) + (Z * Z)) */
	float Length3d() const
	{
		DirectX::XMVECTOR Vec = DirectX::XMVector3Length(DXVEC);
		return Vec.m128_f32[0];
	}

	float Length2d() const
	{
		DirectX::XMVECTOR Vec = DirectX::XMVector2Length(DXVEC);
		return Vec.m128_f32[0];
	}

	CVector HalfVec() const
	{
		CVector HV = *this;
		HV *= 0.5f;
		return HV;
	}

	CVector MulQ(const CVector _Other)
	{
		return DirectX::XMQuaternionMultiply(DXVEC, _Other.DXVEC);
	}

	float fABS(float _Value) const //★
	{
		if (0 > _Value)
		{
			return _Value * -1.0f;
		}
		return _Value;
	}

	CVector AbsVector() const
	{
		CVector Vec = *this;
		Vec.X = (float)abs(Vec.IX());
		Vec.Y = (float)abs(Vec.IY());
		Vec.Z = (float)abs(Vec.IZ());
		return Vec;
	}

	CVector DegToQ() const
	{
		CVector Vector = *this;
		Vector *= GameMath::DTOR;
		return DirectX::XMQuaternionRotationRollPitchYaw(Vector.X, Vector.Y, Vector.Z);
	}

	CVector RadToQ() const
	{
		return DirectX::XMQuaternionRotationRollPitchYaw(X, Y, Z);
	}

	CVector QToRad()
	{
		CVector ReturnVector;

		float dx = X;
		float dy = Y;
		float dz = Z;
		float dw = W;

		float sqx = X * X;
		float sqy = Y * Y;
		float sqz = Z * Z;
		float sqw = W * W;

		ReturnVector.X = asinf(2.0f * (dw * dx - dy * dz));
		ReturnVector.Y = atan2f(2.0f * (dx * dz + dw * dy), -sqx - sqy + sqz + sqw);
		ReturnVector.Z = atan2f(2.0f * (dx * dy + dw * dz), -sqx + sqy - sqz + sqw);

		return ReturnVector;
	}

	CVector QToDeg()
	{
		return QToRad() * GameMath::RTOD;
	}

	/* 	단위벡터 : 빗변의 길이로 x,y축을 나누는 연산으로 길이가 1인 벡터  */
	/*
		벡터의 길이를 1로 변경하는 함수 float Len = Length3d();
		X /= Len;
		Y /= Len;
		Z /= Len;
	*/

	void Normalize3d()
	{
		DXVEC = DirectX::XMVector3Normalize(DXVEC);
		return;
	}

	CVector Normal3dVecReturn() const
	{
		CVector VEC = DirectX::XMVector3Normalize(DXVEC);
		return VEC;
	}

	CVector Normal2dVecReturn()
	{
		CVector VEC = *this;
		VEC.Z = 0;
		VEC.W = 0;
		VEC.DXVEC = DirectX::XMVector2Normalize(VEC.DXVEC);
		return VEC;
	}

	CVector& operator=(const CVector& _Value)
	{
		X = _Value.X;
		Y = _Value.Y;
		Z = _Value.Z;
		W = _Value.W;
		return *this;
	}

	bool operator==(const CVector& _Value) const
	{
		return X == _Value.X && Y == _Value.Y && Z == _Value.Z;
	}

	bool operator!=(const CVector& _Value) const
	{
		return X != _Value.X || Y != _Value.Y || Z != _Value.Z;
	}

	CVector operator+(const CVector& _Value) const
	{
		return { X + _Value.X, Y + _Value.Y, Z + _Value.Z };
	}

	CVector operator-(const CVector& _Value) const
	{
		return { X - _Value.X, Y - _Value.Y,  Z - _Value.Z };
	}

	CVector operator-()
	{
		return { -X, -Y, -Z };
	}

	CVector operator*(const CVector& _Value) const
	{
		return { X * _Value.X, Y * _Value.Y, Z * _Value.Z };
	}

	CVector operator/(const CVector& _Value) const
	{
		return { X / _Value.X, Y / _Value.Y,  Z / _Value.Z };
	}

	CVector operator/(const float _Value) const
	{
		return { X / _Value, Y / _Value, Z / _Value };
	}

	CVector& operator-=(const CVector& _Value)
	{
		X -= _Value.X;
		Y -= _Value.Y;
		Z -= _Value.Z;
		return *this;
	}

	CVector& operator+=(const CVector& _Value)
	{
		X += _Value.X;
		Y += _Value.Y;
		Z += _Value.Z;
		return *this;
	}

	CVector& operator*=(const CMatrix& _Value);

	CVector operator*(const CMatrix& _Value);

	CVector& operator*=(const float _Value)
	{
		X *= _Value;
		Y *= _Value;
		Z *= _Value;
		return *this;
	}

	CVector& operator*=(const CVector& _Value)
	{
		X *= _Value.X;
		Y *= _Value.Y;
		Z *= _Value.Z;
		return *this;
	}

	CVector operator*(const float& _Value) const
	{
		return { X * _Value, Y * _Value, Z * _Value };
	}

	operator POINT()
	{
		return POINT{ IX(), IY() };
	}

	void SetVector3d(const CVector& _Other)
	{
		X = _Other.X;
		Y = _Other.Y;
		Z = _Other.Z;
	}

	CVector RotDegReturn(const CVector& _Deg)
	{
		return RotRadReturn(_Deg * GameMath::DTOR);
	}

	CVector RotRadReturn(const CVector& _Rad)
	{
		return DirectX::XMVector3Rotate(*this, _Rad.RadToQ());
	}

	CVector RotDegZReturn(float _Deg)
	{
		return RotRadZReturn(_Deg * GameMath::DTOR);
	}

	CVector RotRadZReturn(float _Rad)
	{
		CVector CalPos = *this;
		CalPos.X = (X * cosf(_Rad)) - (Y * sinf(_Rad));
		CalPos.Y = (X * sinf(_Rad)) + (Y * cosf(_Rad));
		return CalPos;
	}

	CVector RotDegYReturn(float _Deg)
	{
		return RotRadYReturn(_Deg * GameMath::DTOR);
	}

	CVector RotRadYReturn(float _Rad)
	{
		CVector CalPos = *this;
		CalPos.X = (X * cosf(_Rad)) - (Z * sinf(_Rad));
		CalPos.Z = (X * sinf(_Rad)) + (Z * cosf(_Rad));
		return CalPos;
	}

	CVector RotDegXReturn(float _Deg)
	{
		return RotRadXReturn(_Deg * GameMath::DTOR);
	}

	CVector RotRadXReturn(float _Rad)
	{
		CVector CalPos = *this;
		CalPos.Y = (Y * cosf(_Rad)) - (Z * sinf(_Rad));
		CalPos.Z = (Y * sinf(_Rad)) + (Z * cosf(_Rad));
		return CalPos;
	}


	static float VectorToVectorAngleDeg2D(const CVector _Left, const CVector& _Right) // ★
	{
		return DirToDirAngle2D(_Left, _Right) * GameMath::RTOD;
	}

	static float DirToDirAngle2D(const CVector _Left, const CVector& _Right)// ★
	{
		CVector Left = _Left;
		CVector Right = _Right;

		Left.Z = 0.0f;
		Right.Z = 0.0f;
		Left.Normal3dVecReturn();
		Right.Normal3dVecReturn();

		float CosS = Dot(Left, Right);

		float RadAngle = acosf(CosS);

		if (_Right.X < _Left.X)
		{
			RadAngle = GameMath::PI2 - RadAngle;
		}
		// 역함수
		return RadAngle;
	}





	static float VectorToVectorAngle2DPivot(CVector _Pivot, CVector _Left, CVector _Right)
	{
		return VectorToVectorAngle2D(_Left - _Pivot, _Right - _Pivot);
		//return VectorToVectorAngle2D(_Pivot  - _Left, _Pivot - _Right);

	}

	/*
	   static float VectorToVectorAngle2D(CVector _Left, CVector _Right)
	   {
		   _Left.Z = 0.0f;
		   _Right.Z = 0.0f;

		   _Left.Normalize3d();
		   _Right.Normalize3d();

		   CVector CrossResult = CVector::Cross3d(_Left, _Right);
		   float DotResult = CVector::Dot2d(_Left, _Right);
		   float DotResultRad = acosf(DotResult);
		   float DotResultDeg = DotResultRad * GameMath::RTOD;
		   if (0.0f > CrossResult.Z)
		   {
			   DotResultDeg = 360.0f - DotResultDeg;
		   }
		   else
		   {
			   DotResultDeg = DotResultDeg;
		   }

		   return DotResultDeg;
	   }
   */


	static float VectorToVectorAngle2D(CVector _Left, CVector _Right)
	{
		_Left.Z = 0.0F;
		_Left.W = 0.0F;
		_Right.Z = 0.0F;
		_Right.W = 0.0F;

		_Left.Normal2dVecReturn();
		_Right.Normal2dVecReturn();

		CVector Angle = DirectX::XMVector2AngleBetweenNormals(_Left, _Right);

		///////////////////////////////////////////////////////////////////////////////////// 1

		//if (_Left.Y > _Right.Y)
		//{
		//	Angle.X = Angle.X;
		//	return 360.0f - (Angle.X * GameMath::RTOD);
		//}
		//return Angle.X * GameMath::RTOD;

		///////////////////////////////////////////////////////////////////////////////////// 2

		if (_Left.X > _Right.X)
		{
			Angle.Y = Angle.Y;
			return (Angle.Y * GameMath::RTOD);

		}

		return -(Angle.Y * GameMath::RTOD);

	}



	void RotDegZ(float _Deg)
	{
		RotRadZ(_Deg * GameMath::DTOR);
	}

	void RotRadZ(float _Rad)
	{
		CVector CalPos = *this;
		CalPos.X = (X * cosf(_Rad)) - (Y * sinf(_Rad));
		CalPos.Y = (X * sinf(_Rad)) + (Y * cosf(_Rad));
		*this = CalPos;
	}

	void RotDegZMixRatio(float _Deg, float _RatioX)
	{
		RotRadZMixRatio(_Deg * GameMath::DTOR, _RatioX);
	}

	void RotRadZMixRatio(float _Rad, float _RatioX)
	{
		CVector CalPos = *this;
		CalPos.X = ((X * cosf(_Rad)) - (Y * sinf(_Rad))) * (_RatioX);
		CalPos.Y = (X * sinf(_Rad)) + (Y * cosf(_Rad));
		*this = CalPos;
	}

	void RotDegY(float _Rad)
	{
		RotRadY(_Rad * GameMath::DTOR);
	}

	void RotRadY(float _Rad)
	{
		CVector CalPos = *this;
		CalPos.X = (X * cosf(_Rad)) - (Z * sinf(_Rad));
		CalPos.Z = (X * sinf(_Rad)) + (Z * cosf(_Rad));
		*this = CalPos;
	}

	void RotDegX(float _Rad)
	{
		RotRadX(_Rad * GameMath::DTOR);
	}

	void RotRadX(float _Rad)
	{
		CVector CalPos = *this;
		CalPos.Y = (Y * cosf(_Rad)) - (Z * sinf(_Rad));
		CalPos.Z = (Y * sinf(_Rad)) + (Z * cosf(_Rad));
		*this = CalPos;
	}

	void ScalaProduct(float _Size)
	{
		CVector CalPos = *this;
		CalPos.X *= _Size;
		CalPos.Y *= _Size;
		CalPos.Z *= _Size;
		*this = CalPos;
	}

	CVector ScalaProductReturn(float _Size)
	{
		CVector CalPos = *this;
		CalPos* _Size;
		return CalPos;
	}

public:
	CVector() : X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) {}
	CVector(const int _X, const int _Y) : X((float)_X), Y((float)_Y), Z(0.0f), W(1.0f) {}
	CVector(const float _X, const  float _Y) : X(_X), Y(_Y), Z(0.0f), W(1.0f) {}
	CVector(const float _X, const  float _Y, const  float _Z) : X(_X), Y(_Y), Z(_Z), W(1.0f) {}
	CVector(const float _X, const  float _Y, const  float _Z, const  float _W) : X(_X), Y(_Y), Z(_Z), W(_W) {}
	CVector(const CVector& _Other) : X(_Other.X), Y(_Other.Y), Z(_Other.Z), W(_Other.W) {}
	CVector(const DirectX::XMVECTOR& _Other) : DXVEC(_Other) {}
};

class CMatrix
{
public:
	union
	{
		struct
		{
			float Arr2D[4][4];
		};

		struct
		{
			float ArrF1D[16];
		};

		struct
		{
			CVector ArrV[4];
		};
		/* 64bit만 */
		DirectX::XMMATRIX DXMAT;
		/* 	union >> 메모리 주소를 공유함 */
	};

public:
	CMatrix() { UnitMat(); }

	CMatrix(const CMatrix& _Other) : Arr2D{ 0, }
	{
		memcpy_s(this, sizeof(CMatrix), &_Other, sizeof(CMatrix));
	}

	CMatrix(const DirectX::XMMATRIX& _Other)
	{
		DXMAT = _Other;
	}

	~CMatrix() { }

public:
	operator DirectX::XMMATRIX() const
	{
		return DXMAT;
	}

#pragma region 단위행렬만들기 
	/*
		memset(this, 0, sizeof(CMatrix));
		ArrF2D[0][0] = ArrF2D[1][1] = ArrF2D[2][2] = ArrF2D[3][3] = 1.0F;
	*/
#pragma endregion


public:
	static CMatrix Affine(CVector _Scale, CVector _RotQ, CVector _Pos)
	{

		return DirectX::XMMatrixAffineTransformation(_Scale, CVector::ZERO, _RotQ, _Pos);
	}

	static CMatrix Transformation(CVector _Scale, CVector _RotQ, CVector _Pos)
	{
		return DirectX::XMMatrixTransformation(CVector::ZERO, CVector::ZERO, _Scale.DXVEC, CVector::ZERO, _RotQ, _Pos);
	}


	CVector ExtractScaling()
	{
		CVector ret = CVector::ZERO;

		float Tolerance = 1.e-8f;

		const float SquareSum0 = (Arr2D[0][0] * Arr2D[0][0]) + (Arr2D[0][1] * Arr2D[0][1]) + (Arr2D[0][2] * Arr2D[0][2]);
		const float SquareSum1 = (Arr2D[1][0] * Arr2D[1][0]) + (Arr2D[1][1] * Arr2D[1][1]) + (Arr2D[1][2] * Arr2D[1][2]);
		const float SquareSum2 = (Arr2D[2][0] * Arr2D[2][0]) + (Arr2D[2][1] * Arr2D[2][1]) + (Arr2D[2][2] * Arr2D[2][2]);

		if (SquareSum0 > Tolerance)
		{
			float Scale0 = sqrtf(SquareSum0);
			ret.X = Scale0;
			float InvScale0 = 1.f / Scale0;
			Arr2D[0][0] *= InvScale0;
			Arr2D[0][1] *= InvScale0;
			Arr2D[0][2] *= InvScale0;
		}
		else
		{
			ret.X = 0;
		}

		if (SquareSum1 > Tolerance)
		{
			float Scale1 = sqrtf(SquareSum1);
			ret.Y = Scale1;
			float InvScale1 = 1.f / Scale1;
			Arr2D[1][0] *= InvScale1;
			Arr2D[1][1] *= InvScale1;
			Arr2D[1][2] *= InvScale1;
		}
		else
		{
			ret.Y = 0;
		}

		if (SquareSum2 > Tolerance)
		{
			float Scale2 = sqrtf(SquareSum2);
			ret.Z = Scale2;
			float InvScale2 = 1.f / Scale2;
			Arr2D[2][0] *= InvScale2;
			Arr2D[2][1] *= InvScale2;
			Arr2D[2][2] *= InvScale2;
		}
		else
		{
			ret.Z = 0;
		}

		return ret;
	}

	inline float Determinant() const
	{
		return	Arr2D[0][0] * (
			Arr2D[1][1] * (Arr2D[2][2] * Arr2D[3][3] - Arr2D[2][3] * Arr2D[3][2]) -
			Arr2D[2][1] * (Arr2D[1][2] * Arr2D[3][3] - Arr2D[1][3] * Arr2D[3][2]) +
			Arr2D[3][1] * (Arr2D[1][2] * Arr2D[2][3] - Arr2D[1][3] * Arr2D[2][2])
			) -
			Arr2D[1][0] * (
				Arr2D[0][1] * (Arr2D[2][2] * Arr2D[3][3] - Arr2D[2][3] * Arr2D[3][2]) -
				Arr2D[2][1] * (Arr2D[0][2] * Arr2D[3][3] - Arr2D[0][3] * Arr2D[3][2]) +
				Arr2D[3][1] * (Arr2D[0][2] * Arr2D[2][3] - Arr2D[0][3] * Arr2D[2][2])
				) +
			Arr2D[2][0] * (
				Arr2D[0][1] * (Arr2D[1][2] * Arr2D[3][3] - Arr2D[1][3] * Arr2D[3][2]) -
				Arr2D[1][1] * (Arr2D[0][2] * Arr2D[3][3] - Arr2D[0][3] * Arr2D[3][2]) +
				Arr2D[3][1] * (Arr2D[0][2] * Arr2D[1][3] - Arr2D[0][3] * Arr2D[1][2])
				) -
			Arr2D[3][0] * (
				Arr2D[0][1] * (Arr2D[1][2] * Arr2D[2][3] - Arr2D[1][3] * Arr2D[2][2]) -
				Arr2D[1][1] * (Arr2D[0][2] * Arr2D[2][3] - Arr2D[0][3] * Arr2D[2][2]) +
				Arr2D[2][1] * (Arr2D[0][2] * Arr2D[1][3] - Arr2D[0][3] * Arr2D[1][2])
				);
	}



public:
	// 단위행렬(unit),항등행렬(identity)
	void UnitMat()
	{
		DXMAT = DirectX::XMMatrixIdentity();
	}

	void RotDeg(const CVector& _Value)
	{
		RotRad(_Value * GameMath::DTOR);
	}

	void RotRad(const CVector& _Value)
	{
		DXMAT = DirectX::XMMatrixRotationRollPitchYaw(_Value.X, _Value.Y, _Value.Z);
	}

	void RotXDeg(float _Angle)
	{
		RotXRad(_Angle * GameMath::DTOR);
	}

	void RotXRad(float _Angle)
	{
		UnitMat();
		DXMAT = DirectX::XMMatrixRotationX(_Angle);
		/*
			~
			ArrF2D[1][1] = cosf(_Angle);
			ArrF2D[1][2] = -sinf(_Angle);
			ArrF2D[2][1] = sinf(_Angle);
			ArrF2D[2][2] = cosf(_Angle);
			~
		*/
	}

	void RotYDeg(float _Angle)
	{
		RotYRad(_Angle * GameMath::DTOR);
	}

	void RotYRad(float _Angle)
	{
		UnitMat();
		DXMAT = DirectX::XMMatrixRotationY(_Angle);
		/*
			void RotYRad(float _Angle)
			{
				~
				ArrF2D[0][0] = cosf(_Angle);
				ArrF2D[0][2] = sinf(_Angle);
				ArrF2D[2][0] = -sinf(_Angle);
				ArrF2D[2][2] = cosf(_Angle);
				~
			}
		*/
	}

	void RotZDeg(float _Angle)
	{
		RotZRad(_Angle * GameMath::DTOR);
	}

	void RotZRad(float _Angle)
	{
		UnitMat();
		DXMAT = DirectX::XMMatrixRotationZ(_Angle);
		/*
			void RotZRad(float _Angle)
			{
				~
				ArrF2D[0][0] = cosf(_Angle);
				ArrF2D[0][1] = -sinf(_Angle);
				ArrF2D[1][0] = sinf(_Angle);
				ArrF2D[1][1] = cosf(_Angle);
				~
			}
		*/
	}

	void Pos3d(const CVector& _Value)	/* ArrV[3].SetVector3d(_Value); */
	{
		UnitMat();
		DXMAT = DirectX::XMMatrixTranslation(_Value.X, _Value.Y, _Value.Z);
		/*
			참고) 64비트에서만 된다. 32비트로 빌드하면 안된다.
			DXMAT = DirectX::XMLoadFloat4x4(DirectX::XMMatrixTranslation(_Value.X, _Value.Y, _Value.Z));
			#ifdef X64
			#else
			#endif
		*/
	}

	void Scale3d(const CVector& _Value)
	{
		UnitMat();
		/*
			void Scale3d(const CVector& _Value)
			{
				~
				ArrF2D[0][0] = _Value.X;
				ArrF2D[1][1] = _Value.Y;
				ArrF2D[2][2] = _Value.Z;
				~
			}
		*/
		_Value.ZEROCHECK();
		DXMAT = DirectX::XMMatrixScaling(_Value.X, _Value.Y, _Value.Z);
	}

	void SetWorld(const CVector& _Scale, const CVector& _EulerRot, const CVector& _Pos)
	{
		CMatrix Scale;
		CMatrix Rot;
		CMatrix Pos;

		Scale.Scale3d(_Scale);
		Rot.RotDeg(_EulerRot);
		Pos.Pos3d(_Pos);

		*this = Scale * Rot * Pos;
	}


#pragma region 뷰행렬매커니즘
	/*
		CVector Dir = _EyeDir;
		CVector Up = _EyeUp;

		Dir.Normalize3d();
		Up.Normalize3d();

		ArrV[2] = Dir;
		ArrV[1] = Up;

		ArrV[0] = CVector::Corss3D(ArrV[1], ArrV[2]);
		TRANSPOSE();

		ArrV[3] =
		{
			CVector::Dot(ArrV[0], _Pos),
			CVector::Dot(ArrV[1], _Pos),
			CVector::Dot(ArrV[2], _Pos)
		};
	*/
#pragma endregion

	void VIEWLH(const CVector& _Pos, const CVector& _EyeDir, const CVector& _EyeUp)
	{
		UnitMat();
		DXMAT = DirectX::XMMatrixLookToLH(_Pos, _EyeDir, _EyeUp);
		/* LookAt함수(LookAt은 위치만 인자로 넣어주면된다.) */
		return;
	}

#pragma region 원근투영
	/*
		_FOV : 수직 시야각
		_Width : 출력하고 싶은 화면의 너비
		_Height : 출력하고 싶은 화면의 높이
		_Near : 근평면의 거리
		_Far : 원평면의 거리
	*/
#pragma endregion

	// ArrF2D
	void VIEWPORT(float _StartX, float _StartY, float _W, float _H, float _MinZ, float _MaxZ)
	{
		UnitMat();
		Arr2D[0][0] = _W / 2;
		Arr2D[1][1] = -(_H / 2);
		Arr2D[2][2] = _MinZ - _MaxZ;
		Arr2D[3][0] = _StartX + Arr2D[0][0];
		Arr2D[3][1] = _StartY + (_H / 2);
		Arr2D[3][2] = _MinZ;
	}

	void INVERSE()
	{
		DXMAT = DirectX::XMMatrixInverse(nullptr, DXMAT);	/* 역행렬 */
	}

	CMatrix InverseReturn()
	{
		CMatrix ReturnMat = DirectX::XMMatrixInverse(nullptr, DXMAT);
		return ReturnMat;
	}

	void ORTHLH(const CVector& _Size, float _Near, float _Far)
	{
		UnitMat();
		DXMAT = DirectX::XMMatrixOrthographicLH(_Size.X, _Size.Y, _Near, _Far);
		return;
	}

	void PERSDEG(float _Fov, const CVector& _Size, float _Near, float _Far)
	{
		PERSRAD(_Fov, _Size.X, _Size.Y, _Near, _Far);
	}

	/* 	화면 전체(점)를 -1 ~ +1 사이에 가져다 놓자. */
	void PERSRAD(float _Fov, float _Width, float _Height, float _Near, float _Far)
	{
		UnitMat();
		DXMAT = DirectX::XMMatrixPerspectiveFovLH(_Fov * GameMath::DTOR, _Width / _Height, _Near, _Far);
		return;
	}

#pragma region 원근투영행렬 매커니즘
	/*
		<누운 직각삼각형 60도->라디안전환>
		float A = _Fov * GameMath::DTOR;

		<비율>
		float R = _Width / _Height;

		<수평시야각공식>
		float B = A * R;

		<어떤 X, Y가 화면 어떻게 나올까?>
		X' = 1 / (tanf(B / 2)) * X;

		<수평으로 x가 어떻게 줄어드느냐에 대한 비율>
		ArrF2D[0][0] = 1 / (R * tanf(A / 2));

											* Y / Z
		<수직으로 Y가 어떻게 줄어드느냐에 대한 비율>
		ArrF2D[1][1] = 1 / (tanf(A / 2));

					   6       4          4
										   * Z / Z
		<이 수치가 곱해지면 원래 자신의 Z를 잃어버리게 된다.>
		ArrF2D[2][2] = _Far / (_Far - _Near);
		ArrF2D[3][2] = (-_Near * _Far) / (_Far - _Near);
		ArrF2D[2][3] = 1.0F;
		ArrF2D[3][3] = 0.0F;
	*/
#pragma endregion

	void TRANSPOSE() /* 변환행렬 */
	{
		DXMAT = DirectX::XMMatrixTranspose(DXMAT);
#pragma region 행렬만들기
		/*
			CMatrix Mat;
			for (size_t y = 0; y < 4; y++)
			{
				for (size_t x = 0; x < 4; x++)
				{
					Mat.ArrF2D[y][x] = ArrF2D[x][y];
				}
			}

			*this = Mat;
		*/
#pragma endregion
	}



	CVector GetQ()
	{
		return DirectX::XMQuaternionRotationMatrix(DXMAT);
	}

	CVector MulOne(CVector _Vector)
	{
		_Vector.W = 1.0f;

		return DirectX::XMVector4Transform(_Vector, DXMAT);
	}

	CVector MulZero(CVector _Vector)
	{
		_Vector.W = 0.0f;
		return DirectX::XMVector4Transform(_Vector, DXMAT);
	}






public:
	CMatrix& operator=(const CMatrix& _Value)
	{
		memcpy_s(this, sizeof(CMatrix), &_Value, sizeof(CMatrix));
		return *this;
	}

	CMatrix operator*(const CMatrix& _Value) const
	{
		CMatrix Mat = DirectX::XMMatrixMultiply(DXMAT, _Value.DXMAT);
		return Mat;
#pragma region 행렬만들기
		/*
			CMatrix NewMat;

			for (size_t y = 0; y < 4; y++)
			{
				for (size_t x = 0; x < 4; x++)
				{
					NewMat.ArrF2D[y][x] = 0.0f;
					for (size_t CalCount = 0; CalCount < 4; CalCount++)
					{
						NewMat.ArrF2D[y][x] += ArrF2D[y][CalCount] * _Value.ArrF2D[CalCount][x];
					}
					int a = 0;
				}
			}

			return NewMat;
		*/
#pragma endregion
	}

};

enum class MATTYPE
{
	MATTYPE_POS,
	MATTYPE_SCALE,
	MATTYPE_ROT,
	MATTYPE_REVO,
	MATTYPE_PARENT,
	MATTYPE_LWORLD,
	MATTYPE_WWORLD,
	MATTYPE_VIEW,
	MATTYPE_PROJ,
	MATTYPE_WV,
	MATTYPE_VP,
	MATTYPE_WVP,
	MATTYPE_MAX,
};


class CTransformData
{
public:
	union
	{
		struct
		{
			CMatrix POS;
			CMatrix SCALE;
			CMatrix ROT;
			CMatrix REVO;
			CMatrix PARENT;
			CMatrix LWORLD;
			CMatrix WWORLD;
			CMatrix VIEW;
			CMatrix PROJ;
			CMatrix WV;
			CMatrix VP;
			CMatrix WVP;
		};
		CMatrix	ARRMAT[(int)MATTYPE::MATTYPE_MAX];
	};

public:
	void CalUnitMatrix()
	{
		for (auto& _Value : ARRMAT)
		{
			_Value.UnitMat();
		}
	}

	void CalTransposMat()
	{
		for (auto& _Value : ARRMAT)
		{
			_Value.TRANSPOSE();
		}
	}

	void CalLWorld()
	{
		LWORLD = SCALE * ROT * POS * REVO;
	}

	void CalWWorld()
	{
		WWORLD = LWORLD * PARENT;
	}

	void SetVP(CMatrix _VIEW, CMatrix _PROJ)
	{
		VIEW = _VIEW;
		PROJ = _PROJ;
	}

	/* 데이터 수정, 업데이트의 편의성을 위한 방식 */
	void CalWVP()
	{
		WV = WWORLD * VIEW;
		VP = VIEW * PROJ;
		WVP = WWORLD * VIEW * PROJ;
	}

public:
	void CalTransData()
	{
		CalLWorld();
		CalWWorld();
		CalWVP();
	}

public:
	CTransformData() : LWORLD() 
	{
	}

	CTransformData(const CTransformData& _Other)
	{
		memcpy_s(this, sizeof(CTransformData), &_Other, sizeof(CTransformData));
	}

	~CTransformData() 
	{
	}

};


struct int2
{
	union
	{
		struct
		{
			int x;
			int y;
		};

		__int64 Key;

		struct
		{
			int Arr[2];
		};
	};

};

struct int4
{
	union
	{
		struct
		{
			int x;
			int y;
			int z;
			int w;
		};
		struct
		{
			int Arr[4];
		};
	};

};

typedef CVector float4;

/////////////////////////////////////////////////////////////// 추가 

enum class MATTYPE_PLUS
{
	MATTYPE_PLUS_POS,
	MATTYPE_PLUS_GRID_DIVIDE,
	MATTYPE_PLUS_GRID_AREA,
	MATTYPE_PLUS_GRID_MIN_ALPHA,
	MATTYPE_PLUS_LINE_THICKNESS,
	MATTYPE_PLUS_MAX,
};

class CTransDataPlus
{
public:
	union
	{
		struct
		{
			CVector Pos;
			float GridDivide;
			float GridArea;
			float GridMinAlpha;
			float LineThickness;
		};

		CMatrix ARRMAT[(int)MATTYPE_PLUS::MATTYPE_PLUS_MAX];
	};

public:
	void CalUnitMat()
	{
		for (auto& _Value : ARRMAT)
		{
			_Value.UnitMat();
		}
	}

	void FloatSetting(float _GridDivide, float _GridArea, float _GridMinAlpha, float _LineThickness)
	{
		GridDivide = _GridDivide;
		GridArea = _GridArea;
		GridMinAlpha = _GridMinAlpha;
		LineThickness = _LineThickness;
	}

public:
	CTransDataPlus()
	{
	}

	CTransDataPlus(const CTransDataPlus& _Other)
	{
		memcpy_s(this, sizeof(CTransDataPlus), &_Other, sizeof(CTransDataPlus));
	}

	~CTransDataPlus()
	{
	}
};

#pragma region CalWVP
/*
	여기서 곱해진다.
	WWORLD	: 플레이어의 위치를 담고 있다.
	VIEW	: 카메라의 위치와 바라보는 뱡향, 회전 (이동했음에도 (0,0)에 있다.)
	WVP     : 투영까지 전부다 정해졌다.
*/
#pragma endregion
