#pragma once
#include <map>
#include "GameName.h"
#include "GameString.h"
#include "GameDebug.h"
#include "GameFile.h"
#include "CPtr.h"

template<typename T>
class GameObjTFuncMgr : public CRef, public GameName
{
public:
	static std::map<GameString, CPtr<T>> m_AllObj;

public:
	static CPtr<T> Find(const GameString& _Name)
	{
		if (m_AllObj.end() == m_AllObj.find(_Name))
		{
			return nullptr;
		}

		return m_AllObj[_Name];
	}

	static void Insert(const GameString& _Name, T* _NewObj)
	{
		if (Find(_Name) != nullptr)
		{
			MSG_ASSERT_CODE(_Name + L"�̸��� ������Ʈ�� �̹��� �����մϴ�");
		}

		m_AllObj[_Name] = _NewObj;
	}

	template<typename ... REST>
	static CPtr<T> CreateAndInsert(const GameString& _Name, REST ... _Arg)
	{
		if (Find(_Name) != nullptr)
		{
			MSG_ASSERT_CODE(_Name + L"�̸��� ������Ʈ�� �̹� �����մϴ�");
		}

		T* NewObj = new T(_Arg...);

		NewObj->Name(_Name);

		Insert(_Name, NewObj);

		return NewObj;
	}

	template<typename OBJ, typename ... REST>
	static CPtr<T> CreateAndInsertToChild(const GameString& _Name, REST ... _Arg)
	{
		if (Find(_Name) != nullptr)
		{
			MSG_ASSERT_CODE(_Name + L"�̸��� ������Ʈ�� �̹� �����մϴ�");
		}

		T* NewObj = new OBJ(_Arg...);

		NewObj->Name(_Name);

		Insert(_Name, NewObj);

		return NewObj;
	}


	static void Delete(const GameString& _Name)
	{
		if (Find(_Name) == nullptr)
		{
			MSG_ASSERT_CODE(_Name + L"�̸��� ������Ʈ�� �������� �ʽ��ϴ�. ");
		}

		m_AllObj.erase(_Name);
		return;
	}

	static void Clear()
	{
		m_AllObj.clear();
	}


public:
	virtual ~GameObjTFuncMgr() {}
};

template<typename T>
std::map<GameString, CPtr<T>> GameObjTFuncMgr<T>::m_AllObj;

// ���� : ��ΰ� �ʿ��� ��Ȳ�� ����ؼ� ���� Case�� �����ϱ� ���� ���� Ŭ���� ����
template<typename T>
class GameFileMgr : public GameObjTFuncMgr<T>
{
public:
	GameFile CFile;

public:
	template<typename ... REST>
	static CPtr<T> CreateAndInsertToFile(const GameString& _Path, REST ... _Arg)
	{
		CPtr<T> NewRes = GameObjTFuncMgr<T>::CreateAndInsert(GameIO::FileName(_Path), _Arg...);
		NewRes->CFile.SetPath(_Path);
		return NewRes;
	}

	template<typename ... REST>
	static CPtr<T> CreateAndInsertToName(const GameString& _Path, const GameString& _Name, REST ... _Arg)
	{
		CPtr<T> NewRes = GameObjTFuncMgr<T>::CreateAndInsert(_Name, _Arg...);
		NewRes->CFile.SetPath(_Path);
		return NewRes;
	}

	template<typename ... REST>
	static CPtr<T> CreateAndInsertToFileObj(const GameFile& _File, REST ... _Arg)
	{
		CPtr<T> NewRes = GameObjTFuncMgr<T>::CreateAndInsert(_File.FileName(), _Arg...);
		NewRes->CFile = _File;
		return NewRes;
	}
};

template<typename T>
class GameFirstObjMgr : public GameObjTFuncMgr<T>
{
private:
	static T* FirstObj; // Window, Device�� ���� ù ������Ʈ 

public:
	static T* MainObj()
	{
		return FirstObj;
	}

public:
	template<typename ... REST>
	static CPtr<T> CreateAndInsert(const GameString& _Name, REST ... _Arg)
	{
		CPtr<T> NewObj = GameObjTFuncMgr<T>::CreateAndInsert(_Name, _Arg...);
		if (nullptr == FirstObj)
		{
			FirstObj = NewObj;
		}

		return NewObj;
	}
};

template<typename T>
T* GameFirstObjMgr<T>::FirstObj = nullptr;

#pragma region ����� �������� ���� 

/*
	template<typename T>
	class GameObjTFuncMgr : public CRef, public GameName // ������� �ڵ� ���̴�.
	{
		private :
			static T* FirstObj;

		public:
			static T* MainObj()
			{
				return FirstObj;
			}
		...

*/
/*
	��ó�� GameObjTFuncMgr ���� Ŭ������ ��� ��Ʈ�� ���δ�.
	��������� ��Ӱ����� ���� ������ Ŭ������ �������̽��� �ʹ� ���� ����� �޴´�.
	�� ������ ���ϱ� ���� ��� : ���� ���, �ʿ��� ��ü�� Ŭ������ ���� �����ϴ� ����� �ִ�.
	���� ���, GameFirstObjMgró�� FirstObj�� Ŭ������ ����� ���
*/
#pragma endregion

#pragma region ���ø� ���������� Ư¡
/*
	�Լ��� ���ڰ� ��� ������ �𸥴�.
	�ᱹ REST ... _Arg �� ��� ó������ �𸥴�.
	���� ���޸� �Ѵ�.
*/
#pragma endregion