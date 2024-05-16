#pragma once
#include <vector>
#include <GameObjTFuncMgr.h>
#include "GameDevBuffer.h"
#include <CPtr.h>
#include "GameShader.h"

enum class CBUFMODE
{
	CB_LINK,
	CB_NEW,
	CB_NONE,
};

class GameConstantBuffer : public GameObjTFuncMgr<GameConstantBuffer>, public GameDevBuffer
{
public:
	template<typename T>
	static void Create(const GameString& _Name)
	{
		CPtr<GameConstantBuffer> Res = CreateAndInsert(_Name);
		Res->Create(sizeof(T));
		// 어떤구조체가 인자로 들어갈지 예측할수없다. 얼만큼 사이즈가 될지 모른다. 
	}

	static void Create(const GameString& _Name, unsigned int _Size)
	{
		CPtr<GameConstantBuffer> Res = CreateAndInsert(_Name);
		Res->Create(_Size);
	}

private:
	D3D11_MAPPED_SUBRESOURCE m_SubData;

public:
	void Create(unsigned int _Size);
	void Setting(SHADERTYPE _Type, unsigned int _Reg);

	template<typename T>
	void DataChange(const T& _Data)
	{
		DataChange((void*)&_Data, sizeof(T));
	}// (void*)강제형변환 

	void DataChange(void* _Data, unsigned int _Size);

public:
	GameConstantBuffer() {};
	~GameConstantBuffer() {};

};