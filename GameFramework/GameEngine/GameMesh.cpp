#include "GameMesh.h"

GameMesh::GameMesh() : m_InstancedRenderCount(0), m_DrawType(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}

GameMesh::~GameMesh()
{
}

void GameMesh::SetVtxBuffer(const GameString& _Name)
{
	m_VtxBuffer = GameVtxBuffer::Find(_Name);

	if (nullptr == m_VtxBuffer)
	{
		MSG_ASSERT_CODE(L"���ؽ� ���۰� nullptr �Դϴ�.");
	}

}
void GameMesh::SetIdxBuffer(const GameString& _Name)
{
	m_IdxBuffer = GameIdxBuffer::Find(_Name);

	if (nullptr == m_IdxBuffer)
	{
		MSG_ASSERT_CODE(L"�ε��� ���۰� nullptr �Դϴ�.");
	}
}

void GameMesh::Render()
{
	m_VtxBuffer->Setting();
	m_IdxBuffer->Setting();

	GameDevice::MainObj()->Context()->IASetPrimitiveTopology(m_DrawType);


	if (0 == m_InstancedRenderCount)
	{
		GameDevice::MainObj()->Context()->DrawIndexed(m_IdxBuffer->Count(), 0, 0);
	}
	else
	{
		GameDevice::MainObj()->Context()->DrawIndexedInstanced(m_IdxBuffer->Count(), m_InstancedRenderCount, 0, 0, 0);
	}
}

void GameMesh::SetVtxBuffer(CPtr<GameVtxBuffer> _Buffer)
{
	if (nullptr == _Buffer)
	{
		return;
	}

	m_VtxBuffer = _Buffer;
}

void GameMesh::SetIdxBuffer(CPtr<GameIdxBuffer> _Buffer)
{
	if (nullptr == _Buffer)
	{
		return;
	}

	m_IdxBuffer = _Buffer;
}
// CreateShaderResourceView