#pragma once
#include <list>
#include "GameString.h"
#include "CPtr.h"

template<typename MGRTYPE>
class GameObjListTFuncMgr
{

#pragma region RTTI == 	RUN TIME TYPE INFOMATION
	/*
		���� ���� �Ϲ������� �� �� ���� 'Ÿ��'�� �� �� �ְ� ���ִ� ����� RTTI��� �Ѵ�.
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

#pragma region ������ ���� 
	/*
		�������� ��Ŀ������ �̿��Ѵ�.
		�̸��� Ŭ������ ���� ������Ʈ�� ����ϱ� ���� �Ѵ�.
		�ڷᱸ���� Ȱ���Ѵ�. std::list<CListData>	m_ObjList;
	*/
#pragma endregion
protected:
	std::list<CListData>	m_ObjList;

public:
	GameObjListTFuncMgr() {}
	virtual ~GameObjListTFuncMgr() {}

#pragma region ���ַ̼��̼� ��
	/*
		�θ�-�ڽ�
		��� �������� ������ �ظ��ϸ� ��Ȳ���� �ɰ� ���´�.
		�������� ���� �θ𿡼� dynamic-cast �Ѵ�.
		���־��ų� ������ �´� �ʿ��� �κи� �ϳ��� Ŭ������ ������ �ϴ� ��Ÿ��.
	*/
#pragma endregion

public:
	template<typename CREATETYPE>
	CPtr<CREATETYPE> CreateObj(const GameString& _Name = L"")
	{
		CListData Data;
		Data.Name = _Name;
		Data.Type = &typeid(CREATETYPE);
#pragma region RTTI�̽� & �ٿ�ĳ���� 
		/*
			������ typeid�� ��� �ð����� ���ǵȴ�
			�����Ϸ��� �˾Ƽ� Ÿ���� �������� �˷��ִ� ��� ��ü�� RTTI��� �Ѵ�.
		*/
		/*
			EX) CPtr<MGRTYPE> Obj
				�ǵ� : CPtr<SceneComponent> Obj�� ���� �Ϸ��� �ߴ�.
				���� : CPtr<_ljSceneTitle> Obj�� �ǵ�ȴ�.
				CPtr<SceneComponent> Obj ----(����)----> CPtr<_ljSceneTitle> Obj
				�̷��� �ٿ�ĳ���� ���� ��Ȳ�� ������ ��
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

	CPtr<MGRTYPE> FindObjName(const GameString& _Name) // �̸����� ã�´�. 
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
#pragma region RTTI�̽� & �ٿ�ĳ���� 
			/*
				������ typeid�� ��� �ð����� ���ǵȴ�
				�����Ϸ��� �˾Ƽ� Ÿ���� �������� �˷��ִ� ��� ��ü�� RTTI��� �Ѵ�.
			*/
			/*
				EX) _Value.Obj�� Type���� ���𰡸� �Ϸ��� �ߴ�.
					�ǵ� : CPtr<SceneComponent> �� find �Ϸ��� �ߴ�.(�׷���)
					���� : CPtr<_ljSceneTitle> �� �ǵ�ȴ�.
					�̷��� �ٿ�ĳ���� ���� ��Ȳ�� ������ ��
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