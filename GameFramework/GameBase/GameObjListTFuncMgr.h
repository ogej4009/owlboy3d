#pragma once
#include <list>
#include "GameString.h"
#include "CPtr.h"

template<typename MGRTYPE>
class GameObjListTFuncMgr
{

#pragma region RTTI == 	RUN TIME TYPE INFOMATION
	/*
		실행 도중 일반적으로 알 수 없는 '타입'을 알 수 있게 해주는 기술을 RTTI라고 한다.
	*/
#pragma endregion
public:
	class CListData
	{
	public:
		GameString Name;
		const type_info* Type;
		CPtr<MGRTYPE> Obj;
	};

#pragma region 다형성 응용 
	/*
		다형성의 메커니즘을 이용한다.
		이름과 클래스를 가진 오브젝트를 양산하기 위해 한다.
		자료구조로 활용한다. std::list<CListData>	m_ObjList;
	*/
#pragma endregion
protected:
	std::list<CListData>	m_ObjList;

public:
	GameObjListTFuncMgr() {}
	virtual ~GameObjListTFuncMgr() {}

#pragma region 아이솔레이션 팁
	/*
		부모-자식
		상속 구조에서 언제나 왠만하면 상황별로 쪼개 놓는다.
		다형성을 위해 부모에서 dynamic-cast 한다.
		자주쓰거나 목적에 맞는 필요한 부분만 하나의 클래스로 래핑을 하는 스타일.
	*/
#pragma endregion

public:
	template<typename CREATETYPE>
	CPtr<CREATETYPE> CreateObj(const GameString& _Name = L"")
	{
		CListData Data;
		Data.Name = _Name;
		Data.Type = &typeid(CREATETYPE);
#pragma region RTTI이슈 & 다운캐스팅 
		/*
			언제나 typeid는 상수 시간때에 정의된다
			컴파일러가 알아서 타입을 유저에게 알려주는 기능 자체를 RTTI라고 한다.
		*/
		/*
			EX) CPtr<MGRTYPE> Obj
				의도 : CPtr<SceneComponent> Obj을 관리 하려고 했다.
				문제 : CPtr<_ljSceneTitle> Obj를 건드렸다.
				CPtr<SceneComponent> Obj ----(수정)----> CPtr<_ljSceneTitle> Obj
				이러한 다운캐스팅 오류 상황을 조심할 것
		*/
#pragma endregion
		CREATETYPE* NewPtr = new CREATETYPE();
		Data.Obj = NewPtr;
		m_ObjList.push_back(Data);
		return NewPtr;
	}

	void InsertObj(CPtr<MGRTYPE> _Obj, const GameString& _Name = L"")
	{
		CListData Data;
		Data.Name = _Name;
		Data.Type = &typeid(MGRTYPE);
		Data.Obj = _Obj;
		m_ObjList.push_back(Data);
	}

	CPtr<MGRTYPE> FindObjName(const GameString& _Name) // 이름으로 찾는다. 
	{
		for (auto& _Value : m_ObjList)
		{
			if (_Value.Name == _Name)
			{
				return _Value.Obj;
			}
		}
		return nullptr;
	}

	template<typename FINDTYPE>
	CPtr<FINDTYPE> FindObjName(std::wstring _Name)
	{
		for (auto& _Value : m_ObjList)
		{
			if (_Value.Name == _Name)
			{
				return _Value.Obj;
			}
		}

		return nullptr;
	}

	bool IsObjName(std::wstring _Name)
	{
		for (auto& _Value : m_ObjList)
		{
			if (_Value.Name == _Name)
			{
				return true;
			}
		}

		return false;
	}



	template<typename FINDTYPE>
	CPtr<FINDTYPE> FindObjType()
	{
		for (auto& _Value : m_ObjList)
		{
#pragma region RTTI이슈 & 다운캐스팅 
			/*
				언제나 typeid는 상수 시간때에 정의된다
				컴파일러가 알아서 타입을 유저에게 알려주는 기능 자체를 RTTI라고 한다.
			*/
			/*
				EX) _Value.Obj의 Type으로 무언가를 하려고 했다.
					의도 : CPtr<SceneComponent> 를 find 하려고 했다.(그러나)
					문제 : CPtr<_ljSceneTitle> 를 건드렸다.
					이러한 다운캐스팅 오류 상황을 조심할 것
			*/
#pragma endregion
			if (_Value.Type == &typeid(FINDTYPE))
			{
				return _Value.Obj;
			}
		}
		return nullptr;
	}

	template<typename FINDTYPE>
	std::list<CPtr<FINDTYPE>> FindObjTypeAll()
	{
		std::list<CPtr<FINDTYPE>> List;
		for (auto& _Value : m_ObjList)
		{
			if (_Value.Type == &typeid(FINDTYPE))
			{
				List.push_back((FINDTYPE*)_Value.Obj);
			}
		}
		return List;
	}
};

template<typename MGRTYPE>
class GameObjListTFuncMgrProgress : public GameObjListTFuncMgr<MGRTYPE>
{
public:
	void UpdatePrev()
	{
		for (auto& Value : GameObjListTFuncMgr<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdateObj())
			{
				continue;
			}
			Value.Obj->UpdatePrev();
		}
	}

	void Update()
	{
		for (auto& Value : GameObjListTFuncMgr<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdateObj())
			{
				continue;
			}
			Value.Obj->Update();
		}
	}

	void UpdateNext()
	{
		for (auto& Value : GameObjListTFuncMgr<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdateObj())
			{
				continue;
			}
			Value.Obj->UpdateNext();
		}
	}

	void RenderPrev()
	{
		for (auto& Value : GameObjListTFuncMgr<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdateObj())
			{
				continue;
			}
			Value.Obj->RenderPrev();
		}
	}

	void RenderNext()
	{
		for (auto& Value : GameObjListTFuncMgr<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdateObj())
			{
				continue;
			}
			Value.Obj->RenderNext();
		}
	}

	void CollisionPrev()
	{
		for (auto& Value : GameObjListTFuncMgr<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdateObj())
			{
				continue;
			}
			Value.Obj->CollisionPrev();
		}
	}

	void CollisionNext()
	{
		for (auto& Value : GameObjListTFuncMgr<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdateObj())
			{
				continue;
			}
			Value.Obj->CollisionNext();
		}
	}

	void SceneChangeEnd()
	{
		for (auto& Value : GameObjListTFuncMgr<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdateObj())
			{
				continue;
			}
			Value.Obj->SceneChangeEnd();
		}
	}

	void SceneChangeStart()
	{
		for (auto& Value : GameObjListTFuncMgr<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdateObj())
			{
				continue;
			}
			Value.Obj->SceneChangeStart();
		}
	}

	void Release()
	{
		for (auto& Value : GameObjListTFuncMgr<MGRTYPE>::m_ObjList)
		{
			Value.Obj->Release();
		}
	}
}; // Intro  First