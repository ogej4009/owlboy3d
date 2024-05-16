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
			MSG_ASSERT_CODE(_Name + L"이름의 오브젝트가 이미지 존재합니다");
		}

		m_AllObj[_Name] = _NewObj;
	}

	template<typename ... REST>
	static CPtr<T> CreateAndInsert(const GameString& _Name, REST ... _Arg)
	{
		if (Find(_Name) != nullptr)
		{
			MSG_ASSERT_CODE(_Name + L"이름의 오브젝트가 이미 존재합니다");
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
			MSG_ASSERT_CODE(_Name + L"이름의 오브젝트가 이미 존재합니다");
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
			MSG_ASSERT_CODE(_Name + L"이름의 오브젝트가 존재하지 않습니다. ");
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

// 목적 : 경로가 필요한 상황을 대비해서 여러 Case를 관리하기 위한 상위 클래스 개념
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
	static T* FirstObj; // Window, Device를 위한 첫 오브젝트 

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

#pragma region 상속의 복합적인 문제 

/*
	template<typename T>
	class GameObjTFuncMgr : public CRef, public GameName // 상속으로 코드 줄이다.
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
	위처럼 GameObjTFuncMgr 같은 클래스는 모든 파트에 쓰인다.
	결과적으로 상속관계의 가장 말단의 클래스가 인터페이스를 너무 많이 상속을 받는다.
	이 문제를 피하기 위한 방법 : 다중 상속, 필요한 객체를 클래스로 만들어서 래핑하는 방법이 있다.
	예를 들어, GameFirstObjMgr처럼 FirstObj를 클래스로 만드는 방법
*/
#pragma endregion

#pragma region 템플릿 가변인자의 특징
/*
	함수에 인자가 몇개가 들어올지 모른다.
	결국 REST ... _Arg 가 어떻게 처리될지 모른다.
	단지 전달만 한다.
*/
#pragma endregion