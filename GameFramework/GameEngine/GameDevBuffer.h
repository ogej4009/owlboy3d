#pragma once
#include "GameDevice.h"

class GameDevBuffer
{
protected:
	D3D11_BUFFER_DESC m_BufferDesc;
	ID3D11Buffer* m_pBuffer;
	ID3D11Buffer* m_instanceBuffer;

public:
	GameDevBuffer() : m_instanceBuffer(nullptr), m_pBuffer(nullptr), m_BufferDesc({ 0, })  // 멤버이니셜라이저문법
	{
	}

	~GameDevBuffer()
	{
		if (nullptr != m_pBuffer)
		{
			m_pBuffer->Release();
		}

		if (nullptr != m_instanceBuffer)
		{
			m_instanceBuffer->Release();
		}
	}
};

// 디바이스 버퍼 
// 그래픽카드에 디바이스가 원하는 정보를 넣을 공간을 확보해달라는 요청을 보낸다. 
// 프로그램 -(요청)-> 디바이스 -> 그래픽카드 : 느림  
// 프로그램 -(요청)-> CPU					 : 빠름

// 그래픽카드 -> 메모리 잠금 
// 메모리 관련 요청을 하면, 그래픽 카드가 진행중이던 그림을 그리는 행위를 멈추고(하고 있다면...) 
// RUN 하던 메모리를 활용을 중단 장금하고, 요청을 받는다. 