#pragma once

// 다형성 : 
// 상속구조에서 모두가 가지지만
// , 다르게 동작하게 하는 설계

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
	/// 어떤함수가 가장 먼저실행되나? 마지막실행은? 
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
