#pragma once

// ������ : 
// ��ӱ������� ��ΰ� ��������
// , �ٸ��� �����ϰ� �ϴ� ����

class GameVirtualProgress
{
private:
	int		m_Order;
	bool	m_bIsUpdateObj;
	bool	m_bIsDeathObj;

public:
	bool	m_IsDebug;
	void DebugOn()
	{
		m_IsDebug = true;
	}

	void DebugOff()
	{
		m_IsDebug = false;
	}

	bool DebugCheck()
	{
		if (true == m_IsDebug)
		{
			return m_IsDebug;
		}

		return false;
	}

public:
	int Order()
	{
		return m_Order;
	}

	void Order(int _Order)
	{
		m_Order = _Order;
	}

	virtual bool IsUpdateObj()
	{
		return m_bIsUpdateObj;
	}

	virtual bool IsDeathObj()
	{
		return m_bIsDeathObj;
	}

	void Death()
	{
		m_bIsDeathObj = true;
	}

	void On()
	{
		m_bIsUpdateObj = true;
	}

	virtual void Off()
	{
		m_bIsUpdateObj = false;
	}

public:
	/// ��Լ��� ���� ��������ǳ�? ������������? 
	virtual void Init() {} 
	virtual void UpdatePrev() {}
	virtual void Update() {}
	virtual void UpdateNext() {}
	virtual void RenderPrev() {}
	virtual void RenderNext() {}
	virtual void CollisionPrev() {}
	virtual void CollisionNext() {}
	virtual void SceneChangeEnd() {}
	virtual void SceneChangeStart() {}
	virtual void Release() {} 

public:
	GameVirtualProgress() 
		: m_bIsUpdateObj(true)
		, m_bIsDeathObj(false)
		, m_IsDebug(false) 
		, m_Order(0)
	{
	}
	virtual ~GameVirtualProgress() {}
};

#define DEBUG_CHECK DebugCheck();
